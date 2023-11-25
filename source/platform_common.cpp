#include "platform_common.h"

float* safe::brightnessLookup;

std::string safe::disposable::askVideoPath()
{
    std::cout
        << "Insert the path of your video\n\n"
        << "Example :\nC:\\folder_name\\some_other_folder\\videofile.mp4\n\n"
        << "(You can resize the console window as you wish, even while the video is playing)\n\n";

    std::string video_path;
    do {
        std::getline(std::cin, video_path, '\n');
    } while (video_path.empty());

    // remove all spaces at the beginning
    int space_amount = 0;
    for (; space_amount < video_path.length() && video_path[space_amount] == ' '; ++space_amount);
    video_path.erase(0, space_amount);

    return video_path;
}

char safe::disposable::askResolution()
{
    std::cout << "\n\nSelect console window resolution (font size basically)\n"
        << "You can also select any font you want in your console window settings (even while the video is playing)\n\n"
        << "0 - Keep as is\n"
        << "1 - Best resolution\n"
        << "2 - High resolution\n"
        << "3 - Medium resolution\n"
        << "4 - Low resolution\n\n"
        << "Enter the number of desired resolution : ";

    char resolution = 0;
    std::cin >> resolution;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (bool passed = false; !passed; passed = true)
    {
        switch (resolution) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
            break;
        default:
            std::cout << "Bad input, must ba a number from 0 to 4, try again : ";
            std::cin >> resolution;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            passed = false;
        }
    }

    return resolution;
}

void safe::disposable::ComputeBrightnessLookupTable()
{
    // Rec. 601 standard
    constexpr float WeightR = 0.299f;
    constexpr float WeightG = 0.587f;
    constexpr float WeightB = 0.114f;

    safe::brightnessLookup = new float[256 * 256 * 256];

    for (unsigned int r = 0; r < 256; ++r) {
        for (unsigned int g = 0; g < 256; ++g) {
            for (unsigned int b = 0; b < 256; ++b)
            {
                size_t index = combineRGB(r, g, b);
                // The darkest is 0 and the brightest is 1
                brightnessLookup[index] = ((r / 255.0f * WeightR) + (g / 255.0f * WeightG) + (b / 255.0f * WeightB));
            }
        }
    }
}