![GitHub](https://img.shields.io/github/license/hunar4321/life_code)
# Terminal ASCII Video
The C++ program that takes a video file and plays it in your terminal with ASCII characters\
This program is built on pure C++ with the help of OpenCV(for reading video frames) and wxWidgets(for showing file dialog)\
Right now works under windows only.
# Usage
- Download `executable.zip` from [`releases`](https://github.com/martytyty2098/Terminal-ASCII-Video/releases)
- Extract all the files into the same folder and run `VIDEO_SEEKER.exe` the executable like this:
<img width="600" alt="Screenshot_1" src="https://user-images.githubusercontent.com/108870368/232514678-c9d7df83-4f79-429a-bdc3-889626971b04.png">
- **`IMPORTANT`** Ensure that `ASCII_VIDEO.exe` and `VIDEO_SEEKER.exe` are in the same directory/folder because `VIDEO_SEEKER.exe` invokes `ASCII_VIDEO.exe`
- Follow displayed instructions

**`COOL THINGS`**
- The console window is fully resizable during real time video playback.
- The program supports all types of fonts, so you can set a small font to increase the resolution of the ASCII video.

# How to build
If you have CMake, insert this in your terminal:
```
git clone https://github.com/martytyty2098/Terminal-ASCII-Video.git && cd Terminal-ASCII-Video && mkdir build && cd build && cmake ..
```
Then open the `MASTER` project, there will be two subprojects named `ASCII_VIDEO` and `VIDEO_SEEKER`\
`VIDEO_SEEKER` contains the wxWidgets-dependent code that displays the file dialog and then passes path of the video to `ASCII_VIDEO.exe`\
You will have to setup library dependencies on your own.
#### IMPORTANT
Ensure that `ASCII_VIDEO.exe` and `VIDEO_SEEKER.exe` are in the same directory/folder because `VIDEO_SEEKER.exe` invokes `ASCII_VIDEO.exe`

# Known issues
- This program only works under Windows
- The program can't handle video files that are heavily compressed with codecs like AV1
