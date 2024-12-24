#pragma once

#include "ColorEnumerations.h"
#include <utility>
#include "Vector2D.h"

#ifdef __linux__

#include <ncurses.h>

namespace utl
{
	class Console
	{
	public:
		Console();
		~Console();
		void Refresh();

		void ClearScreen();
		void PauseApplication();
		void StopFor(unsigned milliseconds);

		void ResetCursorPosition();
		void SetCursorPosition(unsigned y, unsigned x);
		Vector2DS GetCursorPosition();

		bool SupportsColors();
		void SetColor(Color color);
		void DisableColor();
	private:
		void BeginNcurses();
		void EndNcurses();

		void HideCursor();

		bool EnableColorMode();
		void InitializeColor();
	};
	extern Console cnsl;
}
#elif _WIN32

#include <string>
#include <Windows.h>

namespace utl
{
	class Console
	{
	public:
		Console();

		void ClearScreen();
		void PauseApplication();
		void StopFor(unsigned milliseconds);

		void ResetCursorPosition();
		void SetCursorPosition(unsigned y, unsigned x);
		Vector2DS GetCursorPosition();

		void SetWindowSize(SHORT width, SHORT height);
		void SetFontSettings(SHORT fontSize, const std::wstring& fontName);
		void SetTitle(const std::string& title);

		void SetColor(Color color);
		void DisableColor();
	private:
		void HideCursor();
		void DisableScrollBars();
		void DisableMaximizeButton();
		void DisableWindowResizing();
	
		HANDLE consoleHandle;
		HWND consoleWindow;
	};
	extern Console cnsl;
}
#endif