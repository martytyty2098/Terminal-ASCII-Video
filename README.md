![GitHub](https://img.shields.io/github/license/hunar4321/life_code)
# Terminal ASCII Video
The C++ program that takes a video file and plays it in your terminal with grayscale ASCII characters\
This program is built on pure C++ with the help of OpenCV library\
Right now only works on windows, but linux support will be added in the future
# Usage
- Download `executable.zip` from [`releases`](https://github.com/martytyty2098/Terminal-ASCII-Video/releases)
- Extract all the files into the same folder and run the executable like this:
<img width="600" alt="Screenshot_1" src="https://user-images.githubusercontent.com/108870368/232514678-c9d7df83-4f79-429a-bdc3-889626971b04.png">

- Follow displayed instructions

**`COOL THINGS`**
- The console window is fully resizable during real time video playback, but note that larger window size can result in a decrease in FPS, because more characters need to be rendered.
- The program supports all types of fonts, so you can set a small font to increase the resolution of the ASCII video, but too small a font can result in a decrease in FPS, as more characters must be displayed on the console screen.

# How to build
If you have CMake, insert this in your terminal:
```
git clone https://github.com/martytyty2098/Terminal-ASCII-Video.git && cd Terminal-ASCII-Video && mkdir build && cd build && cmake ..
```

# Known issues
- The file path to the video passed to the program must be in english characters
- This program only works on Windows
- .dll files in `executable.zip` are heavy
