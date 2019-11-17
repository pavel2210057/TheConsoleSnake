#include "Eat.hpp"
#include <ctime>

MEat::MEat(MConsole& rConsole) :
	MSector(rConsole) {
	this->consoleSize = rConsole.getConsoleInnerSize();

	this->drawable = (char*)"<>";
	this->clearMask = (char*)"  ";

	srand((UINT)time(nullptr));
}

MEat::~MEat() = default;

void MEat::spawn() {
	COORD
		randomCoord = {
			rand() / 2 % (this->consoleSize.X - 2),
			1 + rand() % (this->consoleSize.Y - 3)
		};

	if (randomCoord.X % 2 != 0)
		--randomCoord.X;

	this->position = randomCoord;
}