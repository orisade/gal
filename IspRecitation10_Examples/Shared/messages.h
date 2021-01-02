//Name:messages.h
//Description: headers for the message module
#ifndef _MESSAGES_H
#define _MESSAGES_H
#include "HardCodedData.h"
#include <string.h>
#include <stdio.h>
#include "Socket.h"
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define SERVER_MESSAGES_LEN 11
#define CLIENT_MESSAGES_LEN 5


typedef struct message {

	int message_type;
	int message_argument_length;
	char* message_arguments;

}message;


/*	Declarations	*/
void delete_message(message* lp_msg);

message* process_Message(const char* message_text, int is_server);

int get_message_code(const char* message_type, int is_server);

int send_message_server(message* lp_message, SOCKET s_target);



#endif