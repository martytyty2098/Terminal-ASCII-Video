#pragma once

#include "platform_common.h"

#ifdef _WIN32
#include <Windows.h>
namespace safe {
    using CHAR_ABSTRACT = ::_CHAR_INFO;
}
#endif

namespace safe
{
    void LoadImageToBuffer(cv::Mat& SourceImage, safe::CHAR_ABSTRACT* DestBuffer, int WinWidth, int WinHeight);
    // console window size in character
    void GetWindowSize(int& width_out, int& height_out);
    void RenderBuffer(safe::CHAR_ABSTRACT* buffer, short win_width, short win_height);
    void SetConsoleTextSize(int new_width, int new_height);
    void SetConsoleResolution(char resolution);
}