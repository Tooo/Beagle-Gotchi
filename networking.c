#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>	
#include <pthread.h>
#include <time.h>


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

static void *udp_listen_thread(void *threadId)
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