#pragma once

#include "ColorEnumerations.h"
#include <utility>
#include "Vector2D.h"

#ifdef __linux__

namespace waki
{
	class Console
	{
	public:
		static Console& GetObject();

		~Console();
		void Refresh();

		void ClearScreen();
		void PauseApplication();
		void StopFor(unsigned milliseconds);

		void ResetCursorPosition();
		void MoveCursorPosition(unsigned y, unsigned x);
		void MoveCursorPosition(Vector2D vec);
		Vector2DS GetCursorPosition();

		void Timeout(int time);

		bool SupportsColors();
		void SetColor(Color color);
		void DisableColor();
	private:
		Console();

		Console(Console&) = delete;
		Console(Console&&) = delete;
		Console& operator=(Console&) = delete;
		Console& operator=(Console&&) = delete;

		void BeginNcurses();
		void EndNcurses();

		void HideCursor();
		void DisableBuffering();
		void EnableFuncKeys();
		void DisableCharOutput();
		bool EnableColorMode();
		
		void InitializeColor();
	};
}
#elif _WIN32

#include <string>
#include <Windows.h>

namespace waki
{
	class Console
	{
	public:	
		static Console& GetObject();

		Console(Console&) = delete;
		Console(Console&&) = delete;
		Console& operator=(Console&) = delete;
		Console& operator=(Console&&) = delete;

		void ClearScreen();
		void PauseApplication();
		void StopFor(unsigned milliseconds);

		void ResetCursorPosition();
		void SetCursorPosition(unsigned y, unsigned x);
		void SetCursorPosition(Vector2D vec);
		Vector2DS GetCursorPosition();

		void SetWindowSize(SHORT width, SHORT height);
		void SetFontSettings(SHORT fontSize, const std::wstring& fontName);
		void SetTitle(const std::string& title);

		void SetColor(Color color);
		void DisableColor();
	private:
		Console();

		void HideCursor();
		void DisableScrollBars();
		void DisableMaximizeButton();
		void DisableWindowResizing();
	
		HANDLE consoleHandle;
		HWND consoleWindow;
	};
}
#endif


namespace waki
{
	extern Console& cnsl;
}
