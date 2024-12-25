#include "Console.h"

#ifdef __linux__

#include "OutputStream.h"
#include <vector>
#include <ncurses.h>

waki::Console& waki::Console::GetObject()
{
	static Console console;
	return console;
}

waki::Console::~Console()
{
	EndNcurses();
}

void waki::Console::Refresh()
{
	refresh();
}

void waki::Console::ClearScreen()
{
	clear();
}

void waki::Console::PauseApplication()
{
	waki::cout << "Press any key to continue . . .";
	getch();
}

void waki::Console::StopFor(unsigned milliseconds)
{
	napms(milliseconds);
}

void waki::Console::ResetCursorPosition()
{
	MoveCursorPosition(0, 0);
}

void waki::Console::MoveCursorPosition(unsigned y, unsigned x)
{
	move(y, x);
}

void waki::Console::MoveCursorPosition(Vector2D vec)
{
	move(vec.y, vec.x);
}

waki::Vector2DS waki::Console::GetCursorPosition()
{
	Vector2DS cursorPosition{0, 0};

	getyx(stdscr, cursorPosition.y, cursorPosition.x);

	return cursorPosition; 
}

void waki::Console::Timeout(int time)
{
	timeout(time);
}

bool waki::Console::SupportsColors()
{
	return has_colors();
}

void waki::Console::SetColor(Color color)
{
	if(!SupportsColors())
	{
		return;
	}
	DisableColor();
	attron(COLOR_PAIR(static_cast<int>(color)));
}

void waki::Console::DisableColor()
{	
	standend();
}

waki::Console::Console()
{
	BeginNcurses();
	HideCursor();
	DisableBuffering();
	EnableFuncKeys();
	DisableCharOutput();
	EnableColorMode();
}

void waki::Console::BeginNcurses()
{
	initscr();
}

void waki::Console::EndNcurses()
{
	endwin();
}

void waki::Console::HideCursor()
{
	curs_set(0);
}

void waki::Console::DisableBuffering()
{
	cbreak();
}

void waki::Console::EnableFuncKeys()
{
	keypad(stdscr, TRUE);
}

void waki::Console::DisableCharOutput()
{
	noecho();
}

bool waki::Console::EnableColorMode()
{
	if(!SupportsColors())
	{
		return false;
	}

	start_color();

	InitializeColor();

	return true;
}

void waki::Console::InitializeColor()
{
    const int backgroundColor = 2;
	init_color(backgroundColor, 30 * 1000 / 255, 30 * 1000 / 255, 46 * 1000 / 255); 

	init_pair(backgroundColor, static_cast<int>(Color::White), backgroundColor); 
	bkgd(COLOR_PAIR(backgroundColor));

	init_pair(static_cast<int>(Color::Whiteandblue), static_cast<int>(Color::White), static_cast<int>(Color::Blue));

	std::vector<Color> colors = {
		Color::LightPinkishLavender,
		Color::LightPink,
		Color::LightAquamarine,
		Color::White,
		Color::LightBlue,
		Color::CharcoalGray,
		Color::Blue,
		Color::DeepSkyBlue,
		Color::VividBlue,
		Color::Azure,
		Color::BrightVividBlue,
		Color::ForestGreen,
		Color::MediumGreenishBlue,
		Color::Teal,
		Color::BrightSkyBlue,
		Color::NeonGreen,
		Color::BrightMintGreen,
		Color::DeepRed,
		Color::Violet,
		Color::Purple,
		Color::BlueViolet,
		Color::MediumVioletBlue,
		Color::PeriwinkleBlue,
		Color::DarkRed,
		Color::PurpleViolet,
		Color::DeepPurple,
		Color::MediumPurple,
		Color::ScarletRed,
		Color::BrightFuchsia,
		Color::VividOrchid,
		Color::LavenderBlue,
		Color::Crimson,
		Color::PinkishPurple,
		Color::LightPurple,
		Color::LightPink2,
		Color::PaleBeige
    };

    for(auto color : colors)
	{
		init_pair(static_cast<int>(color), static_cast<int>(color), backgroundColor);
	}
}
#elif _WIN32
    
#include <iostream>
#include <Windows.h>

waki::Console& waki::Console::GetObject()
{
	static Console console;
	return console;
}

void waki::Console::ClearScreen()
{
	system("cls");
}

void waki::Console::PauseApplication()
{
	system("pause");
}

void waki::Console::StopFor(unsigned milliseconds)
{
	Sleep(milliseconds);
}

void waki::Console::ResetCursorPosition()
{
	SetCursorPosition(0, 0);
}

void waki::Console::SetCursorPosition(unsigned y, unsigned x)
{
	std::cout.flush();
	COORD newCursorPosition = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	SetConsoleCursorPosition(consoleHandle, newCursorPosition);
}

void waki::Console::SetCursorPosition(Vector2D vec)
{
	std::cout.flush();
	COORD newCursorPosition = { static_cast<SHORT>(vec.x), static_cast<SHORT>(vec.y) };
	SetConsoleCursorPosition(consoleHandle, newCursorPosition);
}

waki::Vector2DS waki::Console::GetCursorPosition()
{
	Vector2DS cursorPosition{0, 0};

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(consoleHandle, &csbi);
	cursorPosition = {csbi.dwCursorPosition.Y, csbi.dwCursorPosition.X};

	return cursorPosition; 
}

void waki::Console::SetWindowSize(SHORT width, SHORT height)
{
	SMALL_RECT windowArea = { 0, 0, width, height };
	COORD coord;
	coord.X = width;
	coord.Y = height;

	SetConsoleScreenBufferSize(consoleHandle, coord);
	SetConsoleWindowInfo(consoleHandle, TRUE, &windowArea);
}

void waki::Console::SetFontSettings(SHORT fontSize, const std::wstring& fontName)
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = fontSize;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, sizeof(L"Consolas"), fontName.c_str());

	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void waki::Console::SetTitle(const std::string& title)
{
	SetConsoleTitleA(title.c_str());
}

void waki::Console::SetColor(Color color)
{
	if (color == Color::Whiteandblue)
	{
		std::cout << "\033[48;5;" << static_cast<int>(Color::Blue) << "m\033[38;5;" << static_cast<int>(Color::White) << "m";
		return;
	}

	DisableColor();
	std::cout << "\033[38;5;" << static_cast<int>(color) << "m";
}

void waki::Console::DisableColor()
{
	std::cout << "\033[0m";
}

waki::Console::Console()
{ 	
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	consoleWindow = GetConsoleWindow();

	HideCursor();
	DisableScrollBars();
	DisableMaximizeButton();
	DisableWindowResizing();
}

void waki::Console::HideCursor()
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 100;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void waki::Console::DisableScrollBars()
{
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	GetConsoleScreenBufferInfo(consoleHandle, &bufferInfo);
	COORD newBuffetSize =
	{
		static_cast<SHORT>(bufferInfo.srWindow.Right - bufferInfo.srWindow.Left + 1),
		static_cast<SHORT>(bufferInfo.srWindow.Bottom - bufferInfo.srWindow.Top + 1)
	};

	SetConsoleScreenBufferSize(consoleHandle, newBuffetSize);
}

void waki::Console::DisableMaximizeButton()
{
	DWORD windowStyle = GetWindowLong(consoleWindow, GWL_STYLE);
	windowStyle &= ~WS_MAXIMIZEBOX;
	SetWindowLong(consoleWindow, GWL_STYLE, windowStyle);
	SetWindowPos(consoleWindow, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_FRAMECHANGED);
}

void waki::Console::DisableWindowResizing()
{
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}
#endif

namespace waki
{
	Console& cnsl = Console::GetObject();
}
