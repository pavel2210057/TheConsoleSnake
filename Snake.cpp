#include "Snake.hpp"
#include <algorithm>

MSnake::MSnake(MConsole& rConsole, SHORT length) :
	MRenderable(rConsole) {
	COORD consoleSize = rConsole.getConsoleInnerSize();

	this->headPosition = {
		consoleSize.X / 2,
		consoleSize.Y / 2
	};

	MSector head = { rConsole, this->headPosition };
	head.setDrawable((char*)this->drawable);
	head.setClearMask((char*)this->clearMask);

	this->sectors.push_back(head);
	this->consoleSize = this->pConsole->getConsoleInnerSize();

	while (length--)
		pushSector({ 0, -1 });
}

MSnake::~MSnake() = default;

void MSnake::pushSector() {
	pushSector({ 0, 0 });;
}

void MSnake::pushSector(COORD dir) {
	COORD newPos = this->sectors.back().getPosition() + dir;

	MSector sector = { *this->pConsole, newPos };
	sector.setDrawable((char*)this->drawable);
	sector.setClearMask((char*)this->clearMask);

	this->sectors.push_back(sector);
}

void MSnake::move(COORD dir) {
	move(dir.X, dir.Y);
}

void MSnake::move(int dx, int dy) {
	this->headPosition.X += this->sectorSize * dx;
	this->headPosition.Y += dy;

	//on wall intersection
	//X
	if (this->headPosition.X < 0)
		this->headPosition.X = this->consoleSize.X - this->sectorSize - 1;

	else if (this->headPosition.X + this->sectorSize > this->consoleSize.X - 1)
		this->headPosition.X = 0;
	//Y
	else if (this->headPosition.Y < 1)
		this->headPosition.Y = this->consoleSize.Y - 2;

	else if (this->headPosition.Y > this->consoleSize.Y - 2)
		this->headPosition.Y = 1;

	this->sectors.back().setPosition(this->headPosition);

	std::rotate(
		this->sectors.rbegin(),
		this->sectors.rbegin() + 1,
		this->sectors.rend()
	);
}

bool MSnake::isCollision() {
	for (auto it = this->sectors.begin() + 1; it != this->sectors.end(); ++it)
		if (this->headPosition == it->getPosition())
			return true;
	return false;
}

void MSnake::clear() {
	applyForAll(
		[](MSector sector) {
			sector.clear();
		}
	);
}

void MSnake::draw() {
	applyForAll(
		[](MSector sector) {
			sector.draw();
		}
	);
}

COORD MSnake::getHeadPosition() {
	return this->headPosition;
}

template <typename F>
void MSnake::applyForAll(F func) {
	std::for_each(this->sectors.begin(), this->sectors.end(), func);
}