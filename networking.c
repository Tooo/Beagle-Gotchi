#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>	
#include <pthread.h>
#include <time.h>

#include "petInteract.h"
#include "networking.h"
#include "pet.h"
#include "utils.h"

#define MSG_MAX_LEN 1024
#define MAX_MESSAGE_STATE_LEN 50
#define PORT        12345

struct sockaddr_in;
static pthread_t listenThread;
static int socketDescriptor;

bool stopping;

static void send_dgram(int sockDescriptor, struct sockaddr_in sinRemote, char* msg)
{
	unsigned int sin_len = sizeof(sinRemote);
	
	int res = sendto(sockDescriptor, msg, 
		strlen(msg), 0,
		(struct sockaddr *) &sinRemote, sin_len);
	
	if (res == -1) {
		printf("Invalid datagram sent!\n");
		exit(EXIT_FAILURE);
	} 
}

// Gets the full status from the pet and send it over udp
static void udp_get_status_command(int sockDescriptor, struct sockaddr_in sinRemote) 
{
	char *msg = (char*)malloc(MAX_MESSAGE_STATE_LEN  * sizeof(char));

	char *name = (char*)malloc(10  * sizeof(char));
	
	Pet_getName(name);
	int age = Pet_getAge();
	int mood = Pet_getMoodNum();
	int friendship = Pet_getFriendshipNum();
	int hunger = Pet_getHungerNum();
	int weight = Pet_getWeight();

	// Replace name spaces with underscore 
	name = replace_char(name, ' ', '_');

	// status {name} {age} {mood} {friendship} {hunger} {weight}
 	sprintf(msg, "status %s %d %d %d %d %d", name, age, mood, friendship, hunger, weight);
	// printf("%s\n", msg);

	send_dgram(sockDescriptor, sinRemote, msg);

	free(msg);
	free(name);
}

static void udp_feed_command(int sockDescriptor, struct sockaddr_in sinRemote, char* feed) {
	// Confirm feed
	char * reply = "feedSuccess";
	if (strncmp(feed, "meal", strlen("meal")) == 0) {
		PetInteract_feedMeal();
	}
	else if (strncmp(feed, "snack", strlen("snack")) == 0) {
		PetInteract_feedSnack();
	}
	else {
		printf("Invalid feed command from udp\n");
	}
	send_dgram(sockDescriptor, sinRemote, reply);
}

static void udp_interact_command(int sockDescriptor, struct sockaddr_in sinRemote, char* interaction) {
	// Confirm interact
	char * reply = "interactSuccess";
	if (strncmp(interaction, "pet", strlen("pet")) == 0) {
		PetInteract_pet();
	}
	else if (strncmp(interaction, "slap", strlen("slap")) == 0) {
		PetInteract_slap();
	}
	else {
		printf("Invalid interaction command from udp\n");
	}
	send_dgram(sockDescriptor, sinRemote, reply);
}

static void udp_get_pet_screen_command(int sockDescriptor, struct sockaddr_in sinRemote)
{
	int currentStage = Pet_getStage();

	char *msg = (char*)malloc(MAX_MESSAGE_STATE_LEN  * sizeof(char));

	sprintf(msg, "screen %d", currentStage);
	// printf("%s\n", msg);

	send_dgram(sockDescriptor, sinRemote, msg);

	free(msg);
}


static void *udp_listen_thread()
{
    // Address
	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;                   // Connection may be from network
	sin.sin_addr.s_addr = htonl(INADDR_ANY);    // Host to Network long
	sin.sin_port = htons(PORT);                 // Host to Network short
	
	// Create the socket for UDP
	socketDescriptor = socket(PF_INET, SOCK_DGRAM, 0);

	// Bind the socket to the port (PORT) that we specify
	bind (socketDescriptor, (struct sockaddr*) &sin, sizeof(sin));	

	// Check for errors (-1)

	while (!stopping) {
		// Get the data (blocking)
		// Will change sin (the address) to be the address of the client.
		// Note: sin passes information in and out of call!
		struct sockaddr_in sinRemote;
		unsigned int sin_len = sizeof(sinRemote);

		// Get message 
		char messageRx[MSG_MAX_LEN]; 
		int bytesRx;
		// Pass buffer size - 1 for max # bytes so room for the null (string data)
		bytesRx = recvfrom(socketDescriptor,
			messageRx, MSG_MAX_LEN - 1, 0,
			(struct sockaddr *) &sinRemote, &sin_len);
		// Check for errors (-1)
		// Make it null terminated (so string functions work)
		// - recvfrom given max size - 1, so there is always room for the null
		messageRx[bytesRx] = 0;
		
		// TODO: Commands
		if (strncmp(messageRx, "get-pet-screen", strlen("get-pet-screen")) == 0) {
			udp_get_pet_screen_command(socketDescriptor, sinRemote);
		}
		else if (strncmp(messageRx, "feed", strlen("feed")) == 0) {
			char feedString[6];
			memcpy(feedString, &messageRx[5], 5);

			udp_feed_command(socketDescriptor, sinRemote, feedString);
		}
		else if (strncmp(messageRx, "interact", strlen("interact")) == 0) {
			char interactString[6];
			memcpy(interactString, &messageRx[9], 5);

			udp_interact_command(socketDescriptor, sinRemote, interactString);
		}
		else if (strncmp(messageRx, "get-status", strlen("get-status")) == 0) {
			udp_get_status_command(socketDescriptor, sinRemote);
		}
		else if (bytesRx == 0) { // Close
			break;
		}
		else {
			printf("INVALID COMMAND\n");
		}
	}
    return NULL;
}

void udp_init(void) {
	// Create thread
	stopping = false;
	pthread_create(&listenThread, NULL, &udp_listen_thread, NULL);
	printf("Started UDP...\n");
}

void udp_clean_up(void) {
	stopping = true;
	shutdown(socketDescriptor, SHUT_RDWR);
	pthread_join(listenThread, NULL);
	// Close
	close(socketDescriptor);
}