
#include <windows.h>
#include <stdio.h>
#include <vector>
#include "interaction.h"



HWND hPath, hTextContents, hMatrix, hIfExists, hNumOfColumn, Sum1, Sum2;

#define PUSHBUTTON 1



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
    const wchar_t* CLASS_NAME = L"Desktop_Window";
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
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        800, 800,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    ::ShowWindow(hWnd, nCmdShow);
    ::UpdateWindow(hWnd);

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
        case PUSHBUTTON:
            char hFilePath[MAX_PATH];
            CheckPermissions(hFilePath, hPath, hTextContents);

            //SetWindowTextA(hIfExists, hFilePath);
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
}

void AddStatic(HWND hWnd) {
    CreateWindow(
        L"STATIC",
        L"Enter path to the file ->",
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

    CreateWindow(
        L"STATIC",
        L"...The matrix will appear here...",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        360, 85,
        340, 20,
        hWnd,
        NULL,
        NULL,
        NULL
    );

    CreateWindow(
        L"STATIC",
        L"RESULTS",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        10, 500,
        340, 20,
        hWnd,
        NULL,
        NULL,
        NULL
    );

    CreateWindow(
        L"STATIC",
        L"Column (exists/not exists): ",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        10, 530,
        340, 20,
        hWnd,
        NULL,
        NULL,
        NULL
    );

    CreateWindow(
        L"STATIC",
        L"Number of the column (if exists): ",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        10, 560,
        340, 20,
        hWnd,
        NULL,
        NULL,
        NULL
    );

    CreateWindow(
        L"STATIC",
        L"Sum of the left part : ",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        10, 590,
        340, 20,
        hWnd,
        NULL,
        NULL,
        NULL
    );

    CreateWindow(
        L"STATIC",
        L"Sum of the right part : ",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        10, 620,
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
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE,
        10, 110,
        340, 340,
        hWnd,
        NULL,
        NULL,
        NULL
    );

    hMatrix = CreateWindow(
        L"EDIT",
        L"",
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE,
        360, 110,
        340, 340,
        hWnd,
        NULL,
        NULL,
        NULL
    );

    hIfExists = CreateWindow(
        L"EDIT",
        L"",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        360, 530,
        340, 20,
        hWnd,
        NULL,
        NULL,
        NULL
    );

    hNumOfColumn = CreateWindow(
        L"EDIT",
        L"",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        360, 560,
        340, 20,
        hWnd,
        NULL,
        NULL,
        NULL
    );

    Sum1 = CreateWindow(
        L"EDIT",
        L"",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        360, 590,
        340, 20,
        hWnd,
        NULL,
        NULL,
        NULL
    );

    Sum2 = CreateWindow(
        L"EDIT",
        L"",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        360, 620,
        340, 20,
        hWnd,
        NULL,
        NULL,
        NULL
    );
}