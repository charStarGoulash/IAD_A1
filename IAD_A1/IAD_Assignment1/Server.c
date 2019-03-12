#include "Common.h"

//constants

//cases for switch 
#define FIRST_ARG 1
#define FIRST_CHAR 1
#define ADDRESS 'a'
#define TCP 'T'
#define UDP 'U'
#define PORT 'p'
#define SIZE_BLOCK 's'
#define NUM_BLOCK 'n'
#define TCP_CONNECTION 6
#define UDP_CONNECTION 17

//max and min
#define PORT_MAX 6
#define SERVER_NAME_MAX 25
#define IP_MAX 39 //ipv max is 39, so should be enough

//return codes
#define PORT_ERROR -1

//disable warning for strcpy
#pragma warning(disable:4996)

//prototypes
int validatePort(char* portInput);
void server(void);
char* getIP();
int runClient(int connectionType, char* address, int port, int blockSize, int blockNum);
int validateIP(char* testIP);


int main(int argc, char *argv[])
{
	char port[PORT_MAX] = { "" };
	char* ipaddr = NULL;
	char clientIP[25] = { "" };
	int blockSize = 0;
	int blockNum = 0;
	int connectionType;
	int portNum = 0;


	if (argc == 3)
	{
		if (argv[FIRST_ARG][FIRST_CHAR] == PORT)
		{
			//validate port (make sure its a number)
			if (validatePort(argv[2]) != 0)
			{
				//debug error, not a number
				printf("Port invalid\n");
			}
			else //start server
			{
				strcpy(port, argv[2]); //copy second arg (port num) to 'port' variable

				printf("you are entering: %s as a port!\n", port); //debugging
				server(); //run server
			}

		}
	}
	else
	{
		if (argc == 10)
		{
			
			if (strcmp(argv[1], "-TCP") || strcmp(argv[1], "UDP"))
			{
				//args okay, check specific UDP vs, TCP
				if (strcmp(argv[1],"-TCP") == 0)
				{
					connectionType = TCP_CONNECTION;
				}
				else if (strcmp(argv[1], "-UDP") == 0)
				{
					connectionType = UDP_CONNECTION;
				}
				
			}
			else
			{
				//return fail for argument
			}

			if (strcmp(argv[2], "-a") == 0)
			{
				strcpy(clientIP, argv[3]);
			}
			else
			{
				int i = 0;
				//return fail
			}

			if (strcmp(argv[4], "-p") == 0)
			{
				//validate port (make sure its a number)
				if (validatePort(argv[5]) != 0)
				{
					//debug error, not a number
					printf("Port invalid\n");
				}
				else //start server
				{
					portNum = atoi(argv[5]); //copy second arg (port num) to 'port' variable					
				}
			}
			else
			{
				//return fail
			}

			if (strcmp(argv[6], "-s") == 0)
			{
				blockSize = atoi(argv[7]);
			}
			else
			{
				//return arg fail
			}

			if (strcmp(argv[8], "-n") == 0)
			{
				blockNum = atoi(argv[9]);
			}
			else
			{
				//return arg fail
			}

			runClient(connectionType, clientIP, portNum, blockSize, blockNum);
		}
	}

	//debug for arguments
	for (int i = 0; i < argc; i++)
	{

		printf("Arg #%d: %s\n", i + 1, argv[i]);
	}

	return 0;
	
}



//function that takes in a port as a string and validates it to
//ensure that it only contains numbers
int validatePort(char* portInput)
{
	int portLength = 0;
	int retCode = 0;
	portLength = (int)strlen(portInput); //get length

	//check length of port
	if (portLength > PORT_MAX)
	{
		retCode = PORT_ERROR;
	}
	else
	{
		for (int i = 0; i < portLength; i++)
		{
			if (!isdigit(portInput[i]))
			{
				retCode = PORT_ERROR;
				break;
			}
		}
	}

	return retCode;
}

//this functions runs the server logic to listen for incoming connections
void server(void)
{
	char *serverIP = NULL; //serverIP 
	struct sockaddr_in sock_receive;
	/*struct sockaddr_in sock_receive_tcp;
	struct sockaddr_in sock_receive_udp;*/
	SOCKET message_sock_in;
	struct sockaddr_in sockIn;
	struct sockaddr_in sendAddr;
	int theLength = sizeof(sendAddr);
	int msgLength;
	SOCKET tcpIn;
	SOCKET udpIn;
	int p = 0;
	int totalBytes = 0;
	char buffer[255];
	
	serverIP = getIP(); //getIP function
	if (serverIP != NULL) //error checking if ip was assigned
	{
		printf("ServerIP: %s\n", serverIP);
	}

	sockIn.sin_family = AF_INET;
	sockIn.sin_port = htons(12345); //TODO: add actual port chosen from argv
	sockIn.sin_addr.s_addr = INADDR_ANY;

	//create socket, think this is where you can choose TCP or UDP ('0')
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	//SOCKET tcpSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	int enable = 1;
	/*if (setsockopt(tcpSock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
	{
		int i = WSAGetLastError();
	}*/
	
	//SOCKET udpSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	

	int socketListen = 0;
	int socketConnection = 0;
	int sockRet;

	//get the socket (as an int)
	//TODO: error checking for sockets
	sockRet = bind(serverSocket, (struct sockaddr*)&sockIn, sizeof(sockIn));
	
	
	//sockRet = bind(udpSock, (struct sockaddr*)&sockIn, sizeof(sockIn));

	char messageSnd[100];

	////assign socket to listen
	////TODO: error check
	//listen(serverSocket, 0);
	//
	////listen(udpSock, 0);

	////listen for connections
	//msgLength = sizeof(sock_receive);
	//message_sock_in = accept(serverSocket, (struct sockaddr*) &sock_receive, &msgLength); //wait for incoming connections to socket
	while (1)
	{
		//assign socket to listen
	//TODO: error check
		listen(serverSocket, 0);

		//listen(udpSock, 0);

		//listen for connections
		msgLength = sizeof(sock_receive);
		message_sock_in = accept(serverSocket, (struct sockaddr*) &sock_receive, &msgLength); //wait for incoming connections to socket
		char clientData[10000];

		//msgLength = sizeof(sock_receive);
		//message_sock_in = accept(serverSocket, (struct sockaddr*) &sock_receive, &msgLength); //wait for incoming connections to socket

		if (message_sock_in != INVALID_SOCKET)
		{
			//TODO: get message and parse etc.
			recv(message_sock_in, buffer, sizeof(buffer), 0);			
			//printf("BUFFER: %s\n", buffer);
			char *pass ="P";
			char *fail = "F";
			
			int blockNum;
			int blockSize;

			blockNum = atoi((strrchr(buffer, "-") + 1));
			blockSize = atoi(((strchr(buffer, "-") + 1) - (strrchr(buffer, "-"))));
			

			if (buffer[0] == 'T') //check if handshake is with tcp
			{
				totalBytes = 0;
		
				buffer[0] = '\0';
				send(message_sock_in, pass, strlen(pass) + 1, 0);
				for (int x = 0; x <= blockNum; x++)
				{
					p = recv(message_sock_in, clientData, sizeof(clientData), 0);
					totalBytes = totalBytes + p;
				}
				

				printf("BTYES DOWNLOADED : %d\n", totalBytes);
				
			}
			else if (buffer[0] == 'U')//check if handshake is with udp
			{
				buffer[0] = '\0';
				send(message_sock_in, pass, strlen(pass) + 1, 0);
				//closesocket(serverSocket);
				//create udp socket

				int udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
				sockRet = bind(udpSocket, (struct sockaddr*)&sockIn, sizeof(sockIn));

				p = recvfrom(udpSocket, clientData, sizeof(clientData), 0 ,(const struct sockaddr *)&sendAddr, &theLength);

				if (p == SOCKET_ERROR)
				{
					int i = WSAGetLastError();
					printf("ERROR: %d\n", i);
				}
				//printf("BTYES DOWNLOADED : %d\n", p);

				closesocket(udpSocket);
			}
		}

		
		
		//TODO: exit condition

	}

	WSACleanup();
	
}


/* This fucntion will get and parse the messages from the client
*  I.E. main logic of tests
*/
int getMessage(SOCKET messageSock)
{
	return 0;
}

/* This function gets the IP address for linux and windows and returns a string (pointer to)
*/
char* getIP()
{
	char* myIP = NULL;
	
	
	//windows sockets
	if (PLATFORM_NAME == "windows")
	{
		struct WSAData data;
		char serverName[SERVER_NAME_MAX];

		PHOSTENT serverInfo;

		//get the server ip from the socket and hostname
		if (WSAStartup(0x0202, &data) == 0)
		{
			//get ip of host
			if (gethostname(serverName, sizeof(serverName)) == 0)
			{
				if ((serverInfo = gethostbyname(serverName)) != NULL)
				{
					myIP = (char*)malloc(sizeof(serverInfo));
					strcpy(myIP, inet_ntoa(*(struct in_addr *)*serverInfo->h_addr_list));
				}
			}
		}
	}

	//TODO: get ip for linux

	return myIP;
}

/* This function validates IP addresses to ensure correct format
*  EX: 255.255.255.255
*/
int validateIP(char* testIP)
{
	char* ipToValidate;
	//strcpy(ipToValidate, testIP);
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
	char testRecv[255];
	WSADATA wsaData;
	char *connectionChar;
	connectionChar = (char *)malloc(100);

	char data[100000];
	memset(data, 0, sizeof(data));
	memset(data, 'A', blockSize);

	int * seq = (int *)data;
	int p = 0;
	int totalBytes = 0;
	/*for (int x = 1; x <= blockNum; x++)
	{
		memset(data, x, 1);
	}
*/

	/*int x = 1;
	for (int y = 0; y <= 499; y++)
	{
		data[y] = x;
		x++;

		if (x == 11)
		{
			x = 1;
		}
	}*/
	if (connectionType == UDP_CONNECTION)
	{
		snprintf(connectionChar, 100, "U-%d-%d%c", blockSize, blockNum, '\0');
	}
	else if (connectionType == TCP_CONNECTION)
	{
		snprintf(connectionChar, 100, "T-%d-%d%c", blockSize, blockNum,'\0');
	}
	




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
	send(client_socket, connectionChar, strlen(connectionChar), 0);
	
	//recv response
	recv(client_socket, testRecv, 255, 0);
	//closesocket(client_socket);

	if (strcmp(testRecv, "P") == 0)
	{
		if ((strcmp("T", connectionChar[0])) == 0)
		{
			for (int x = 1; x <= blockNum; x++)
			{
				//(*seq) = x;
				p = send(client_socket, data, strlen(data), 0);
				totalBytes = totalBytes + p;
			}
			printf("TOTAL BYTES: %d", totalBytes);
		}
		else if ((strcmp("U", connectionChar[0])) == 0)
		{
			
			closesocket(client_socket);
			int udpClient = socket(AF_INET, SOCK_DGRAM, 0);

			int p = sendto(udpClient, data, sizeof(data), 0, (const struct sockaddr *)&server, sizeof (server));
			printf("BYTES SENT : %d \n", p);
			closesocket(udpClient);
		}
		else
		{
			printf("ERROR WITH CONNECTION TYPE PLEASE RESTART CLIENT\n");
		}
	}
	else
	{
		printf("ERROR WITH CONNECTION TYPE PLEASE RESTART CLIENT\n");
	}
	free(connectionChar);
	return 0;
}