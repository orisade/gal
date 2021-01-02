

/*
*	Name:messages.c
*	messages module implementation
*/

#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include "messages.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_MESSAGE_TYPE_SIZE 19 //according to to what we are given, that is 18 characters + null terminator


/* Free memory	*/
void delete_message(message* lp_msg) {

	free(lp_msg);
}


/*	Utility functions that support other function for general things	*/
int get_message_code_server(const char* message_type) {
	int i;

	for (i = 0; i < 3; i++) {
		if (strstr(message_type, server_messages[i]) == message_type)
			return i;

	}
	return -1;
}

message* process_Message(const char* message_text) {
	char message_type_string[MAX_MESSAGE_TYPE_SIZE];
	int message_type_size;
	char* token;
	int message_type_code;
	char* temp = 0;
	char* lp_params = NULL;
	message* proccessed_message;
	proccessed_message = (message*)malloc(sizeof(message));

	/* get the message type */
	if ((lp_params = strchr(message_text, ':')) == NULL)//parameterless message type
		message_type_code = get_message_code_server(message_text);

	else {
		message_type_size = (int)(lp_params - message_text);//lp_params-message=length of the first part of the message, e.g.:SEND_MESSAGE ==> 11 chars
		memcpy(message_type_string, message_text, message_type_size);//extract the first time of the message
		message_type_string[message_type_size] = '\0'; //add null terminator
		message_type_code = get_message_code_server(message_type_string);
	}

	if (message_type_code >= 0)
	{
		temp = (lp_params)+1;

		proccessed_message->message_arguments = temp;
	}
	else
	{
		proccessed_message->message_arguments = NULL;
	}

	proccessed_message->message_type = message_type_code;

	return proccessed_message;


}