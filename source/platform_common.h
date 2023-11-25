#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <limits>

#define combineRGB(r, g, b) ((r << 16) | (g << 8) | b)

namespace safe
{
    // ASCII characters from darkest to brightest
    const static char* const chars = " `.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@";
    constexpr int CharsAmount = 91;

    // an array that stores the precomputed brightness value for each possible RGB value
    // i know its not memory efficient because its about 67 megabytes, but at least 
    // the program doesn't have to do expensive floating point calculations during video playback
    extern float* brightnessLookup;

    namespace disposable
    {
        std::string askVideoPath();
        char askResolution();
        // precomputes the brightness value for each possible RGB value
        void ComputeBrightnessLookupTable();
    }

}