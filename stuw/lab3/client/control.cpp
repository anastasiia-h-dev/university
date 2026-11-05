#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "interaction.h"


SOCKET Connect(const char* ip, int port, HWND hLog)
{

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET sockfd;

	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in server;
	server.sin_addr.s_addr = inet_addr(ip);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);


	if (connect(sockfd, (struct sockaddr*)&server, sizeof(server)) < 0)
	{
		closesocket(sockfd);
		return INVALID_SOCKET;
	}
	return sockfd;
}


void SendRequest(int sockfd, char* data,HWND hOut)
{
	send(sockfd, data, strlen(data), 0);

	char response[4096];
	int bytes = recv(sockfd, response, sizeof(response) - 1, 0);
	response[bytes] = '\0';
	SetWindowTextA(hOut, response);
}