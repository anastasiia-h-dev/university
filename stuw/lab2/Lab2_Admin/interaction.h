#pragma once
#include <windows.h>
#include <ntsecapi.h>
#include <aclapi.h>
#include <sddl.h> 
#include <stdio.h>
#include <sstream>
#include <vector>
#include <ntstatus.h>

#define READ_CONTROL                     (0x00020000L)
#define WRITE_DAC                        (0x00040000L)
#define WRITE_OWNER                      (0x00080000L)
#define STANDARD_RIGHTS_REQUIRED         (0x000F0000L)

#define TARGET_SYSTEM_NAME L"ASUS_F15"

//buttons
#define PUSHBUTTON 1
#define ADVANCED 2
#define ID_CHILD 3
#define APPLY_TO_FILE 4
#define APPLY_TO_DIR 5

//checkboxes
#define WRITE 101
#define READ 102
#define CREATE 103

#define DIR_READ_OWNER 104
#define DIR_CREATE 105
#define DIR_WRITE_ATTR 106
#define DIR_READ_PERM 107


void CreateChildWindow(HWND hParent);
int CheckPermissions(HWND hWindow, HWND hAnotherWindow);

void SetPermissions(wchar_t* pszObjName, wchar_t* pszTrustee, DWORD dwAccessRights);

int ExtractText(HWND hWindow1, wchar_t* out);
ACCESS_MASK CheckFileMask(HWND hCheckbox);
ACCESS_MASK CheckDirMask(HWND hCheckbox);
