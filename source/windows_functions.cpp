#pragma once
#ifdef _WIN32

#include <chrono>
#include "platform_specific.h"

HANDLE OutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

void safe::LoadImageToBuffer(cv::Mat& SourceImage, safe::CHAR_ABSTRACT* DestBuffer, int WinWidth, int WinHeight)
{
    if (WinWidth < 1 || WinHeight < 1) return;

    cv::resize(SourceImage, SourceImage, cv::Size(WinWidth, WinHeight), 0.0, 0.0, cv::INTER_NEAREST);

    for (int y = 0; y < WinHeight; ++y)
    {
        const unsigned char* const CurrentRow = SourceImage.ptr<unsigned char>(y);
        for (int x = 0; x < WinWidth; ++x)
        {
            const unsigned char* const CurrentPix = CurrentRow + 3 * x;
            
            //std::cout << "R: " << r << "\tG: " << g << "\tB: " << b << "\n";

            unsigned int combined_RGB = combineRGB(CurrentPix[2], CurrentPix[1], CurrentPix[0]);
            float CurrentBrightness = safe::brightnessLookup[combined_RGB];

            safe::CHAR_ABSTRACT& CurrentChar = DestBuffer[WinWidth * y + x];
            CurrentChar.Char.AsciiChar = safe::chars[int(safe::CharsAmount * CurrentBrightness)];
            CurrentChar.Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
        }
    }
}

// Console window size in characters
void safe::GetWindowSize(int& width_out, int& height_out)
{
    CONSOLE_SCREEN_BUFFER_INFO OutputBufferInfo = {};
    GetConsoleScreenBufferInfo(OutputHandle, &OutputBufferInfo);
    width_out = OutputBufferInfo.srWindow.Right - OutputBufferInfo.srWindow.Left + 1;
    height_out = OutputBufferInfo.srWindow.Bottom - OutputBufferInfo.srWindow.Top + 1;
}

void safe::RenderBuffer(safe::CHAR_ABSTRACT* buffer, short win_width, short win_height)
{
    SMALL_RECT writeArea = { 0, 0, win_width - 1, win_height - 1 };
    WriteConsoleOutputA(OutputHandle, buffer, { win_width, win_height }, { 0, 0 }, &writeArea);
}

void safe::SetConsoleTextSize(int new_width, int new_height)
{
    CONSOLE_FONT_INFOEX cfi = {};
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = new_width;
    cfi.dwFontSize.Y = new_height;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, new_width < 6 ? L"Terminal" : L"Consolas");
    SetCurrentConsoleFontEx(OutputHandle, FALSE, &cfi);
}

void safe::SetConsoleResolution(char resolution)
{
    switch (resolution)
    {
    case '1':
        safe::SetConsoleTextSize(2, 5);
        break;
    case '2':
        safe::SetConsoleTextSize(4, 8);
        break;
    case '3':
        safe::SetConsoleTextSize(6, 12);
        break;
    case '4':
        safe::SetConsoleTextSize(8, 16);
        break;
    }
}

#endif