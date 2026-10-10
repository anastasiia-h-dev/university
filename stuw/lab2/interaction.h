#pragma once
#include <windows.h>
#include <ntsecapi.h>
#include <aclapi.h>
#include <sddl.h> 
#include <stdio.h>
#include <sstream>
#include <vector>
#include <ntstatus.h>

#define DELETE                           (0x00010000L)
#define READ_CONTROL                     (0x00020000L)
#define WRITE_DAC                        (0x00040000L)
#define WRITE_OWNER                      (0x00080000L)
#define SYNCHRONIZE                      (0x00100000L)

#define STANDARD_RIGHTS_REQUIRED         (0x000F0000L)

#define STANDARD_RIGHTS_READ             (READ_CONTROL)
#define STANDARD_RIGHTS_WRITE            (READ_CONTROL)
#define STANDARD_RIGHTS_EXECUTE          (READ_CONTROL)

#define STANDARD_RIGHTS_ALL              (0x001F0000L)

#define SPECIFIC_RIGHTS_ALL              (0x0000FFFFL)


#define TARGET_SYSTEM_NAME L"ASUS_F15"


#define WRITE 101
#define READ 102
#define CREATE 103

typedef struct
{

}DACLList;

void CreateChildWindow(HWND hParent);
void CheckPermissions(char* cPath, HWND hWindow, HWND hAnotherWindow);

void SetPermissions(wchar_t* pszObjName, wchar_t* pszTrustee, DWORD dwAccessRights);

void ExtractText(HWND hWindow1, wchar_t* out);
ACCESS_MASK CheckCheckbox(HWND hCheckbox);
