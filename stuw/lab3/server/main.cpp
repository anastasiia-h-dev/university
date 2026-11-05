#pragma once
#include <WinSock2.h>

#include <windows.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <sstream>
#include <climits>
#include <time.h>


#pragma comment(lib, "ws2_32.lib")

#define MAX_REQUESTS 10
#define PORT 8981
#define BUFSIZE 8192

void log(const char* msg)
{
	time_t now = time(NULL);
	struct tm* t = localtime(&now);

	char time[128];
	sprintf(time, "\n%d:%d:%d %d:%d:%d %s", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
										t->tm_hour, t->tm_min, t->tm_sec,
										msg);
	printf(time);
	return;
}

std::vector<SOCKET> clients;

std::string ProcessNumbers(const char* input)
{
	std::stringstream ss(input);
	int value;
	int max_val = INT_MIN;
	bool found = false;

	while (ss >> value)
	{
		if (!found || value > max_val)
		{
			max_val = value;
			found = true;
		}
	}

	if (!found)
		return "Error: no valid integers received.\n";

	return "Max value: " + std::to_string(max_val) + "\n";
}


int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET sockfd; //'s' in metodychka
	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockfd < 0)
		log("Failed to create socket");
	//sockfd = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);

	u_long non_blocking = 1;
	ioctlsocket(sockfd, FIONBIO, &non_blocking);

	struct sockaddr_in server;
	//server.sin_addr.s_addr = inet_addr(INADDR_ANY);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);


	//main thread listens, child threads connect
	bind(sockfd, (SOCKADDR*)&server, sizeof(server));
	listen(sockfd, MAX_REQUESTS);


	while (true)
	{
		fd_set read_fds;
		FD_ZERO(&read_fds);

		FD_SET(sockfd, &read_fds);

		for (SOCKET client : clients)
		{
			FD_SET(client, &read_fds);
		}

		timeval timeout;
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;

		int activity = select(0, &read_fds, NULL, NULL, &timeout);
		if (FD_ISSET(sockfd, &read_fds))
		{
			sockaddr_in client_addr;
			int addr_len = sizeof(client_addr);
			SOCKET new_sock = accept(sockfd, (SOCKADDR*)&client_addr, &addr_len);


			if (new_sock != INVALID_SOCKET)
			{
				ioctlsocket(new_sock, FIONBIO, &non_blocking);
				clients.push_back(new_sock);
				log("Client connected");
			}
		}

		char request[BUFSIZE];
		for (int i = 0; i < clients.size(); i++)
		{
				SOCKET client_sock = clients[i];
				if (FD_ISSET(client_sock, &read_fds))
				{
					int bytes_read = recv(client_sock, request, sizeof(request) - 1, 0);

					if (bytes_read > 0)
					{
						request[bytes_read] = '\0';
						std::string response = ProcessNumbers(request);
						send(client_sock, response.c_str(), (int)response.length(), 0);
					}
					else {
						log("Client disconnected");
						closesocket(client_sock);
						clients.erase(clients.begin() + i);
						i--;
					}
				}
		}
			
	}
	for (SOCKET client : clients) closesocket(client);

	closesocket(sockfd);
	WSACleanup();

	return 0;
}