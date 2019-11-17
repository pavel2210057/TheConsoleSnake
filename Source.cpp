#include "Game.hpp"

int main() {
	MConsole console;
	console.setCursorVisible(false);
	console.setConsoleColor(COLOR1);
	console.setConsoleOuterSize(OUTER_SIZE);
	console.setConsoleInnerSize(INNER_SIZE);
	console.alignWindowByCenter();

	MGame game(console);
	game.run();

	return 0;
}