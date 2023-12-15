#include <opencv2/core/utils/logger.hpp> // for setLogLevel
#include <chrono> // for high_resolution_clock
#include "utils.h"

int main(int argc, char** argv)
{
    cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);

    std::string video_path;

    if (argc > 1)
    {
        video_path = argv[1];
    }
    else video_path = common::disposable::askVideoPath();

    std::cout << "\nOpening video at " << video_path << '\n';

    cv::VideoCapture SourceVideo(video_path);

    if (!SourceVideo.isOpened())
    {
        std::cout << "\nThe video at " << video_path << " was not opened.\n";
        std::cout << "This address is probably invalid or the file extension is not supported\n";
        std::cout << "\n\nPress Enter to exit . . . ";
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

    common::SetConsoleResolution(argc > 2 ? argv[2][0] : common::disposable::askResolution());

    SourceVideo.set(cv::CAP_PROP_BUFFERSIZE, 1);
    common::StartPlayback(SourceVideo);

    std::cin.get();
    return 0;
}