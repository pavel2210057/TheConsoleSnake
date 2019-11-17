#ifndef GAME_HPP
#define GAME_HPP

#include "Snake.hpp"
#include "Eat.hpp"

//game params
#define SNAKE_INIT_LEN 5
#define SNAKE_INIT_DIR { 0, 1 }
#define SCORE_OUTPUT_POS { 0, 0 }
#define DELAY 100

//control
#define EXIT_KEY   'P'
#define UP_KEY     'W'
#define DOWN_KEY   'S'
#define LEFT_KEY   'A'
#define RIGHT_KEY  'D'
#define COLOR1_KEY '1'
#define COLOR2_KEY '2'
#define COLOR3_KEY '3'

//console params
#define COLOR1 FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define COLOR2 FOREGROUND_RED   | FOREGROUND_INTENSITY
#define COLOR3 FOREGROUND_BLUE  | FOREGROUND_INTENSITY
#define OUTER_SIZE { 60, 30 }
#define INNER_SIZE { 61, 31 }

class MGame {
	MConsole* pConsole;
	struct SnakeData {
		MSnake snake;
		COORD dir;
	} *pSnakeData;
	MEat eat;
	size_t score;
public:
	MGame(MConsole& rConsole);

	~MGame();

	void run();
private:
	bool render();

	void updateScore();

	bool control();
};

#endif //!GAME_HPP