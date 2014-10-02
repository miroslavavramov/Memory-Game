#ifndef GAMESTART_H_
#define GAMESTART_H_
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
//#include <string>
//#include <iostream>
//#include <ctime>
#include <vector>
#include "StartBackgroundTexture.h"
#include "Buttons.h"


using namespace std;

class GameStart {
public:
	GameStart();
	virtual ~GameStart();
//	void Init(SDL_Renderer*);

	void Init(SDL_Renderer*);
	void Draw();
	void Update();
	void GetButton();
	bool Running();

//private:
//	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	StartBackgroundTexture backGroundMenu;

	vector<Buttons> m_buttonSet;
	Buttons m_buttonsMenu;
	bool m_bRunning;

};

#endif /* GAME_H_ */
