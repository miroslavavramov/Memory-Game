#include "Game.h"

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
// our Game object
Game* g_game = 0;
int main(int argc, char* argv[]) {
	g_game = new Game();
	g_game->Init("Memory_;)", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	g_game->GetCardFromDeck();
//main loop

	while (g_game->Running()) {

		g_game->Update();

		g_game->Draw();

	} //end main loop

//	exit the game
//	g_game->clean();

	return 0;
}
