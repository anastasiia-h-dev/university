#pragma once
#include <windows.h>
#include <WinSock2.h>
#include <stdio.h>
#include <vector>


void WorkerThread(int sockfd, DWORD dwThreadID, char* arg);