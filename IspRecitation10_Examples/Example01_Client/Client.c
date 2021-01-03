/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/
/*
 This file was written for instruction purposes for the
 course "Introduction to Systems Programming" at Tel-Aviv
 University, School of Electrical Engineering.
Last updated by Amnon Drory, Winter 2011.
 */
 /*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include "messages.h"
#include "../Shared/HardCodedData.h"
#include "Socket.h"
#include "threads.h"

/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/
HANDLE Send_event;
SOCKET m_socket;

/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/

//Reading data coming from the server

static DWORD UIThread(void)
{

}
static DWORD RecvDataThread(void)
{
	TransferResult_t RecvRes;

	while (1)
	{
		char* AcceptedStr = NULL;
		RecvRes = ReceiveString(&AcceptedStr, m_socket);

		if (RecvRes == TRNS_FAILED)
		{
			printf("Socket error while trying to write data to socket\n");
			free(AcceptedStr);
			return 0x555;
		}
		else if (RecvRes == TRNS_DISCONNECTED)
		{
			printf("Server closed connection. Bye!\n");
			free(AcceptedStr);
			return 0x555;
		}
		else
		{
			printf("%s\n", AcceptedStr);
		}

		free(AcceptedStr);
	}

	return 0;
}

/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/

//Sending data to the server
static DWORD SendDataThread(void)
{
	char SendStr[256];
	TransferResult_t SendRes;

	while (1)
	{
		gets_s(SendStr, sizeof(SendStr)); //Reading a string from the keyboard
		message* user_mes = process_Message(SendStr, 0); //TO-DO DEFINE IS SERVER; 
		if (STRINGS_ARE_EQUAL(SendStr, "quit"))
			return 0x555; //"quit" signals an exit from the client side
		SendRes = SendString(SendStr, m_socket);
		if (SendRes == TRNS_FAILED)
		{
			printf("Socket error while trying to write data to socket\n");
			free(user_mes);
			return 0x555;
		}
		free(user_mes);
	}
}

/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/

void MainClient(int argc ,char *argv [] )
{
	//int port = atoi(argv[1]);

	int ret_val = create_event_simple(&Send_event);
	if (ret_val != SUCCESS)
		return ret_val;
	SOCKADDR_IN clientService;
	HANDLE hThread[3];

	// Initialize Winsock.
	WSADATA wsaData; //Create a WSADATA object called wsaData.
	ret_val = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (ret_val != NO_ERROR)
	{
		printf("Error at WSAStartup()\n");
		goto clean1;
	}
	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// Check for errors to ensure that the socket is a valid socket.
	if (m_socket == INVALID_SOCKET) {
		ret_val = m_socket;
		printf("Error at socket(): %ld\n", WSAGetLastError());
		goto clean1;
	}
	//Create a sockaddr_in object clientService and set  values.
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr(SERVER_ADDRESS_STR); //Setting the IP address to connect to
	clientService.sin_port = htons(SERVER_PORT); //Setting the port to connect to.
	// Call the connect function, passing the created socket and the sockaddr_in structure as parameters. 
	// Check for general errors.
	if (connect(m_socket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
		ret_val = WSAGetLastError();
		/*
			printf("Failed to Connect to server on %d : %d", SERVER_ADDRESS_STR, SERVER_PORT);
			printf("Choose what to do next:");
			printf("1. Try to reconnect");
			printf("2. Exit");*/
		goto clean1;
	}
	printf("Connected to server on %d : %d", SERVER_ADDRESS_STR, SERVER_PORT);
	printf("please enter user name: ");
	hThread[0] = CreateThreadSimple((LPTHREAD_START_ROUTINE)SendDataThread, NULL, NULL);
	if (hThread[0] == NULL)
	{
		printf("cannot open send Thread");
		WSACleanup();
		goto clean2;
	}
	hThread[1] = CreateThreadSimple((LPTHREAD_START_ROUTINE)RecvDataThread,NULL,NULL);
	if (hThread[1] == NULL)
	{
		printf("cannot open recv Thread");
		goto clean2;
	}
	hThread[2] = CreateThreadSimple((LPTHREAD_START_ROUTINE)UIThread, NULL, NULL);
	if (hThread[2] == NULL)
	{
		printf("cannot open user interface thread.\n");
		goto clean2;
	} 
	ret_val=WaitForMultipleObjectsWrap(3, hThread, INFINITE, FALSE);
	if (ret_val != SUCCESS)
		goto clean3;
	ret_val = SUCCESS;
clean3:

	TerminateThread(hThread[0], 0x555);
	TerminateThread(hThread[1], 0x555);
	TerminateThread(hThread[2], 0x555);
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	CloseHandle(hThread[2]);
clean2:
	CloseSocketGracefullySender(m_socket);
clean1:
	WSACleanup();
	return ret_val;
	//return ret_val;
}

