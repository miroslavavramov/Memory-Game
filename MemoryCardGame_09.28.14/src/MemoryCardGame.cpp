#include "Game.h"

// our Game object
Game* g_game = 0;
int main(int argc, char* argv[]) {
	g_game = new Game();
	g_game->Init("Memory_;)", 100, 100, 640, 480, SDL_WINDOW_MAXIMIZED);

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
