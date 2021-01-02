//Name:messages.h
//Description: headers for the message module
#include <string.h>
#include <stdio.h>
#include "SocketSendRecvTools.h"
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define SERVER_MESSAGES_LEN 11
const char* server_messages[] = { "SERVER_MAIN_MENU",
								"SERVER_APPROVED",
								"SERVER_DENIED",
								"SERVER_INVITE",
								"SERVER_SETUP_REQUSET",
								"SERVER_PLAYER_MOVE_REQUEST",
								"SERVER_GAME_RESULTS",
								"SERVER_WIN",
								"SERVER_DRAW",
								"SERVER_NO_OPPONENTS",
								"SERVER_OPPONENT_QUIT" }; //extern because client.c uses this too

#define CLIENT_MESSAGES_LEN 5
const char* client_messges[] = { "CLIENT_REQUEST",
								"CLIENT_VERSUS",
								"CLIENT_SETUP",
								"CLIENT_PLAYER_MOVE",
								"CLIENT_DISCONNECT" };

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