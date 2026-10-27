#include "interaction.h"

#define MAX_BUF 8192

DWORD WINAPI ClientThreadEntry(LPVOID arg)
{
	char *received_string = (char*)arg;
	std::vector<int> numbers(strlen(received_string));
	char* temp = (char*)calloc(4096, sizeof(char*));

	for (int i = 0; i < strlen(received_string); i++) 
	{
		if (received_string[i] == (char)" ")
		{ 
			numbers.push_back(temp - '0');
			temp = (char*)calloc(4096, sizeof(char));
		}
		strcat(temp, received_string[i]);
	}

	if (numbers.size() == 0) return -1;

	int max = numbers[0];
	for (int i = 0; i < numbers.size(); i++)
	{
		if (numbers[i] > max) max = numbers[i];
	}
	return 0;
}

void WorkerThread(int sockfd, DWORD dwThreadID, char* arg)
{
	char request[MAX_BUF];
	//recv(sockfd, request, 100, 0);

	CreateThread(NULL, 0, &ClientThreadEntry, (LPVOID)arg, 0, &dwThreadID);
}