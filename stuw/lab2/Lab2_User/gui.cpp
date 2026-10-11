

#include "interaction.h"

void RegisterChildClass(void);

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
 
        
        break;
    case WM_COMMAND:
        switch (wParam) {
        case CHECK_ATTR:
            SetWindowTextW(hTextContents, NULL);
            ExtractText(hPath, pszObjName);

            CheckPermissions(hPath, hTextContents);
            //CheckFileAttr(pszObjName, hTextContents);
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
