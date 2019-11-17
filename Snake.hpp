#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "Sector.hpp"
#include <vector>

class MSnake : public MRenderable {
	std::vector<MSector> sectors;
	const char* drawable = "()";
	const char* clearMask = "  ";
	const SHORT sectorSize = 2;
	COORD headPosition;
	COORD consoleSize;
public:
	MSnake(MConsole& rConsole, SHORT length);

	~MSnake();

	void pushSector(COORD dir);

	void pushSector();

	void move(COORD dir);

	void move(int dx, int dy);

	bool isCollision();

	virtual void clear() final;

	virtual void draw() final;

	COORD getHeadPosition();
private:
	template <typename F>
	void applyForAll(F func);
};

#endif //!SNAKE_HPP