#ifndef WINDOW_SETTINGS_H
#define WINDOW_SETTINGS_H

#include <windows.h>
#include <vector>

extern HICON hIcon;
extern HBITMAP hBitmap;
extern std::vector<POINT> bitmapPositions;

HMENU CreateCustomMenu();


void AddPlant(HWND hwnd);
void DrawPlants(HDC hdc);

#endif // WINDOW_UTILS_H
