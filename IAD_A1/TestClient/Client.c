#include "Header.h"
#pragma warning (disable:4996)

int runClient(int connectionType, char* address, int port, int blockSize, int blockNum);


int main(void)
{
	runClient(1, "192.168.2.29", 12345, 12, 12);
	return 0;
}

/* This function starts and runs the client
*
*/
int runClient(int connectionType, char* address, int port, int blockSize, int blockNum)
{
	unsigned int serverIP;
	struct sockaddr_in server;
	SOCKET client_socket;
	char testString[255] = { "Hello, this is a test!" };
	char testRecv[255];
	WSADATA wsaData;

	//TODO: error check values from args
	if (WSAStartup(0x202, &wsaData) == SOCKET_ERROR) {
		return 1;
	}	/* endif */

	//set ip of server
	serverIP = inet_addr(address);

	//set socket info
	memset(&server, 0, sizeof(server));
	server.sin_addr.s_addr = serverIP; //ip address
	server.sin_family = AF_INET;
	server.sin_port = htons(port); //port

	//make socket
	client_socket = socket(AF_INET, SOCK_STREAM, 0);//TODO: ERROR CHECK

	//connect to socket
	connect(client_socket, (struct sockaddr*) &server, sizeof(server)); //TODO: ERROR CHECK

	//send info
	send(client_socket, testString, strlen(testString) + 1, 0);

	//recv response
	recv(client_socket, testRecv, 255, 0);
	testRecv[254] = '\0';

	printf("FROM SERVER: %s\n", testRecv);

	return 0;
}
