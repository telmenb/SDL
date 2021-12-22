#include "graphics.hpp"
#include "entity.hpp"
#include "board.hpp"
#include "mouse.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

//Game refresh rate
const int FPS = 60;

//Event handler
SDL_Event event;

//Mouse object
Mouse mouse;

//Game loop flag
bool running = true;

//Framerate-limiter
Uint32 starting_tick = 0;

void Init() {
	if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) 
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());

	if ( !IMG_Init(IMG_INIT_PNG) )
		printf("SDL_Image could not be initialized! SDL_Error: %s\n", SDL_GetError());

	if ( TTF_Init() != 0 )
		printf("SDL_ttf could not be initialized! SDL_Error: %s\n", SDL_GetError());
}

int main( int argc, char* args[] ) {
	Board board;
	std::cout << board << std::endl;

	Init();
	Graphics graphics("Mancala", SCREEN_WIDTH, SCREEN_HEIGHT);

	if (!graphics.SplashScreen(&event)) {
		SDL_Quit();
		return 0;
	}
	
	while (running) {
		starting_tick = SDL_GetTicks();

		//Event handler
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
				break;
			}

			if (event.type == SDL_MOUSEBUTTONDOWN) {
				int pocket_num = mouse.GetPocketNum(&event);
				try {
					board.StartMove(pocket_num);
				} catch (const std::runtime_error& error) {
					//Do stuff
				}
				std::cout << board << std::endl;
			}
		}

		//Framerate limiter
		if ((1000 / FPS) > SDL_GetTicks() - starting_tick) {
			SDL_Delay(1000 / FPS - (SDL_GetTicks() - starting_tick));
		}

		graphics.Clear();
		graphics.RenderEntities(board);
		graphics.RenderGameScore(board);
		graphics.RenderGameText(board);
		graphics.Display();

		if (board.CheckForWinner()) {
			running = false;
		}
	}
	SDL_Quit();
	return 0;
}