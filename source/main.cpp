#include <opencv2/core/utils/logger.hpp> // for setLogLevel()
#include <chrono> // for high_resolution_clock
#include "platform_specific.h"

int main(int argc, char** argv)
{
    safe::disposable::ComputeBrightnessLookupTable();
    safe::SetConsoleTextSize(8, 16);
    cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);

    std::string video_path = "C:\\users\\martin\\desktop\\fight.mp4"; //safe::disposable::askVideoPath();

    std::cout << "Opening video at " << video_path << '\n';

    // Console window size in characters
    int win_width, win_height;

    cv::VideoCapture SourceVideo(video_path);
    //SourceVideo.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
    //SourceVideo.set(cv::CAP_PROP_BUFFERSIZE, 1);

    if (!SourceVideo.isOpened())
    {
        std::cout << "The video at " << video_path << " was not found.\n";
        std::cout << "This address is probably invalid or the file extension is not supported\n";
        std::cout << "\nPress Enter to exit . . . ";
        std::cin.get();
        return -1;
    }

    size_t frame_amount = static_cast<size_t>(SourceVideo.get(cv::CAP_PROP_FRAME_COUNT));
    double original_fps = SourceVideo.get(cv::CAP_PROP_FPS);

    if (original_fps < 1 || frame_amount <= 0) {
        std::cout 
            << "There was an issue with this particular video, please try another one"
            << "\nPress Enter to exit . . . ";
        std::cin.get();
    }

    std::cout
        << "Video path - " << video_path
        << "\n\nOriginal frame rate of the video - " << original_fps
        << "\nOriginal resolution of the video - " << SourceVideo.get(cv::CAP_PROP_FRAME_WIDTH) << " x " << SourceVideo.get(cv::CAP_PROP_FRAME_HEIGHT);
    {
        int overall_sec = int(frame_amount / original_fps);
        int overall_min = overall_sec / 60;
        int sec = overall_sec % 60;
        int min = overall_min % 60;
        int hrs = overall_min / 60;

        std::cout << "\n\nVideo length - "
            << (hrs < 10 ? '0' : '\0') << hrs << " : "
            << (min < 10 ? '0' : '\0') << min << " : "
            << (sec < 10 ? '0' : '\0') << sec;

        safe::SetConsoleResolution(safe::disposable::askResolution());
    }

    auto frame_end_time = std::chrono::high_resolution_clock::now();
    auto frame_begin_time = std::chrono::high_resolution_clock::now();
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();

    // in seconds
    double DeltaTime; 
    constexpr double MAX_DELTA_TIME = 1.0;
    const double expected_DeltaTime = 1.0 / original_fps;
    
    safe::GetWindowSize(win_width, win_height);

    //SourceVideo.set(cv::CAP_PROP_FRAME_WIDTH, win_width);
    //SourceVideo.set(cv::CAP_PROP_FRAME_HEIGHT, win_height);

    safe::CHAR_ABSTRACT* imageBuffer = new safe::CHAR_ABSTRACT[win_width * win_height];
    memset(imageBuffer, 0, win_width * win_height * sizeof(safe::CHAR_ABSTRACT));
    
    int last_width = win_width;
    int last_height = win_height;

    cv::Mat current_frame;

    for (size_t current_frame_number = 1; current_frame_number < frame_amount;)
    {
        safe::GetWindowSize(win_width, win_height);

        // if the width or height of the last frame does not match the current frame
        // it means the window has been resized
        while (last_width != win_width || last_height != win_height)
        {
            last_width = win_width;
            last_height = win_height;
            delete[] imageBuffer;
            imageBuffer = new safe::CHAR_ABSTRACT[win_width * win_height];
            memset(imageBuffer, 0, win_width * win_height * sizeof(safe::CHAR_ABSTRACT));
            //SourceVideo.set(cv::CAP_PROP_FRAME_WIDTH, win_width);
            //SourceVideo.set(cv::CAP_PROP_FRAME_HEIGHT, win_height);
            safe::GetWindowSize(win_width, win_height);
        }
        
        frame_begin_time = std::chrono::high_resolution_clock::now();

        //start = std::chrono::high_resolution_clock::now();
        SourceVideo.read(current_frame);
        //end = std::chrono::high_resolution_clock::now();
        //std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() * 0.001 << "\tcv::VideoCapture::read()" << std::endl;

        ++current_frame_number;
        if (current_frame.empty()) continue;

        //start = std::chrono::high_resolution_clock::now();
        safe::LoadImageToBuffer(current_frame, imageBuffer, win_width, win_height);
        //end = std::chrono::high_resolution_clock::now();
        //std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() * 0.001 << "\tLoadImageToBuffer()" << std::endl;

        safe::RenderBuffer(imageBuffer, win_width, win_height);

        frame_end_time = std::chrono::high_resolution_clock::now();

        // i heard that multiplication is faster than devision
        DeltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(frame_end_time - frame_begin_time).count() * 0.001;
        //std::cout << DeltaTime << "\tTotal" << std::endl;
        if (DeltaTime > MAX_DELTA_TIME) DeltaTime = MAX_DELTA_TIME;

        // prevents the program from running faster than the original video
        if (DeltaTime < expected_DeltaTime)
        {
            while (DeltaTime < expected_DeltaTime)
            {
                frame_end_time = std::chrono::high_resolution_clock::now();
                DeltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(frame_end_time - frame_begin_time).count() * 0.001;
            }
        }
        // prevents the program from running slower than the original video
        else
        {
            int leftover_frames = int((DeltaTime - expected_DeltaTime) / expected_DeltaTime);
            for (; leftover_frames > 0; --leftover_frames, ++current_frame_number)
            {
                SourceVideo.read(current_frame);
            }
        }

        last_width = win_width;
        last_height = win_height;
    }
    
    // clear screen
    //FillConsoleOutputCharacterA(hConsole, (TCHAR)' ', win_width * win_height, { 0, 0 }, &charsWritten);

    safe::SetConsoleTextSize(8, 16);
    std::cout << "The video was played successfully\n\nPress Enter to exit . . . ";

    std::cin.get();

    return 0;
}
