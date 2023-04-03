#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>	
#include <pthread.h>
#include <time.h>

#include "networking.h"

#define MSG_MAX_LEN 1024
#define MAX_MESSAGE_STATE_LEN 50
#define PORT        12345

struct sockaddr_in;
static pthread_t listenThread;
static int socketDescriptor;

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

// static void udp_change_mode_command(int sockDescriptor, struct sockaddr_in sinRemote, int n) {
// 	char * reply = "modeSuccess";

// 	State_set_mode(n);
	
// 	send_dgram(sockDescriptor, sinRemote, reply);
// }

// static void udp_increase_volume_command(int sockDescriptor, struct sockaddr_in sinRemote) {
// 	char * reply = "volumeSuccess";
// 	State_increase_volume();
// 	send_dgram(sockDescriptor, sinRemote, reply);
// }

// static void udp_decrease_volume_command(int sockDescriptor, struct sockaddr_in sinRemote) {
// 	char * reply = "volumeSuccess";
// 	State_decrease_volume();
// 	send_dgram(sockDescriptor, sinRemote, reply);
// }

// static void udp_increase_tempo_command(int sockDescriptor, struct sockaddr_in sinRemote) {
// 	char * reply = "tempoSuccess";
// 	State_increase_tempo();
// 	send_dgram(sockDescriptor, sinRemote, reply);
// }

// static void udp_decrease_tempo_command(int sockDescriptor, struct sockaddr_in sinRemote) {
// 	char * reply = "tempoSuccess";
// 	State_decrease_tempo();
// 	send_dgram(sockDescriptor, sinRemote, reply);
// }

// static void udp_play_sound_command(int sockDescriptor, struct sockaddr_in sinRemote, char* note) {
// 	// Confirm playing sound
// 	char * reply = "soundSuccess";
// 	if (strncmp(note, "hihat", strlen("hihat")) == 0) {
// 		State_play_sound(0);
// 	}
// 	else if (strncmp(note, "snare", strlen("snare")) == 0) {
// 		State_play_sound(1);
// 	}
// 	else if (strncmp(note, "bass", strlen("bass")) == 0) {
// 		State_play_sound(2);
// 	}
// 	else {
// 		printf("Invalid sound to play from udp\n");
// 	}
// 	send_dgram(sockDescriptor, sinRemote, reply);
// }

// static void udp_get_mode_command(int sockDescriptor, struct sockaddr_in sinRemote)
// {
// 	int mode = State_get_mode();
	
// 	char *modeMsg = (char*)malloc(MAX_MESSAGE_STATE_LEN * sizeof(char));
// 	sprintf(modeMsg, "state mode %i", mode);

// 	send_dgram(socketDescriptor, sinRemote, modeMsg);

// 	free(modeMsg);
// }

// static void udp_get_volume_command(int sockDescriptor, struct sockaddr_in sinRemote)
// {
// 	int volume = State_get_volume();
	
// 	char *msg = (char*)malloc(MAX_MESSAGE_STATE_LEN * sizeof(char));
// 	sprintf(msg, "state volume %i", volume);

// 	send_dgram(socketDescriptor, sinRemote, msg);

// 	free(msg);
// }

// static void udp_get_tempo_command(int sockDescriptor, struct sockaddr_in sinRemote)
// {
// 	int tempo = State_get_tempo();
	
// 	char *msg = (char*)malloc(MAX_MESSAGE_STATE_LEN * sizeof(char));
// 	sprintf(msg, "state tempo %i", tempo);

// 	send_dgram(socketDescriptor, sinRemote, msg);

// 	free(msg);
// }

// static void udp_get_uptime_command(int sockDescriptor, struct sockaddr_in sinRemote)
// {
// 	int uptime = get_device_uptime();
	
// 	char *msg = (char*)malloc(MAX_MESSAGE_STATE_LEN * sizeof(char));
// 	sprintf(msg, "state uptime %i", uptime);

// 	send_dgram(socketDescriptor, sinRemote, msg);
// 	free(msg);
// }

static void udp_feed_command(int sockDescriptor, struct sockaddr_in sinRemote, char* feed) {
	// Confirm feed
	char * reply = "feedSuccess";
	if (strncmp(feed, "food", strlen("food")) == 0) {
		printf("Feed food command.\n");
	}
	else if (strncmp(feed, "water", strlen("water")) == 0) {
		printf("Feed water command.\n");
	}
	else {
		printf("Invalid feed command from udp\n");
	}
	send_dgram(sockDescriptor, sinRemote, reply);
}

static void udp_get_pet_screen_command(int sockDescriptor, struct sockaddr_in sinRemote)
{
	// TODO: Get the current pet screen
	int currentStage = 0; 

	char *msg = (char*)malloc(MAX_MESSAGE_STATE_LEN  * sizeof(char));

	sprintf(msg, "screen %d", currentStage);
	printf("%s\n", msg);

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

	while (1) {
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
		else {
			printf("INVALID COMMAND\n");
		}
	}
    return NULL;
}

void init_udp_listen(void) {
	// Create thread
	pthread_create(&listenThread, NULL, &udp_listen_thread, NULL);
	printf("Started UDP...\n");
}

void udp_clean_up(void) {
	pthread_join(listenThread, NULL);
	// Close
	close(socketDescriptor);
}