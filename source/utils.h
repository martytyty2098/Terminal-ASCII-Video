#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <limits>

#ifdef _WIN32
#include <Windows.h>
namespace common {
    using CHAR_ABSTRACT = ::_CHAR_INFO;
}
#endif

// platform common
namespace common
{
    struct RGB {
        unsigned char R, G, B;
    };

    // ASCII characters from darkest to brightest
    const static char* const chars = " `.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@";
    constexpr int CharsAmount = 91;

    // brightness from 0.0 to 1.0
    float getBrightness(common::RGB color);

    // brightness from 0.0 to 1.0
    char brightnessToChar(float brightness);

    namespace disposable
    {
        std::string askVideoPath();

        // number from '0' to '4'
        char askResolution();
    }

    // transform an actual video frame into ASCII characters
    void LoadImageToBuffer(cv::Mat& SourceImage, common::CHAR_ABSTRACT* DestBuffer, int WinWidth, int WinHeight);

    // a blocking function that will not stop until it finishes playing the video
    void StartPlayback(cv::VideoCapture& video);
}

// platform specific
namespace specific
{
    void LoadCharInfo(common::CHAR_ABSTRACT& charOut, common::RGB color);

    // console window size in character
    void GetWindowSize(int& width_out, int& height_out);

    // write all characters to the console
    void RenderBuffer(common::CHAR_ABSTRACT* buffer, short win_width, short win_height);

    void SetConsoleTextSize(int new_width, int new_height);

    // number from '0' to '4'
    void SetConsoleResolution(char resolution);

    void ClearScreen();
}