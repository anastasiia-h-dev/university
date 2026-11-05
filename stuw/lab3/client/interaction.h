#pragma once
#include <WinSock2.h>
#include <ws2tcpip.h>

#include <windows.h>
#include <ntsecapi.h>
#include <aclapi.h>
#include <sddl.h> 
#include <stdio.h>
#include <sstream>
#include <vector>
#include <ntstatus.h>


#define SEND 1
#define CONNECT 2
#define CHOOSE_OP 3
#define CHOOSE_PROTOCOL 4
#define IDK 5


SOCKET Connect(const char* ip, int port, HWND hLog);
void SendRequest(int sockfd, char* data, HWND hOut);