#include "Sector.hpp"

MSector::MSector(MConsole& rConsole, COORD position) :
	MRenderable(rConsole),
	position(position) {}

MSector::~MSector() = default;

void MSector::move(COORD offset) {
	clear();

	this->position.X += offset.X;
	this->position.Y += offset.Y;

	draw();
}

void MSector::setDrawable(char* drawable) {
	this->drawable = drawable;
	this->sectorSize = strlen(this->drawable);
}

void MSector::setClearMask(char* clearMask) {
	this->clearMask = clearMask;
}

void MSector::setPosition(COORD position) {
	move({
		position.X - this->position.X,
		position.Y - this->position.Y
	});
}

void MSector::clear() {
	this->pConsole->setCursorPosition(this->position);
	printf(this->clearMask);
}

void MSector::draw() {
	this->pConsole->setCursorPosition(this->position);
	printf(this->drawable);
}

COORD MSector::getPosition() {
	return this->position;
}

size_t MSector::getSectorSize() {
	return this->sectorSize;
}

COORD operator+(COORD left, COORD right) {
	return {
		left.X + right.X,
		left.Y + right.Y
	};
}

bool operator==(COORD left, COORD right) {
	return
		left.X == right.X &&
		left.Y == right.Y;
}