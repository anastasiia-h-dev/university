

#include "interaction.h"


HWND IP, hString, hAnswer;
const wchar_t* CLASS_NAME = L"Desktop_Window";


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void AddButton(HWND hWnd);
void AddStatic(HWND hWnd);
void AddEdit(HWND hWnd);


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
        L"Client",
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
        case CONNECT:
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
        L"Connect",
        WS_TABSTOP | BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD,
        220, 60,
        130, 20,
        hWnd,
        (HMENU)CONNECT,
        NULL,
        NULL
    );

    //CreateWindow(
    //    L"BUTTON",
    //    L"Send",
    //    WS_TABSTOP | BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD,
    //    220, 60,
    //    130, 20,
    //    hWnd,
    //    NULL,
    //    NULL,
    //    NULL
    //);

    //CreateWindow(
    //    L"BUTTON",
    //    L"Choose file",
    //    WS_TABSTOP | BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD,
    //    220, 60,
    //    130, 20,
    //    hWnd,
    //    NULL,
    //    NULL,
    //    NULL
    //);
}

void AddStatic(HWND hWnd) {
    //CreateWindow(
    //    L"STATIC",
    //    L"IP-address : ",
    //    WS_VISIBLE | WS_CHILD | WS_BORDER,
    //    10, 85,
    //    340, 20,
    //    hWnd,
    //    NULL,
    //    NULL,
    //    NULL
    //);

        //CreateWindow(
    //    L"STATIC",
    //    L"Port : ",
    //    WS_VISIBLE | WS_CHILD | WS_BORDER,
    //    10, 85,
    //    340, 20,
    //    hWnd,
    //    NULL,
    //    NULL,
    //    NULL
    //);

 /*   CreateWindow(
        L"STATIC",
        L"Select the operation, choose the file or write some char/number array and click \"Send\": ",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        10, 85,
        340, 20,
        hWnd,
        NULL,
        NULL,
        NULL
    );

    CreateWindow(
        L"STATIC",
        L"For strings and symbols : ",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        10, 85,
        340, 20,
        hWnd,
        NULL,
        NULL,
        NULL
    );


    CreateWindow(
        L"STATIC",
        L"For number arrays : ",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        10, 85,
        340, 20,
        hWnd,
        NULL,
        NULL,
        NULL
    );*/

    //CreateWindow(
    //    L"STATIC",
    //    L"Choose transport layer protocol : ",
    //    WS_VISIBLE | WS_CHILD | WS_BORDER,
    //    10, 85,
    //    340, 20,
    //    hWnd,
    //    NULL,
    //    NULL,
    //    NULL
    //);

    CreateWindow(
        L"STATIC",
        L"Answer from the server : ",
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
    //IP = CreateWindow(
    //    L"EDIT",
    //    L"",
    //    WS_VISIBLE | WS_CHILD | WS_BORDER,
    //    10, 35,
    //    340, 20,
    //    hWnd,
    //    NULL,
    //    NULL,
    //    NULL
    //);


    //hString = CreateWindow(
    //    L"EDIT",
    //    L"",
    //    WS_VISIBLE | WS_CHILD | WS_BORDER,
    //    10, 35,
    //    340, 20,
    //    hWnd,
    //    NULL,
    //    NULL,
    //    NULL
    //);



    hAnswer = CreateWindow(
        L"EDIT",
        L"",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        10, 100,
        340, 340,
        hWnd,
        NULL,
        NULL,
        NULL
    );
}
