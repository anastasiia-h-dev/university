#pragma once
#include <windows.h>
#include <ntsecapi.h>
#include <aclapi.h>
#include <sddl.h> 
#include <stdio.h>
#include <sstream>
#include <vector>
#include <ntstatus.h>
#include <wincred.h>

#define TARGET_SYSTEM_NAME L"ASUS_F15"

//buttons
#define CHECK_ATTR 1
#define SET_ATTR 2
#define LIST 3
#define CHECK_PERM 4 



//checkboxes
#define WRITE 101
#define READ 102
#define CREATE 103

#define DIR_READ_OWNER 104
#define DIR_CREATE 105
#define DIR_WRITE_ATTR 106
#define DIR_READ_PERM 107

//child
#define ADVANCED 22
#define ID_CHILD 23
#define APPLY_TO_FILE 24
#define APPLY_TO_DIR 25

int CheckPermissions(HWND hWindow, HWND hAnotherWindow);

int ExtractText(HWND hWindow1, wchar_t* out);

void CheckFileAttr(wchar_t* filename, HWND hOut);
void SetAttribute(wchar_t* object, int attr);
void TraverseFolder(wchar_t* dirname, HWND hOut);
DWORD ParseAttribute(wchar_t* attr);
void DisplayOwner(wchar_t* object, HWND hOut);
void SetPermissions(wchar_t* pszObjName, wchar_t* pszTrustee, DWORD dwAccessRights);
void RequestRights(HWND hWnd, wchar_t* wObject, wchar_t* pszTrustee, ACCESS_MASK mask);
ACCESS_MASK CheckFileMask(HWND hCheckbox);
ACCESS_MASK CheckDirMask(HWND hCheckbox);
DWORD AddAceToObjectsSecurityDescriptor(
    LPTSTR pszObjName,          // name of object
    SE_OBJECT_TYPE ObjectType,  // type of object
    LPTSTR pszTrustee,          // trustee for new ACE
    TRUSTEE_FORM TrusteeForm,   // format of trustee structure
    DWORD dwAccessRights,       // access mask for new ACE
    ACCESS_MODE AccessMode     // type of ACE
    //DWORD dwInheritance         // inheritance flags for new ACE
);

//creating child gui
void RegisterChildClass(void);
LRESULT CALLBACK PanelProc(HWND hWnd, UINT msg,
    WPARAM wParam, LPARAM lParam);
void CreateChildWindow(HWND hParent);
