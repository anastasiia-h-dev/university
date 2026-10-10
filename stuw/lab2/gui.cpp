

#include "interaction.h"

void RegisterChildClass(void);

HWND hPath, hTextContents, hAdvanced;
HWND hUser, hGroup, hObject;
HWND ReadCheck, WriteCheck;

#define PUSHBUTTON 1
#define ADVANCED 2
#define ID_CHILD 3
#define APPLY 4




const wchar_t* CLASS_NAME = L"Desktop_Window";
wchar_t pszObjName;
wchar_t pszTrustee;
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
        L"Lab2 Admin Panel",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        100, 100,
        800, 800,
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
        case PUSHBUTTON:
            SetWindowTextW(hTextContents, NULL);

            char hFilePath[MAX_PATH];
            CheckPermissions(hFilePath, hPath, hTextContents);
            //SetWindowTextA(hIfExists, hFilePath);
            break;
        case ADVANCED:
            CreateChildWindow(hWnd);
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
        L"CLICK",
        WS_TABSTOP | BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD,
        300, 35,
        100, 20,
        hWnd,
        (HMENU)PUSHBUTTON,
        NULL,
        NULL
    );

    CreateWindow(
        L"BUTTON",
        L"Advanced",
        WS_TABSTOP | BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD,
        200, 460,
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
        L"Enter path to the object ->",
        WS_VISIBLE | WS_CHILD,
        10, 10,
        340, 20,
        hWnd,
        NULL,
        NULL,
        NULL
    );

    CreateWindow(
        L"STATIC",
        L"Contents of the file will appear here",
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
        L"...enter path here...",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        360, 10,
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
        case APPLY:
            MessageBoxW(hWnd, L"Hi", L"asd", MB_OK);
            ExtractText(hUser, &pszObjName);
            ExtractText(hObject, &pszTrustee);
            mask = CheckCheckbox(hWnd);
            SetPermissions(&pszObjName, &pszTrustee, mask);
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


void AddButtonChild(HWND hWnd) {
    CreateWindow(
        L"BUTTON",
        L"Apply",
        WS_TABSTOP | BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD,
        10, 250,
        150, 20,
        hWnd,
        (HMENU)APPLY,
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
        NULL
    );

    CreateWindow(
        L"STATIC",
        L"Enter path to the file/folder : ",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        10, 65,
        200, 20,
        hWnd,
        NULL,
        NULL,
        NULL
    );
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
        L"Create Files/WriteData",
        WS_VISIBLE | WS_CHILD | WS_BORDER | BS_AUTOCHECKBOX,
        10, 125,
        200, 20,
        hWnd,
        (HMENU)CREATE,
        NULL,
        NULL
    );

    WriteCheck = CreateWindow(
        L"BUTTON",
        L"Write Attributes",
        WS_VISIBLE | WS_CHILD | WS_BORDER | BS_AUTOCHECKBOX,
        10, 150,
        200, 20,
        hWnd,
        (HMENU)WRITE,
        NULL,
        NULL
    );

    ReadCheck = CreateWindow(
        L"BUTTON",
        L"Read Permissions",
        WS_VISIBLE | WS_CHILD | WS_BORDER | BS_AUTOCHECKBOX,
        10, 175,
        200, 20,
        hWnd,
        (HMENU)READ,
        NULL,
        NULL
    );
}

