#include "interaction.h"

#define MAX_REQUESTS 10
DWORD dwThreadID[10];


int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET sockfd; //'s' in metodychka
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		return 1;
	sockfd = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);

	struct sockaddr_in server;
	//server.sin_addr.s_addr = inet_addr(INADDR_ANY);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_family = AF_INET;
	server.sin_port = htons(8981);


	//main thread listens, child threads connect
	bind(sockfd, (SOCKADDR *)&server, sizeof(server));
	listen(sockfd, MAX_REQUESTS);

	while (true)
	{
		if()
		{
			WorkerThread(sockfd,);

		}
	}
	//if (connect(sockfd, (struct sockaddr*)&server, sizeof(server)) < 0)
	//	return 3;
	return 0;
}