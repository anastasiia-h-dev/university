#pragma once
#include <windows.h>
#include <ntsecapi.h>
#include <aclapi.h>
#include <sddl.h> 
#include <stdio.h>
#include <sstream>
#include <vector>
#include <ntstatus.h>

#define TARGET_SYSTEM_NAME L"ASUS_F15"

//buttons
#define CHECK_ATTR 1
#define SET_ATTR 2
#define LIST 3
#define CHECK_PERM 4 



int CheckPermissions(HWND hWindow, HWND hAnotherWindow);

int ExtractText(HWND hWindow1, wchar_t* out);

void CheckFileAttr(wchar_t* filename, HWND hOut);
void SetAttribute(wchar_t* object, int attr);
void TraverseFolder(wchar_t* dirname, HWND hOut);
DWORD ParseAttribute(wchar_t* attr);
void DisplayOwner(wchar_t* object, HWND hOut);