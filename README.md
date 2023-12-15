![GitHub](https://img.shields.io/github/license/hunar4321/life_code)
# Terminal ASCII Video
The C++ program that takes a video file and plays it in your terminal with ASCII characters\
This program is built on pure C++ with the help of OpenCV (for reading video frames) and wxWidgets (for showing file dialog)\
_Right now works under windows only._
# Usage
- Download `executable.zip` from [`Releases`](https://github.com/martytyty2098/Terminal-ASCII-Video/releases)
- Extract all the files into the same folder and run `VIDEO_SEEKER.exe` like this:
  
  <img width="300" alt="Screenshot_4" src="https://github.com/martytyty2098/Terminal-ASCII-Video/assets/108870368/b041c1b0-d069-4309-8a30-3e2225e44a84">

- **`IMPORTANT`** Ensure that `ASCII_VIDEO.exe` and `VIDEO_SEEKER.exe` are in the same directory/folder because `VIDEO_SEEKER.exe` invokes `ASCII_VIDEO.exe`
- Follow displayed instructions

#### By the way
- The console window is fully resizable during real time video playback.
- The program supports all types of fonts, so you can set a small font to increase the resolution of the ASCII video.

# How to build
If you have CMake, insert this in your terminal:
```
git clone https://github.com/martytyty2098/Terminal-ASCII-Video.git && cd Terminal-ASCII-Video && mkdir build && cd build && cmake ..
```
Then open the `MASTER` project, there will be two subprojects named `ASCII_VIDEO` and `VIDEO_SEEKER`\
`VIDEO_SEEKER` contains the wxWidgets-dependent code that displays the file dialog and then passes path of the video to `ASCII_VIDEO.exe`\
**You will have to setup library dependencies on your own.**
#### IMPORTANT
**Even if you are not using CMake, ensure that `ASCII_VIDEO.exe` and `VIDEO_SEEKER.exe` are in the same directory/folder because `VIDEO_SEEKER.exe` invokes `ASCII_VIDEO.exe`**

# Known issues
- This program only works under Windows
- The program can't handle video files that are heavily compressed with codecs like AV1
