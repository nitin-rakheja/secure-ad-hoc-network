/*
 *
 * Authentication Module
 *
 * Used for creating a authentication channel, and other authentication purposes
 *
 * Created on : 1. feb. 2011
 * Author     : Espen Graarud
 * Email      : espengra@stud.ntnu.no
 * Project    : Implementing a Secure Ad Hoc Network
 * Institution: NTNU (Norwegian University of Science & Technology), ITEM (Institute of Telematics)
 *
 */

#ifndef AM_H
#define AM_H

#include "batman.h"
//#include "os.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/string.h>
#include <stdio.h>

#define MAXBUFLEN 512	//max bytes, may have to be changed depending on certs sizes...
#define IF_NAMESIZE	16

enum am_type{
	NEW_SIGNATURE = 0,
	CHALLENGE = 1,
	CHALLENGE_RESPONSE = 2,
	RESPONSE = 3,
	AUTHENTICATED_LIST = 4,		//Full AL update
	AL_UPDATE = 5				//Single row update of the AL
};

enum pthread_status{
	IN_USE = 0,
	READY = 99
};

struct am_packet {
	uint16_t id;
	uint8_t type;
} __attribute__((packed));

struct challenge_packet {
	uint8_t challenge_value;
} __attribute__((packed));

struct challenge_response_packet {
	uint8_t challenge_value;
	uint8_t response_value;
} __attribute__((packed));

struct response_packet {
	uint8_t response_value;
	uint16_t auth_token;
} __attribute__((packed));

unsigned char recvBuf[MAXBUFLEN];
unsigned char sendBuf[MAXBUFLEN];
struct addrinfo hints, *res;
int32_t am_send_socket;
int32_t am_recv_socket;
struct am_packet *rcvd_am_header;
struct challenge_packet *rcvd_challenge_packet;
struct challenge_response_packet *rcvd_challenge_response_packet;
struct response_packet *rcvd_response_packet;
char *if_device;
char *addr_prev_sender;
char *my_addr;

void authenticate_thread_init(char *, uint16_t, char *, char *);
void *authenticate();

void setup_am_socks();
void setup_am_recv_sock();
void setup_am_send_sock();
void destroy_am_socks();

enum am_type receive_am_header();

void receive_challenge();
void receive_challenge_response();
void receive_response();

void send_challenge();
void send_challenge_response();
void send_response();





//Temp variables for simple auth
extern uint8_t is_authenticated;	// O eller 1
extern uint8_t my_challenge;		// My Challenge Value, set to 0 if no challenge to send
extern uint8_t my_response;			// My Response Value, set to 0 if no response to send
extern uint16_t my_auth_token;		// My Authentication Token Value, set to 0 if not authenticated
extern uint8_t tmp_response;		// Temporary response value, used in calculation
extern uint8_t generated_challenge;	// My last generated Challenge Value, used to verify received response in Request Message
extern uint8_t generated_request;	// My last generated Request (challenge in a Request message), used to verify received Response
extern uint8_t generated_auth;		// My generated Authentication Value to be used if authentication completes
extern uint8_t rcvd_challenge;		// Received Challenge Value, 0 if no challenge
extern uint8_t rcvd_response;		// Received Response Value, 0 if no response
extern uint16_t rcvd_auth_token;		// Received Authentication Token, 0 if not authenticated, or if not end of handshake
extern uint8_t expecting_token;		// Expected Value of received authentication token
extern uint32_t	random_wait_time;	// Random backoff time, tmp_wait + curr_time
extern uint32_t tmp_wait;			// Random backoff time value



#endif
