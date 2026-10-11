#include "interaction.h"

//TODO:
//- make function to set rights to users: Everyone and Anonymous

wchar_t *GetSid(PSID pSid)
{

    WCHAR name[256];
    WCHAR domain[256];

    DWORD nameSize = sizeof(name);
    DWORD domainSize = sizeof(domain);

    SID_NAME_USE sidNameUse;

    LookupAccountSidW(
        NULL,
        pSid,
        name,
        &nameSize,
        domain,
        &domainSize,
        &sidNameUse
    );
    static wchar_t buf[256];
    swprintf_s(buf, L"\r\n%s", name);

    return buf;
}

void CheckAccessMask(HWND hAnotherWindow, ACCESS_MASK mask)
{
    wchar_t buf[4096];

    if (mask & FILE_READ_DATA)
    {
        swprintf_s(buf,
            L"\r\n✓ReadData");
        SendMessage(hAnotherWindow, EM_SETSEL, -1, -1);
        SendMessageW(hAnotherWindow, EM_REPLACESEL, TRUE, (LPARAM)buf);
    }


    if (mask & FILE_WRITE_DATA)
    {
        swprintf_s(buf,
            L"\r\n✓WriteData");
        SendMessage(hAnotherWindow, EM_SETSEL, -1, -1);
        SendMessage(hAnotherWindow, EM_REPLACESEL, TRUE, (LPARAM)buf);
    }

    if (mask & FILE_APPEND_DATA)
    {
        swprintf_s(buf,
            L"\r\n✓AData");
        SendMessage(hAnotherWindow, EM_SETSEL, -1, -1);
        SendMessage(hAnotherWindow, EM_REPLACESEL, TRUE, (LPARAM)buf);
    }

    if (mask & FILE_EXECUTE)
    {
        swprintf_s(buf,
            L"\r\n✓EData");
        SendMessage(hAnotherWindow, EM_SETSEL, -1, -1);
        SendMessage(hAnotherWindow, EM_REPLACESEL, TRUE, (LPARAM)buf);
    }

    if (mask & DELETE)
    {
        swprintf_s(buf,
            L"\r\n✓DelData");
        SendMessage(hAnotherWindow, EM_SETSEL, -1, -1);
        SendMessage(hAnotherWindow, EM_REPLACESEL, TRUE, (LPARAM)buf);
    }

    if (mask & READ_CONTROL)
    {
        swprintf_s(buf,
            L"\r\n✓ReadCntrl");
        SendMessage(hAnotherWindow, EM_SETSEL, -1, -1);
        SendMessage(hAnotherWindow, EM_REPLACESEL, TRUE, (LPARAM)buf);
    }
    if (mask & WRITE_DAC)
    {
        swprintf_s(buf,
            L"\r\n✓WriteDAC");
        SendMessage(hAnotherWindow, EM_SETSEL, -1, -1);
        SendMessage(hAnotherWindow, EM_REPLACESEL, TRUE, (LPARAM)buf);
    }

    if (mask & WRITE_OWNER)
    {
        swprintf_s(buf,
            L"\r\n✓Writeowner");
        SendMessage(hAnotherWindow, EM_SETSEL, -1, -1);
        SendMessage(hAnotherWindow, EM_REPLACESEL, TRUE, (LPARAM)buf);
    }

}

int CheckPermissions(HWND hWindow, HWND hAnotherWindow)
{
    char cPath[MAX_PATH];

    if (!GetWindowTextA(hWindow, cPath, MAX_PATH))
    {
        MessageBoxA(hWindow, "Enter path to the file/folder", "Extraction Error", MB_OK | MB_ICONEXCLAMATION);
        return 1;
    }

    DWORD dwRes = 0;
    PACL pDACL = NULL;
    PSECURITY_DESCRIPTOR pSD = NULL;
    EXPLICIT_ACCESS ea;

    dwRes = GetNamedSecurityInfoA(
        cPath,
        SE_FILE_OBJECT,
        DACL_SECURITY_INFORMATION,
        NULL, 
        NULL, 
        &pDACL, 
        NULL, 
        &pSD);

    if (dwRes != ERROR_SUCCESS)
    {
        MessageBoxA(hWindow, "GetNamedSecurityInfo()", "Error", MB_OK | MB_ICONEXCLAMATION);
        //goto Cleanup;
        return 1;
    }

    SendMessageW(hAnotherWindow, EM_SETSEL, -1, -1);
    SendMessageW(hAnotherWindow, EM_REPLACESEL, TRUE, (LPARAM)L"        --- PERMISSIONS --");
    

    wchar_t buf[4096];

    for (DWORD i = 0; i < pDACL->AceCount; ++i)
    {
        LPVOID pAce = NULL;

        GetAce(pDACL, i, &pAce);

        ACE_HEADER* header = (ACE_HEADER*)pAce;

        swprintf_s(
            buf,
            L"\r\n\r\nACE #%lu\r\nType: %u\r\nFlags: 0x%02X\r\nSize: %u\n",
            i,
            header->AceType,
            header->AceFlags,
            header->AceSize);

        SendMessageW(hAnotherWindow, EM_SETSEL, -1, -1);
        SendMessageW(hAnotherWindow, EM_REPLACESEL, TRUE, (LPARAM)buf);

        ACCESS_MASK mask = 0;
        PSID sid = nullptr;
            
        if (header->AceType == ACCESS_DENIED_ACE_TYPE)
        {
            ACCESS_DENIED_ACE* ace = (ACCESS_DENIED_ACE*)pAce;
            mask = ace->Mask;
            sid = (PSID)&ace->SidStart;
        }
        else if (header->AceType == ACCESS_ALLOWED_ACE_TYPE)
        {
            ACCESS_ALLOWED_ACE* ace = (ACCESS_ALLOWED_ACE*)pAce;
            mask = ace->Mask;
            sid = (PSID)&ace->SidStart;
        }
        else {
            SendMessageW(hAnotherWindow, EM_SETSEL, -1, -1);
            SendMessageW(hAnotherWindow, EM_REPLACESEL, TRUE, (LPARAM)L"\r\nUnsupported ACE type.");
            continue;
        }

        SendMessageW(hAnotherWindow, EM_SETSEL, -1, -1);
        SendMessageW(hAnotherWindow, EM_REPLACESEL, TRUE, (LPARAM)L"\r\n\r\[+]User:");
        wchar_t* user = GetSid(sid);
        swprintf_s(buf, user);
        SendMessageW(hAnotherWindow, EM_REPLACESEL, TRUE, (LPARAM)buf);


        SendMessageW(hAnotherWindow, EM_SETSEL, -1, -1);
        SendMessageW(hAnotherWindow, EM_REPLACESEL, TRUE, (LPARAM)L"\r\n\r\n[+]Permissions:");
        CheckAccessMask(hAnotherWindow, mask);
    }
    return 0;
}



void SetAttribute(wchar_t *object, int attr)
{
    if (SetFileAttributes(object, attr))
    {
        MessageBoxA(NULL, "Success", "SetFileAttributes", MB_OK | MB_ICONEXCLAMATION);
        //SetFileAttributes(object, FILE_ATTRIBUTE_NORMAL);
    }
    else
    {
        MessageBoxA(NULL, "Access denied", "SetFileAttributes", MB_OK | MB_ICONEXCLAMATION);
    }
}

void CheckFileAttr(wchar_t* filename, HWND hOut)
{
    wchar_t buf[4096];
    SetWindowTextW(hOut, L" ");
    int result = GetFileAttributesW(filename);
    if ( result == INVALID_FILE_ATTRIBUTES)
    {
        MessageBoxA(NULL, "Access denied", "GetFileAttributesW", MB_OK | MB_ICONEXCLAMATION);
    }
    else
    {
        if (result & FILE_ATTRIBUTE_ARCHIVE)
        {
            swprintf_s(buf,
                L"\r\n* Archive");
            SendMessage(hOut, EM_SETSEL, -1, -1);
            SendMessageW(hOut, EM_REPLACESEL, TRUE, (LPARAM)buf);
        }
        if (result & FILE_ATTRIBUTE_DIRECTORY)
        {
            swprintf_s(buf,
                L"\r\n* Directory");
            SendMessage(hOut, EM_SETSEL, -1, -1);
            SendMessageW(hOut, EM_REPLACESEL, TRUE, (LPARAM)buf);
        }
        if (result & FILE_ATTRIBUTE_READONLY)
        {
            swprintf_s(buf,
                L"\r\n* Readonly");
            SendMessage(hOut, EM_SETSEL, -1, -1);
            SendMessageW(hOut, EM_REPLACESEL, TRUE, (LPARAM)buf);
        }
        if (result & FILE_ATTRIBUTE_COMPRESSED)
        {
            swprintf_s(buf,
                L"\r\n* Compressed");
            SendMessage(hOut, EM_SETSEL, -1, -1);
            SendMessageW(hOut, EM_REPLACESEL, TRUE, (LPARAM)buf);
        }
        if (result & FILE_ATTRIBUTE_HIDDEN)
        {
            swprintf_s(buf,
                L"\r\n* Hidden");
            SendMessage(hOut, EM_SETSEL, -1, -1);
            SendMessageW(hOut, EM_REPLACESEL, TRUE, (LPARAM)buf);
        }
        if (result & FILE_ATTRIBUTE_SYSTEM)
        {
            swprintf_s(buf,
                L"\r\n* System");
            SendMessage(hOut, EM_SETSEL, -1, -1);
            SendMessageW(hOut, EM_REPLACESEL, TRUE, (LPARAM)buf);
        }
        if (result & FILE_ATTRIBUTE_COMPRESSED)
        {
            swprintf_s(buf,
                L"\r\n* Compressed");
            SendMessage(hOut, EM_SETSEL, -1, -1);
            SendMessageW(hOut, EM_REPLACESEL, TRUE, (LPARAM)buf);
        }
        if (result & FILE_ATTRIBUTE_NORMAL)
        {
            swprintf_s(buf,
                L"\r\n* Normal (no attributes are set)");
            SendMessage(hOut, EM_SETSEL, -1, -1);
            SendMessageW(hOut, EM_REPLACESEL, TRUE, (LPARAM)buf);
        }
        if (result & FILE_ATTRIBUTE_TEMPORARY)
        {
            swprintf_s(buf,
                L"\r\n* Temporary");
            SendMessage(hOut, EM_SETSEL, -1, -1);
            SendMessageW(hOut, EM_REPLACESEL, TRUE, (LPARAM)buf);
        }
    }
}

void SetDirAttribute(wchar_t* object, int attr)
{
    if (SetFileAttributes(object, attr))
    {
        MessageBoxA(NULL, "Success : attribute changed", "SetFileAttributes", MB_OK | MB_ICONEXCLAMATION);

    }
    else
    {
        MessageBoxA(NULL, "Access denied", "SetFileAttributes", MB_OK | MB_ICONEXCLAMATION);
    }
}


void TraverseFolder(wchar_t* dirname, HWND hOut)
{
    wchar_t searchPath[MAX_PATH];
    swprintf_s(searchPath, L"%s\\*.*", dirname);

    WIN32_FIND_DATA findData;
    HANDLE hFind = FindFirstFileW(searchPath, &findData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        MessageBoxA(NULL, "Failed to traverse folder", "FindFirstFileW", MB_OK | MB_ICONEXCLAMATION);
    }
    else
    {
        do
        {
            wchar_t buf[4096];
            swprintf_s(buf, L"\r\n - %s", findData.cFileName);
            SendMessage(hOut, EM_SETSEL, -1, -1);
            SendMessage(hOut, EM_REPLACESEL, TRUE, (LPARAM)buf);

            wchar_t fullpath[MAX_PATH];
            swprintf_s(fullpath, L"%s\\%s", dirname, findData.cFileName);
            DisplayOwner(fullpath, hOut);
        } while (FindNextFileW(hFind, &findData));
        FindClose(hFind);
    }
}

void DisplayOwner(wchar_t* object, HWND hOut)
{
    PSID pOwnerSid = NULL;
    PSECURITY_DESCRIPTOR pSD = NULL;

    DWORD dwRes = GetNamedSecurityInfoW(
        object,
        SE_FILE_OBJECT,
        OWNER_SECURITY_INFORMATION,
        &pOwnerSid,
        NULL,
        NULL,
        NULL,
        &pSD
    );

    if (dwRes != ERROR_SUCCESS)
    {
        MessageBoxA(NULL, "Failed to get owner", "GetNamedSecurityInfoW()", MB_OK | MB_ICONEXCLAMATION);
        return;
    }

    WCHAR accountName[256];
    WCHAR domainName[256];
    DWORD cchAccount = sizeof(accountName) / sizeof(WCHAR);
    DWORD cchDomain = sizeof(domainName) / sizeof(WCHAR);
    SID_NAME_USE eUse;

    if (LookupAccountSidW(NULL, pOwnerSid, accountName, &cchAccount, domainName, &cchDomain, &eUse))
    {
        wchar_t buf[4096];
        swprintf_s(buf, L"\r\n Owner : %s\\%s", domainName, accountName);
        SendMessage(hOut, EM_SETSEL, -1, -1);
        SendMessage(hOut, EM_REPLACESEL, TRUE, (LPARAM)buf);
    }
    else
    {
        MessageBoxA(NULL, "Failed to get owner", "LookupAccountSidW()", MB_OK | MB_ICONEXCLAMATION);
    }

    if (pSD != NULL)
    {
        LocalFree((HLOCAL)pSD);
    }
}