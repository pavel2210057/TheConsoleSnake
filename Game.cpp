#include "Game.hpp"
#include <ctime>

MGame::MGame(MConsole& rConsole) :
	pConsole(&rConsole),
	eat({ rConsole }),
	score(0) {
	this->pSnakeData = new SnakeData {
		{ rConsole, SNAKE_INIT_LEN },
		SNAKE_INIT_DIR
	};

	//render snake
	this->pSnakeData->snake.draw();
	
	//spawn first food
	this->eat.spawn();

	//render init score
	updateScore();
}

MGame::~MGame() = default;

void MGame::run() {
	while (render() && control())
		Sleep(DELAY);
}

bool MGame::render() {
	//snake render
	this->pSnakeData->snake.move(this->pSnakeData->dir);
	
	//food render
	this->eat.draw();

	//on food eaten
	if (this->pSnakeData->snake.getHeadPosition() == this->eat.getPosition()) {
		++this->score;

		//push snake sector
		this->pSnakeData->snake.pushSector();

		//respawn food
		this->eat.spawn();

		//score update
		updateScore();
	}
	//on snake collision
	else if (this->pSnakeData->snake.isCollision())
		return false;

	return true;
}

void MGame::updateScore() {
	this->pConsole->setCursorPosition(SCORE_OUTPUT_POS);
	printf("Score: %d", this->score);
}

bool MGame::control() {
	//on exit
	if (this->pConsole->isKeyPressed(EXIT_KEY))
		return false;

	//snake control
	else if (
		this->pConsole->isKeyPressed(LEFT_KEY) &&
		this->pSnakeData->dir.X != 1)
		this->pSnakeData->dir = { -1, 0 };
	else if (
		this->pConsole->isKeyPressed(RIGHT_KEY) &&
		this->pSnakeData->dir.X != -1)
		this->pSnakeData->dir = { 1, 0 };
	else if (
		this->pConsole->isKeyPressed(UP_KEY) &&
		this->pSnakeData->dir.Y != 1)
		this->pSnakeData->dir = { 0, -1 };
	else if (
		this->pConsole->isKeyPressed(DOWN_KEY) &&
		this->pSnakeData->dir.Y != -1)
		this->pSnakeData->dir = { 0, 1 };

	//console control
	else if (this->pConsole->isKeyPressed(COLOR1_KEY))
		this->pConsole->setConsoleColor(COLOR1);
	else if (this->pConsole->isKeyPressed(COLOR2_KEY))
		this->pConsole->setConsoleColor(COLOR2);
	else if (this->pConsole->isKeyPressed(COLOR3_KEY))
		this->pConsole->setConsoleColor(COLOR3);

	return true;
}