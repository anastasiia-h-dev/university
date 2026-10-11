

#include "interaction.h"


HWND hPath, hTextContents, hAttribute;
HWND hUser, hGroup, hObject;
HWND ReadCheck, WriteCheck;

DWORD dwFlag;

const wchar_t* CLASS_NAME = L"Desktop_Window";
wchar_t pszObjName[MAX_PATH];
wchar_t pszTrustee[256];
wchar_t attr[256];
DWORD dwAccessRights;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void AddButton(HWND hWnd);
void AddStatic(HWND hWnd);
void AddEdit(HWND hWnd);

void AddButtonChild(HWND hWnd);
void AddStaticChild(HWND hWnd);
void AddEditChild(HWND hWnd);
void AddCheckBox(HWND hWnd);


int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    WNDCLASS _class = { 0 };
    
    _class.lpfnWndProc = WndProc;
    _class.hInstance = hInstance;
    _class.hCursor = LoadCursor(NULL, IDC_ARROW);
    _class.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    _class.lpszClassName = CLASS_NAME;

    if (!RegisterClass(&_class))
    {
        MessageBoxW(NULL,
            L"Call to RegisterClass failed!",
            L"Failed",
            NULL);
        return 1;
    }

    HWND hWnd = CreateWindow(
        CLASS_NAME,
        L"Lab2 Client app",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        100, 100,
        375, 650,
        0,
        0,
        hInstance,
        0
    );
    //::ShowWindow(hWnd, nCmdShow);
    //::UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        AddButton(hWnd);
        AddStatic(hWnd);
        AddEdit(hWnd);
        RegisterChildClass();

        
        break;
    case WM_COMMAND:
        switch (wParam) {
        case CHECK_ATTR:
            SetWindowTextW(hTextContents, NULL);
            ExtractText(hPath, pszObjName);

            CheckFileAttr(pszObjName, hTextContents);
            break;
        case SET_ATTR:
            ExtractText(hPath, pszObjName);
            ExtractText(hAttribute, attr);
            dwFlag = ParseAttribute(attr);
            SetAttribute(pszObjName, dwFlag);
            break;
        case LIST:
            ExtractText(hPath, pszObjName);
            TraverseFolder(pszObjName, hTextContents);
            break;
        case ADVANCED:
            //MessageBoxA(hObject, "Enter path to the file/folder", "Path error", MB_OK | MB_ICONEXCLAMATION);

            CreateChildWindow(hWnd);
            break;

        case CHECK_PERM:
            SetWindowTextW(hTextContents, NULL);
            CheckPermissions(hPath, hTextContents);

            break;
        }


            break;
        

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;

}


void AddButton(HWND hWnd) {
    CreateWindow(
        L"BUTTON",
        L"Check Attributes",
        WS_TABSTOP | BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD,
        220, 60,
        130, 20,
        hWnd,
        (HMENU)CHECK_ATTR,
        NULL,
        NULL
    );

    CreateWindow(
        L"BUTTON",
        L"List",
        WS_TABSTOP | BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD,
        160, 60,
        50, 20,
        hWnd,
        (HMENU)LIST,
        NULL,
        NULL
    );

    CreateWindow(
        L"BUTTON",
        L"Check Permissions",
        WS_TABSTOP | BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD,
        10, 60,
        140, 20,
        hWnd,
        (HMENU)CHECK_PERM,
        NULL,
        NULL
    );

    CreateWindow(
        L"BUTTON",
        L"Set Attribute",
        WS_TABSTOP | BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD,
        200, 505,
        150, 20,
        hWnd,
        (HMENU)SET_ATTR,
        NULL,
        NULL
    );

    CreateWindow(
        L"BUTTON",
        L"Advanced",
        WS_TABSTOP | BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD,
        200, 540,
        150, 20,
        hWnd,
        (HMENU)ADVANCED,
        NULL,
        NULL
    );
}

void AddStatic(HWND hWnd) {
    CreateWindow(
        L"STATIC",
        L"Enter path to the object:",
        WS_VISIBLE | WS_CHILD,
        10, 10,
        240, 20,
        hWnd,
        NULL,
        NULL,
        NULL
    );

    CreateWindow(
        L"STATIC",
        L"Permissions : ",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        10, 85,
        340, 20,
        hWnd,
        NULL,
        NULL,
        NULL
    );
}

void AddEdit(HWND hWnd) {
    hPath = CreateWindow(
        L"EDIT",
        L"",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        10, 35,
        340, 20,
        hWnd,
        NULL,
        NULL,
        NULL
    );

    hTextContents = CreateWindow(
        L"EDIT",
        L"",
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | WS_VSCROLL,
        10, 110,
        340, 340,
        hWnd,
        NULL,
        NULL,
        NULL
    );

    hAttribute = CreateWindow(
        L"EDIT",
        L"",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        10, 480,
        340, 20,
        hWnd,
        NULL,
        NULL,
        NULL
    );
}





///CHILD WINDOW


void AddButtonChild(HWND hWnd) {
    CreateWindow(
        L"BUTTON",
        L"Apply",
        WS_TABSTOP | BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD,
        10, 225,
        100, 20,
        hWnd,
        (HMENU)APPLY_TO_FILE,
        NULL,
        NULL
    );
    CreateWindow(
        L"BUTTON",
        L"Apply",
        WS_TABSTOP | BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD,
        10, 380,
        100, 20,
        hWnd,
        (HMENU)APPLY_TO_DIR,
        NULL,
        NULL
    );
}

void AddStaticChild(HWND hWnd) {
    CreateWindow(
        L"STATIC",
        L"Enter username/group:",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        10, 10,
        200, 20,
        hWnd,
        NULL,
        NULL,
        NULL);

    CreateWindow(
        L"STATIC",
        L"Enter path to the file/folder : ",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        10, 65,
        200, 20,
        hWnd,
        NULL,
        NULL,
        NULL);

    CreateWindow(
        L"STATIC",
        L"File permissions : ",
        WS_VISIBLE | WS_CHILD,
        10, 125,
        200, 20,
        hWnd,
        NULL,
        NULL,
        NULL);

    CreateWindow(
        L"STATIC",
        L"Directory permissions : ",
        WS_VISIBLE | WS_CHILD,
        10, 260,
        200, 20,
        hWnd,
        NULL,
        NULL,
        NULL);
}

void AddEditChild(HWND hWnd) {
    hUser = CreateWindow(
        L"EDIT",
        L"",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        10, 35,
        250, 20,
        hWnd,
        NULL,
        NULL,
        NULL
    );

    hObject = CreateWindow(
        L"EDIT",
        L"",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        10, 90,
        250, 20,
        hWnd,
        NULL,
        NULL,
        NULL
    );
}

void AddCheckBox(HWND hWnd)
{
    CreateWindow(
        L"BUTTON",
        L"Write to files",
        WS_VISIBLE | WS_CHILD | WS_BORDER | BS_AUTOCHECKBOX,
        10, 150,
        250, 20,
        hWnd,
        (HMENU)CREATE,
        NULL,
        NULL
    );

    CreateWindow(
        L"BUTTON",
        L"Change Attributes",
        WS_VISIBLE | WS_CHILD | WS_BORDER | BS_AUTOCHECKBOX,
        10, 175,
        250, 20,
        hWnd,
        (HMENU)WRITE,
        NULL,
        NULL
    );

    CreateWindow(
        L"BUTTON",
        L"Read Permissions/Owners",
        WS_VISIBLE | WS_CHILD | WS_BORDER | BS_AUTOCHECKBOX,
        10, 200,
        250, 20,
        hWnd,
        (HMENU)READ,
        NULL,
        NULL
    );

    CreateWindow(
        L"BUTTON",
        L"Read file Permissions/Owners",
        WS_VISIBLE | WS_CHILD | WS_BORDER | BS_AUTOCHECKBOX,
        10, 285,
        250, 20,
        hWnd,
        (HMENU)DIR_READ_OWNER,
        NULL,
        NULL
    );

    CreateWindow(
        L"BUTTON",
        L"Create files/subdirectories",
        WS_VISIBLE | WS_CHILD | WS_BORDER | BS_AUTOCHECKBOX,
        10, 305,
        250, 20,
        hWnd,
        (HMENU)DIR_CREATE,
        NULL,
        NULL
    );

    CreateWindow(
        L"BUTTON",
        L"Change directory attributes",
        WS_VISIBLE | WS_CHILD | WS_BORDER | BS_AUTOCHECKBOX,
        10, 330,
        250, 20,
        hWnd,
        (HMENU)DIR_WRITE_ATTR,
        NULL,
        NULL
    );

    CreateWindow(
        L"BUTTON",
        L"Read directory Permissions/Owners",
        WS_VISIBLE | WS_CHILD | WS_BORDER | BS_AUTOCHECKBOX,
        10, 355,
        250, 20,
        hWnd,
        (HMENU)DIR_READ_PERM,
        NULL,
        NULL
    );
}




void CreateChildWindow(HWND hParent)
{
    HWND hWnd = CreateWindow(
        L"ChildClass",
        L"Advanced Settings",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        100, 100,
        300, 500,
        hParent,
        0,
        NULL,
        0
    );

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    //return (int)msg.wParam;

}

LRESULT CALLBACK PanelProc(HWND hWnd, UINT msg,
    WPARAM wParam, LPARAM lParam) {
    ACCESS_MASK mask;
    switch (msg) {
    case WM_CREATE:
        AddButtonChild(hWnd);
        AddStaticChild(hWnd);
        AddEditChild(hWnd);
        AddCheckBox(hWnd);
        break;

    case WM_COMMAND:
        switch (wParam)
        {
        case APPLY_TO_FILE:
            if (ExtractText(hObject, pszObjName) == 1)
            {
                MessageBoxA(hObject, "Enter path to the file/folder", "Path error", MB_OK | MB_ICONEXCLAMATION);
                break;
            }
            if (ExtractText(hUser, pszTrustee) == 1)
            {
                MessageBoxA(hUser, "Enter username/group", "Name error", MB_OK | MB_ICONEXCLAMATION);
                break;
            }
            mask = CheckFileMask(hWnd);
            RequestRights(hWnd, pszObjName, pszTrustee, mask);
            break;

        case APPLY_TO_DIR:

            if (ExtractText(hObject, pszObjName) == 1)
            {
                MessageBoxA(hObject, "Enter path to the file/folder", "Path error", MB_OK | MB_ICONEXCLAMATION);
                break;
            }
            if (ExtractText(hUser, pszTrustee) == 1)
            {
                MessageBoxA(hUser, "Enter username/group", "Name error", MB_OK | MB_ICONEXCLAMATION);
                break;
            }
            mask = CheckDirMask(hWnd);
            RequestRights(hWnd, pszObjName, pszTrustee, mask);
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
        break;
    }

    return 0;
}



void RegisterChildClass(void) {

    WNDCLASSW rwc = { 0 };

    rwc.lpszClassName = L"ChildClass";
    rwc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    rwc.lpfnWndProc = PanelProc;
    rwc.hCursor = LoadCursor(0, IDC_ARROW);

    if (!RegisterClass(&rwc))
    {
        MessageBoxW(NULL,
            L"Call to RegisterClass failed!",
            L"Failed",
            NULL);
        return;
    }
}




