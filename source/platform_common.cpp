#include "utils.h"

std::string common::disposable::askVideoPath()
{
    std::cout
        << "Insert the path of your video, path can be relative or full\n\n"
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

char common::disposable::askResolution()
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
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

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
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            passed = false;
        }
    }

    return resolution;
}

float common::getBrightness(common::RGB color)
{
    // Rec. 601 standard
    constexpr float WeightR = 0.299f;
    constexpr float WeightG = 0.587f;
    constexpr float WeightB = 0.114f;

    return ((color.R / 255.0f * WeightR) + (color.G / 255.0f * WeightG) + (color.B / 255.0f * WeightB));
}

char common::brightnessToChar(float brightness)
{
    return common::chars[int(common::CharsAmount * brightness)];
}

void common::LoadImageToBuffer(cv::Mat& SourceImage, common::CHAR_ABSTRACT* DestBuffer, int WinWidth, int WinHeight)
{
    if (WinWidth < 1 || WinHeight < 1) return;

    cv::resize(SourceImage, SourceImage, cv::Size(WinWidth, WinHeight), 0.0, 0.0, cv::INTER_NEAREST);

    for (int y = 0; y < WinHeight; ++y)
    {
        const unsigned char* const CurrentRow = SourceImage.ptr<unsigned char>(y);
        for (int x = 0; x < WinWidth; ++x)
        {
            const unsigned char* const CurrentPix = CurrentRow + 3 * x;
            specific::LoadCharInfo(DestBuffer[WinWidth * y + x], { CurrentPix[2], CurrentPix[1], CurrentPix[0] });
        }
    }
}

void common::StartPlayback(cv::VideoCapture& video)
{
    const size_t frame_amount = static_cast<size_t>(video.get(cv::CAP_PROP_FRAME_COUNT));
    double original_fps = video.get(cv::CAP_PROP_FPS);

    auto frame_end_time = std::chrono::high_resolution_clock::now();
    auto frame_begin_time = std::chrono::high_resolution_clock::now();

    // in seconds
    double DeltaTime;
    const double expected_DeltaTime = 1.0 / original_fps;

    int win_width, win_height;
    specific::GetWindowSize(win_width, win_height);

    common::CHAR_ABSTRACT* imageBuffer = new common::CHAR_ABSTRACT[win_width * win_height];
    memset(imageBuffer, 0, win_width * win_height * sizeof(common::CHAR_ABSTRACT));

    int last_width = win_width;
    int last_height = win_height;

    cv::Mat current_frame;

    for (size_t current_frame_number = 1; current_frame_number < frame_amount;)
    {
        frame_begin_time = std::chrono::high_resolution_clock::now();

        specific::GetWindowSize(win_width, win_height);

        // if the width or height of the last frame does not match the current frame it means the window has been resized
        while (last_width != win_width || last_height != win_height)
        {
            last_width = win_width;
            last_height = win_height;

            // reallocate the buffer to fit the new screen size
            delete[] imageBuffer;
            imageBuffer = new common::CHAR_ABSTRACT[win_width * win_height];
            memset(imageBuffer, 0, win_width * win_height * sizeof(common::CHAR_ABSTRACT));

            specific::GetWindowSize(win_width, win_height);
            // this loop will not end until the user stops resizing the window
        }

        video.read(current_frame);
        ++current_frame_number;
        if (current_frame.empty()) break;

        common::LoadImageToBuffer(current_frame, imageBuffer, win_width, win_height);

        specific::RenderBuffer(imageBuffer, win_width, win_height);

        frame_end_time = std::chrono::high_resolution_clock::now();

        // i heard that multiplication is faster than devision
        DeltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(frame_end_time - frame_begin_time).count() * 0.001;

        // prevents the program from running faster than the original video
        while (DeltaTime < expected_DeltaTime)
        {
            auto now = std::chrono::high_resolution_clock::now();
            DeltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - frame_begin_time).count() * 0.001;
        }

        /* 
        i tried to prevent the program from running slower than the original video by dropping some frames
        but that is simply impossible with some types of video encoding like AV1
        because to jump over some frames you must decode them all, which takes time and CPU power
        if (DeltaTime > expected_DeltaTime)
        {
            int leftover_frames = int((DeltaTime - expected_DeltaTime) / expected_DeltaTime);
            for (; leftover_frames > 0; --leftover_frames, ++current_frame_number)
            {
                SourceVideo.grab(); // i tried to set CAP_PROP_POS_FRAMES or CAP_PROP_POS_MSEC instead, but it causes freeze
            }
        }
        */

        last_width = win_width;
        last_height = win_height;
    }
}