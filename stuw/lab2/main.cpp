#include <windows.h>
#include <aclapi.h>
#include <sddl.h> 
#include <stdio.h>
#include <sstream>
#include "interaction.h"





void CheckPermissions(char *cPath, HWND hWindow, HWND hAnotherWindow)
{
    if (!GetWindowTextA(hWindow, cPath, MAX_PATH))
    {
        MessageBoxA(hWindow, "Failed to extract path of the file", "Extraction Error", MB_OK);
    }else MessageBoxA(hWindow, "Extracted path to the file", "Extraction Success", MB_OK);


    DWORD dwRes = 0;
    PACL pDACL = NULL;
    PSECURITY_DESCRIPTOR pSD = NULL;
    EXPLICIT_ACCESS ea;

    dwRes = GetNamedSecurityInfoA("D:\\Downloads\\стзв\\systeminfo.txt", SE_FILE_OBJECT,
        DACL_SECURITY_INFORMATION,
        NULL, NULL, &pDACL, NULL, &pSD);
    if (ERROR_SUCCESS != dwRes) 
    {
        MessageBoxA(hWindow, "GetNamedSecurityInfo", "Error", MB_OK);
        //goto Cleanup;
    }else MessageBoxA(hWindow, "GetNamedSecurityInfo", "Success", MB_OK);



    char buf[4096];

    for (DWORD i = 0; i < pDACL->AceCount; ++i)
    {
        LPVOID pAce = NULL;

        GetAce(pDACL, i, &pAce);

        ACE_HEADER* header = (ACE_HEADER*)pAce;

        sprintf_s(buf,
            "ACE #%lu\nType: %u\nFlags: 0x%02X\nSize: %u",
            i,
            header->AceType,
            header->AceFlags,
            header->AceSize);
        MessageBoxA(hWindow, buf, "ACE", MB_OK);

        if (header->AceType == ACCESS_ALLOWED_ACE_TYPE)
        {
            ACCESS_ALLOWED_ACE* ace = (ACCESS_ALLOWED_ACE*)pAce;
            ACCESS_MASK mask = ace->Mask;
            PSID sid = (PSID)&ace->SidStart;

            if (mask & FILE_READ_DATA)
                sprintf_s(buf,
                    "ACE #%lu\nMask : ReadData\n", i, ace->Mask);
                MessageBoxA(hWindow, buf, "ACE ACCESS ALLOWED", MB_OK);

            if (mask & FILE_WRITE_DATA)
                sprintf_s(buf,
                    "ACE #%lu\nMask : WriteData\n", i, ace->Mask);
                MessageBoxA(hWindow, buf, "ACE ACCESS ALLOWED", MB_OK);

            if (mask & FILE_APPEND_DATA)
                sprintf_s(buf,
                    "ACE #%lu\nMask : AData\n", i, ace->Mask);
                MessageBoxA(hWindow, buf, "ACE ACCESS ALLOWED", MB_OK);

            if (mask & FILE_EXECUTE)
                sprintf_s(buf,
                    "ACE #%lu\nMask : EData\n", i, ace->Mask);
                MessageBoxA(hWindow, buf, "ACE ACCESS ALLOWED", MB_OK);

            if (mask & DELETE)
                sprintf_s(buf,
                    "ACE #%lu\nMask : DelData\n", i, ace->Mask);
                MessageBoxA(hWindow, buf, "ACE ACCESS ALLOWED", MB_OK);

            if (mask & READ_CONTROL)
                sprintf_s(buf,
                    "ACE #%lu\nMask : ReadCntrl\n", i, ace->Mask);
                MessageBoxA(hWindow, buf, "ACE ACCESS ALLOWED", MB_OK);

            if (mask & WRITE_DAC)
                sprintf_s(buf,
                    "ACE #%lu\nMask : WriteDAC\n", i, ace->Mask);
                MessageBoxA(hWindow, buf, "ACE ACCESS ALLOWED", MB_OK);

            if (mask & WRITE_OWNER)
                sprintf_s(buf,
                    "ACE #%lu\nMask : Writeowner\n", i, ace->Mask);
                MessageBoxA(hWindow, buf, "ACE ACCESS ALLOWED", MB_OK);

            
        }else if (header->AceType == ACCESS_DENIED_ACE_TYPE)
        {
            ACCESS_DENIED_ACE* ace = (ACCESS_DENIED_ACE*)pAce;
            ACCESS_MASK mask = ace->Mask;
            PSID sid = (PSID)&ace->SidStart;

            sprintf_s(buf,
                "ACE #%lu\nMask : 0x%08lX\n", i, ace->Mask);
            MessageBoxA(hWindow, buf, "ACE ACCESS DENIED", MB_OK);
        }

        //sprintf_s(buf,
        //    "ACE #%lu\nSIDstart : %u\n",i, sid);
        //MessageBoxA(hWindow, buf, "ACE", MB_OK);
    }

    //Cleanup:
    //
    //    if (pSD != NULL)
    //        LocalFree((HLOCAL)pSD);
    //    if (pNewDACL != NULL)
    //        LocalFree((HLOCAL)pNewDACL);
    
        //return dwRes;
      //extracting info about object

    //SID_NAME_USE SIDType;
    //PSECURITY_DESCRIPTOR pNewFileSD;
    //PACL pNewFileDACL;

    //const char* username = "user1";

    //char UserSID[2048];

    //DWORD dwSIDLength = sizeof(UserSID);
    //DWORD dwNewACLSize;

    //if (LookupAccountNameA((LPSTR)NULL, username, UserSID, &dwSIDLength, NULL, NULL, &SIDType))
    //{
    //    MessageBoxA(hWindow, "LookupAccountNameA", " Success", MB_OK);

    //}

    //else MessageBoxA(hWindow, "LookupAccountNameA", "Error", MB_OK);



    //SECURITY_INFORMATION siRequestedInformation;
    //SECURITY_DESCRIPTOR *sdSecurityDescriptor = (SECURITY_DESCRIPTOR*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 100);;
    //DWORD dLengthNeeded = 0;

    //if (GetFileSecurityA("D:\\Downloads\\стзв\\systeminfo.txt", DACL_SECURITY_INFORMATION, sdSecurityDescriptor, 100, &dLengthNeeded))
    //{
    //    MessageBoxA(hWindow, "GetFileSecurityA", " Success", MB_OK);
    //    SetWindowTextA(hAnotherWindow, (LPCSTR)sdSecurityDescriptor->Dacl);
    //    //HeapFree(GetProcessHeap(), 0, sdSecurityDescriptor);
    //}

    //else MessageBoxA(hWindow, "GetFileSecurityA", "Error", MB_OK);
}