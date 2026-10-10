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


void CheckPermissions(char *cPath, HWND hWindow, HWND hAnotherWindow)
{
    if (!GetWindowTextA(hWindow, cPath, MAX_PATH))
    {
        MessageBoxA(hWindow, "Failed to extract path to the file", "Extraction Error", MB_OK);
    }//else MessageBoxA(hWindow, "Extracted path to the file", "Extraction Success", MB_OK);


    DWORD dwRes = 0;
    PACL pDACL = NULL;
    PSECURITY_DESCRIPTOR pSD = NULL;
    EXPLICIT_ACCESS ea;

    dwRes = GetNamedSecurityInfoA(
        "D:\\Downloads\\стзв\\systeminfo.txt", 
        SE_FILE_OBJECT,
        DACL_SECURITY_INFORMATION,
        NULL, 
        NULL, 
        &pDACL, 
        NULL, 
        &pSD);

    if (dwRes != ERROR_SUCCESS)
    {
        MessageBoxA(hWindow, "GetNamedSecurityInfo()", "Error", MB_OK);
        //goto Cleanup;
    }//else MessageBoxA(hWindow, "GetNamedSecurityInfo()", "Success", MB_OK);

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
}


LSA_HANDLE GetPolicyHandle()
{
    LSA_OBJECT_ATTRIBUTES ObjectAttributes = {};

    LSA_UNICODE_STRING lusSystemName = {};
    WCHAR SystemName[] = TARGET_SYSTEM_NAME;
    USHORT SystemNameLength;

    LSA_HANDLE lsahPolicyHandle = nullptr;
    NTSTATUS ntsResult;

    ZeroMemory(&ObjectAttributes, sizeof(ObjectAttributes));

    SystemNameLength = wcslen(SystemName);

    lusSystemName.Buffer = SystemName;
    lusSystemName.Length = SystemNameLength * sizeof(WCHAR);
    lusSystemName.MaximumLength = (SystemNameLength + 1) * sizeof(WCHAR);

    ntsResult = LsaOpenPolicy(
        &lusSystemName,  
        &ObjectAttributes, 
        POLICY_LOOKUP_NAMES | POLICY_CREATE_ACCOUNT,
        &lsahPolicyHandle
    );

    if (ntsResult != STATUS_SUCCESS)
    {
        wprintf(L"OpenPolicy returned %lu\n", LsaNtStatusToWinError(ntsResult));
        return nullptr;
    }
    return lsahPolicyHandle;
}


LSA_UNICODE_STRING CreateUserRights()
{
    LSA_UNICODE_STRING rights = {};
    WCHAR wPrivilege[] = L"SE_SYSTEMTIME_NAME";
    USHORT uPrivilegeLength;

    uPrivilegeLength = wcslen(wPrivilege);

    rights.Buffer = wPrivilege;
    rights.Length = uPrivilegeLength * sizeof(WCHAR);
    rights.MaximumLength = (uPrivilegeLength + 1) * sizeof(WCHAR);

    return rights;
}


void SetPrivilege()
{
    LSA_HANDLE PolicyHandle = GetPolicyHandle();;

    PSID pSid = nullptr;
    DWORD cbSid = 0;
    WCHAR* ReferencedDomainName = nullptr;
    DWORD cchReferencedDomainName = 0;
    SID_NAME_USE peUse;

    LSA_UNICODE_STRING UserRights;
    ULONG CountOfRights = 1;

    LookupAccountNameW(
        TARGET_SYSTEM_NAME, 
        L"user1", 
        pSid, 
        &cbSid, 
        ReferencedDomainName, 
        &cchReferencedDomainName, 
        &peUse);

    ReferencedDomainName = new WCHAR[cchReferencedDomainName];

    LookupAccountNameW(
        TARGET_SYSTEM_NAME,
        L"user1",
        pSid,
        &cbSid,
        ReferencedDomainName,
        &cchReferencedDomainName,
        &peUse);


    UserRights = CreateUserRights();

    NTSTATUS status = LsaAddAccountRights(PolicyHandle, pSid, &UserRights, 1);
    if (status != STATUS_SUCCESS)
    {
        MessageBoxA(NULL, "LsaAddAccountRights() : Failed to assign rights.", "LsaAddAccountRights()", MB_OK);
        return;
    }
    delete[] ReferencedDomainName;
    LsaClose(PolicyHandle);

}


DWORD AddAceToObjectsSecurityDescriptor(
    LPTSTR pszObjName,          // name of object
    SE_OBJECT_TYPE ObjectType,  // type of object
    LPTSTR pszTrustee,          // trustee for new ACE
    TRUSTEE_FORM TrusteeForm,   // format of trustee structure
    DWORD dwAccessRights,       // access mask for new ACE
    ACCESS_MODE AccessMode     // type of ACE
    //DWORD dwInheritance         // inheritance flags for new ACE
)
{
    DWORD dwRes = 0;
    PACL pOldDACL = NULL, pNewDACL = NULL;
    PSECURITY_DESCRIPTOR pSD = NULL;
    EXPLICIT_ACCESS ea;

    if (NULL == pszObjName)
        return ERROR_INVALID_PARAMETER;


    dwRes = GetNamedSecurityInfo(pszObjName, ObjectType,
        DACL_SECURITY_INFORMATION,
        NULL, NULL, &pOldDACL, NULL, &pSD);
    if (ERROR_SUCCESS != dwRes) {
        printf("GetNamedSecurityInfo Error %u\n", dwRes);
        goto Cleanup;
    }

    ZeroMemory(&ea, sizeof(EXPLICIT_ACCESS));
    ea.grfAccessPermissions = dwAccessRights;
    ea.grfAccessMode = AccessMode;
    //ea.grfInheritance = dwInheritance;
    ea.Trustee.TrusteeForm = TrusteeForm;
    ea.Trustee.ptstrName = pszTrustee;

    dwRes = SetEntriesInAcl(1, &ea, pOldDACL, &pNewDACL);
    if (ERROR_SUCCESS != dwRes) {
        printf("SetEntriesInAcl Error %u\n", dwRes);
        goto Cleanup;
    }

    dwRes = SetNamedSecurityInfo(pszObjName, ObjectType,
        DACL_SECURITY_INFORMATION,
        NULL, NULL, pNewDACL, NULL);
    if (ERROR_SUCCESS != dwRes) {
        printf("SetNamedSecurityInfo Error %u\n", dwRes);
        goto Cleanup;
    }

Cleanup:

    if (pSD != NULL)
        LocalFree((HLOCAL)pSD);
    if (pNewDACL != NULL)
        LocalFree((HLOCAL)pNewDACL);

    return dwRes;
}

void SetPermissions(wchar_t *pszObjName, wchar_t *pszTrustee, DWORD dwAccessRights)
{
    //wchar_t pszObjName[] = L"D:\\Downloads\\стзв\\systeminfo.txt";
    SE_OBJECT_TYPE ObjectType = SE_FILE_OBJECT;
    //wchar_t pszTrustee[] = L"user1";
    TRUSTEE_FORM TrusteeForm = TRUSTEE_IS_NAME;
    //DWORD dwAccessRights = SPECIFIC_RIGHTS_ALL;
    ACCESS_MODE AccessMode = SET_ACCESS;

    AddAceToObjectsSecurityDescriptor(pszObjName, ObjectType, pszTrustee, TrusteeForm, dwAccessRights, AccessMode);

}
