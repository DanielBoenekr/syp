#include "window_settings.h"

void DrawGrayBar(HWND hwnd, HDC hdc) {
    PAINTSTRUCT ps;
    BeginPaint(hwnd, &ps);

    RECT rect;
    GetClientRect(hwnd, &rect);
    rect.top = 20; // Abstand von oben
    rect.bottom = rect.bottom - 20; // Höhe der Leiste (hier bis zum unteren Rand mit 20 Pixel Abstand)
    rect.left = rect.right - (rect.right * 0.09); // Position der Leiste (hier rechts, 5% der Fensterbreite + 4% Abstand zum Rand)
    rect.right = rect.right - (rect.right * 0.02); // 2% Abstand zum rechten Rand
    HBRUSH hBrush = CreateSolidBrush(RGB(192, 192, 192)); // Graue Farbe
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush); // Set the brush for the device context

    FillRect(hdc, &rect, hBrush);

    SelectObject(hdc, hOldBrush); // Restore the original brush
    DeleteObject(hBrush);

    EndPaint(hwnd, &ps);
}