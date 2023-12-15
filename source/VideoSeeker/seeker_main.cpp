#include <wx\wx.h>
#include <string>
#include <locale>
#include <codecvt>

std::wstring exePath();

class MyApp : public wxApp
{
public:
    MyApp() {};
    ~MyApp() {};
	virtual bool OnInit();
};

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
	wxFileDialog openFileDialog(
		nullptr, wxT("Open video to play"),
		wxEmptyString, wxEmptyString, 
		wxT("Video files (*.mp4;*.avi;*.mkv;*.mov;*.wmv;*.flv;*.webm;*.3gp;*.mpg;*.mpeg)|*.mp4;*.avi;*.mkv;*.mov;*.wmv;*.flv;*.3gp;*.mpg;*.mpeg"),
		wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return false;

	std::wstring video_path = openFileDialog.GetPath().ToStdWstring();
    video_path.insert(video_path.begin(), L'\"');
    video_path.append(L"\"");

    std::wstring command = exePath();
    command.append(L"\\ASCII_VIDEO.exe ");
    command.append(video_path);
    command.append(L" 1");

    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;

    std::string converted_str = converter.to_bytes(command);

    system(converted_str.c_str());

	return false;
}

#ifdef _WIN32

std::wstring exePath() {
    TCHAR buffer[MAX_PATH] = { 0 };
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
    return std::wstring(buffer).substr(0, pos);
}

#endif