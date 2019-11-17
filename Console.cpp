#include "Console.hpp"

MConsole::MConsole() : 
	hin(GetStdHandle(STD_INPUT_HANDLE)),
	hout(GetStdHandle(STD_OUTPUT_HANDLE)),
	host(GetConsoleWindow()) {}

MConsole::~MConsole() = default;

void MConsole::setCursorVisible(bool isVisible) {
	try {
		CONSOLE_CURSOR_INFO info;
		if (!GetConsoleCursorInfo(
			this->hout,
			&info
		))
			throw GetLastError();

		info.bVisible = isVisible;
		
		if (!SetConsoleCursorInfo(
			this->hout,
			&info
		))
			throw GetLastError();
	} catch (DWORD code) {
		printf("Error code: %d\n", code);
	}
}

void MConsole::setConsoleOuterSize(COORD size) {
	try {
		COORD maxSize = getConsoleInnerSize();
			
		SMALL_RECT rect = {
			0,
			0,
			size.X,
			size.Y
		};

		if (!SetConsoleWindowInfo(
			this->hout,
			TRUE,
			&rect
		))
			throw GetLastError();
	}
	catch (DWORD code) {
		printf("Error code: %d\n", code);
	}
}

void MConsole::setConsoleInnerSize(COORD size) {
	try {
		if (!SetConsoleScreenBufferSize(this->hout, size))
			throw GetLastError();
	}
	catch (DWORD code) {
		printf("Error code: %d\n", code);
	}
}

void MConsole::setConsoleColor(int color) {
	SetConsoleTextAttribute(
		this->hout,
		color
	);
}

void MConsole::setCursorPosition(COORD position) {
	try {
		if (!SetConsoleCursorPosition(this->hout, position))
			throw GetLastError();
	}
	catch (DWORD code) {
		printf("Error code: %d\n", code);
	}
}

bool MConsole::isKeyPressed(BYTE key) {
	return GetAsyncKeyState(key);
}

void MConsole::alignWindowByCenter() {
	try {
		COORD 
			desktopSize = getWindowSize(GetDesktopWindow()),
			consoleSize = getConsoleOuterSize();
		
		if (!SetWindowPos(
			this->host,
			HWND_TOPMOST,
			desktopSize.X / 2 - consoleSize.X / 2,
			desktopSize.Y / 2 - consoleSize.Y / 2,
			0,
			0,
			SWP_NOSIZE
		))
			throw GetLastError();
	}
	catch (DWORD code) {
		printf("Error code: %d\n", code);
	}
}

COORD MConsole::getWindowSize(HWND window) {
	COORD size;

	try {
		RECT rect;

		if (!GetWindowRect(window, &rect))
			throw GetLastError();

		size.X = (SHORT)(rect.right - rect.left);
		size.Y = (SHORT)(rect.bottom - rect.top);
	}
	catch (DWORD code) {
		printf("Error code: %d\n", code);
	}

	return size;
}

COORD MConsole::getConsoleInnerSize() {
	COORD size;

	try {
		CONSOLE_SCREEN_BUFFER_INFO info;

		if (!GetConsoleScreenBufferInfo(
			this->hout,
			&info
		))
			throw GetLastError();

		size = info.dwMaximumWindowSize;
	}
	catch (DWORD code) {
		printf("Error code: %d\n", code);
	}

	return size;
}

COORD MConsole::getConsoleOuterSize() {
	return getWindowSize(this->host);
}