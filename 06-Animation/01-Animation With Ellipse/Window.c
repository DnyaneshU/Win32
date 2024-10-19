#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#include "Window.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define ELLIPSE_SIZE_X 100
#define ELLIPSE_SIZE_Y 100
#define DMU_TIMER 201

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
    WNDCLASSEX wndclass;
    HWND hwnd;
    MSG msg;
    TCHAR szClassName[] = TEXT("DMU_WINDOW");

    ZeroMemory(&wndclass, sizeof(WNDCLASSEX));

    wndclass.cbSize = sizeof(WNDCLASSEX);
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.hInstance = hInstance;
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndclass.lpszClassName = szClassName;

    if (!RegisterClassEx(&wndclass))
    {
        MessageBox(NULL, TEXT("Window Registration Failed!"), TEXT("Error"), MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindow(szClassName, TEXT("Dnyanesh Milind Ujalambkar: First Window"), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);

    if (hwnd == NULL)
    {
        MessageBox(NULL, TEXT("Window Creation Failed!"), TEXT("Error"), MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rect;
    HBRUSH hBrush;
    static int xAnimate = 0;
    static BOOL bGoFromLeftToRight = TRUE;

    switch (iMsg)
    {
    case WM_CREATE:
        SetTimer(hwnd, DMU_TIMER, 1, NULL);
        break;

    case WM_PAINT:
        GetClientRect(hwnd, &rect);
        hdc = BeginPaint(hwnd, &ps);
        hBrush = CreateSolidBrush(RGB(255, 0, 0));

        SelectObject(hdc, hBrush);
        Ellipse(hdc, xAnimate, (WINDOW_HEIGHT / 2) - (ELLIPSE_SIZE_Y / 2),
            xAnimate + ELLIPSE_SIZE_X, (WINDOW_HEIGHT / 2) + (ELLIPSE_SIZE_Y / 2));

        DeleteObject(hBrush);
        EndPaint(hwnd, &ps);
        break;

    case WM_TIMER:
        if (bGoFromLeftToRight)
        {
            xAnimate += 1;
            if (xAnimate + ELLIPSE_SIZE_X >= WINDOW_WIDTH)
            {
                bGoFromLeftToRight = FALSE;
            }
        }
        else
        {
            xAnimate -= 1;
            if (xAnimate <= 0)
            {
                bGoFromLeftToRight = TRUE;
            }
        }
        InvalidateRect(hwnd, NULL, TRUE);
        break;

    case WM_DESTROY:
        PlaySound(NULL, 0, 0);
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, iMsg, wParam, lParam);
    }
    return 0;
}
