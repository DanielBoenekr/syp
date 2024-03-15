#include "window_settings.h"

// Globale Variablen
HICON hIcon; // Handle für das Icon
POINT iconPos; // Position des Icons
HBITMAP hBitmap;
std::vector<POINT> bitmapPositions;


HMENU CreateCustomMenu() {
    // Erstellen Sie ein neues Menü
    HMENU hMenu = CreateMenu();

    // Fügen Sie Menüpunkte hinzu
    AppendMenu(hMenu, MF_STRING, 1001, "Plant");
    AppendMenu(hMenu, MF_STRING, 1002, "Add Room");

    // Geben Sie das erstellte Menü zurück
    return hMenu;
}

void AddPlant(HWND hwnd) {
    if (bitmapPositions.size() < 10) {
        RECT rect;
        GetClientRect(hwnd, &rect);
        POINT pt = {(rect.right - rect.left) / 2, (rect.bottom - rect.top) / 2};
        bitmapPositions.push_back(pt);
        InvalidateRect(hwnd, NULL, TRUE);
    } else {
        MessageBox(hwnd, "Maximale Anzahl von Pflanzen erreicht.", "Information", MB_OK | MB_ICONINFORMATION);
    }
}

void DrawPlants(HDC hdc) {
    HDC hdcMem = CreateCompatibleDC(hdc);
    SelectObject(hdcMem, hBitmap);
    BITMAP bitmap;
    GetObject(hBitmap, sizeof(bitmap), &bitmap);
    for (const POINT& pt : bitmapPositions) {
        BitBlt(hdc, pt.x, pt.y, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);
    }
    DeleteDC(hdcMem);
}
