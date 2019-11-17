#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <Windows.h>
#include <cstdio>

class MConsole {
	HANDLE hin, hout;
	HWND host;
public:
	MConsole();

	~MConsole();

	void setCursorVisible(bool isVisible);

	void setConsoleOuterSize(COORD size);

	void setConsoleInnerSize(COORD size);

	void setConsoleColor(int color);

	void setCursorPosition(COORD position);

	bool isKeyPressed(BYTE key);

	void alignWindowByCenter();

	COORD getConsoleInnerSize();

	COORD getConsoleOuterSize();
private:
	COORD getWindowSize(HWND window);
};

#endif //!CONSOLE_HPP