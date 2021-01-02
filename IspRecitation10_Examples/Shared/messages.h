//Name:messages.h
//Description: headers for the message module
//Authors:Amit Herman and Raz Rajwan
#include <string.h>
#include <stdio.h>

const char* server_messages[] = { "CLIENT_REQUEST", "PLAY_REQUEST","SEND_MESSAGE" }; //extern because client.c uses this too
const char* client_messges[] = { "

typedef struct message {

	int message_type;
	char * message_arguments;

}message;


/*	Declarations	*/
void delete_message(message* lp_msg);

message* process_Message(const char* message_text);

int get_message_code_server(const char* message_type);

