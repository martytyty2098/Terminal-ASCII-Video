#include <opencv2/core/utils/logger.hpp> // for setLogLevel
#include <chrono> // for high_resolution_clock
#include "utils.h"

int main(void)
{
    cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);

    std::string video_path = common::disposable::askVideoPath();

    std::cout << "Opening video at " << video_path << '\n';

    cv::VideoCapture SourceVideo(video_path);
    SourceVideo.set(cv::CAP_PROP_BUFFERSIZE, 1);

    if (!SourceVideo.isOpened())
    {
        std::cout << "The video at " << video_path << " was not found.\n";
        std::cout << "This address is probably invalid or the file extension is not supported\n";
        std::cout << "\nPress Enter to exit . . . ";
        std::cin.get();
        return -1;
    }

    {
        size_t frame_amount = static_cast<size_t>(SourceVideo.get(cv::CAP_PROP_FRAME_COUNT));
        double original_fps = SourceVideo.get(cv::CAP_PROP_FPS);

        if (original_fps < 1 || frame_amount <= 0) {
            std::cout
                << "There was an issue with this particular video, please try another one"
                << "\nPress Enter to exit . . . ";
            std::cin.get();
        }

        std::cout
            << "\n\nOriginal frame rate of the video - " << original_fps
            << "\nOriginal resolution of the video - " << SourceVideo.get(cv::CAP_PROP_FRAME_WIDTH) << " x " << SourceVideo.get(cv::CAP_PROP_FRAME_HEIGHT);

        int total_sec = int(frame_amount / original_fps);
        int hrs = total_sec / 3600;
        total_sec %= 3600;
        int min = total_sec / 60;
        int sec = total_sec % 60;

        printf("\n\nVideo length - %02d : %02d : %02d\n", hrs, min, sec);
    }

    specific::SetConsoleResolution(common::disposable::askResolution());

    common::StartPlayback(SourceVideo);

    specific::ClearScreen();

    std::cout << "The video was played successfully.\nPress enter to exit . . . ";
    std::cin.get();
    return 0;
}