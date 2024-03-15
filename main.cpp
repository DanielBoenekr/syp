#include <windows.h>
#include <d3d9.h>
#include "window_settings.h"
#include <vector>


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            hBitmap = (HBITMAP)LoadImage(NULL, "..\\Icons\\pflanze.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            if (hBitmap == NULL) {
                MessageBox(NULL, "Das Bild konnte nicht geladen werden.", "Fehler", MB_OK | MB_ICONERROR);
            }
            break;
        }
        case WM_COMMAND: {
            if (LOWORD(wParam) == 1001) {
                AddPlant(hwnd);
            }
            break;
        }
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            HDC hdcMem = CreateCompatibleDC(hdc);
            SelectObject(hdcMem, hBitmap);
            BITMAP bitmap;
            GetObject(hBitmap, sizeof(bitmap), &bitmap);
            for (const POINT& pt : bitmapPositions) {
                BitBlt(hdc, pt.x, pt.y, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);
            }
            DeleteDC(hdcMem);
            EndPaint(hwnd, &ps);
            break;
        }

        case WM_CLOSE:
            PostQuitMessage(0);
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

    HMENU hMenu = CreateCustomMenu();
    SetMenu(hwnd, hMenu);
    DrawMenuBar(hwnd); // Neu zeichnen des Fensters
    ShowWindow(hwnd, SW_SHOWDEFAULT);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
