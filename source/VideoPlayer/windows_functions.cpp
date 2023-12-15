#pragma once
#ifdef _WIN32

#include "utils.h"

HANDLE OutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

void specific::LoadCharInfo(common::CHAR_ABSTRACT& charOut, common::RGB color)
{
    float brightness = common::getBrightness(color);
    charOut.Char.AsciiChar = common::brightnessToChar(brightness);
    charOut.Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
}

// Console window size in characters
void specific::GetWindowSize(int& width_out, int& height_out)
{
    CONSOLE_SCREEN_BUFFER_INFO OutputBufferInfo = {};
    GetConsoleScreenBufferInfo(OutputHandle, &OutputBufferInfo);
    width_out = OutputBufferInfo.srWindow.Right - OutputBufferInfo.srWindow.Left + 1;
    height_out = OutputBufferInfo.srWindow.Bottom - OutputBufferInfo.srWindow.Top + 1;
}

void specific::RenderBuffer(common::CHAR_ABSTRACT* buffer, short win_width, short win_height)
{
    SMALL_RECT writeArea = { 0, 0, win_width - 1, win_height - 1 };
    WriteConsoleOutputA(OutputHandle, buffer, { win_width, win_height }, { 0, 0 }, &writeArea);
    SetConsoleCursorPosition(OutputHandle, { 0, 0 });
}

void specific::SetConsoleTextSize(int new_width, int new_height)
{
    CONSOLE_FONT_INFOEX cfi = {};
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = new_width;
    cfi.dwFontSize.Y = new_height;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, new_width == 4 ? L"Terminal" : L"Consolas");
    SetCurrentConsoleFontEx(OutputHandle, FALSE, &cfi);
}

#endif