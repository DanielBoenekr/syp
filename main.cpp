#include <windows.h>
#include "window_settings.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CLOSE:
            PostQuitMessage(0);
            break;
        case WM_PAINT:
        {
            HDC hdc = GetDC(hwnd);
            DrawGrayBar(hwnd, hdc);
            ReleaseDC(hwnd, hdc);
        }
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int main() {
    const char CLASS_NAME[] = "Sample Window Class";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
            0,
            CLASS_NAME,
            "Save-Your-Plants",
            WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, // Entfernen der Sizable-Eigenschaft
            CW_USEDEFAULT, CW_USEDEFAULT, 1000, 600,
            NULL,
            NULL,
            GetModuleHandle(NULL),
            NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, SW_SHOWDEFAULT);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
