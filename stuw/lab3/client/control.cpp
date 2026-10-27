#include "interaction.h"

#define IP_ADDR "192.168.11.141"

int Connect(int port)
{

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET sockfd;

	sockfd = (AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server;
	server.sin_addr.s_addr = inet_addr(IP_ADDR);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);


	if (connect(sockfd, (struct sockaddr*)&server, sizeof(server)) < 0)
		return 3;
}


void SendRequest(int sockfd, char* data, HWND hIn, HWND hOut)
{
	send(sockfd, data, strlen(data), 0);

	char response[4096];
	recv(sockfd, response, strlen(response), 0);

	//char *buf[4096];
	//GetText(hIn, buf);
	//SendMessage(hOut, )
}