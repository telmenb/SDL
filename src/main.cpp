#include "render_window.hpp"
#include "entity.hpp"
#include "board.hpp"
#include "mouse.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <vector>

//Game refresh rate
const int FPS = 60;

//Event handler
SDL_Event event;

TTF_Font font;

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

	if ( TTF_Init() != 0)
		printf("SDL_ttf could not be initialized! SDL_Error: %s\n", SDL_GetError());
}

int main( int argc, char* args[] ) {
	Board board;
	std::cout << board << std::endl;

	Init();
	RenderWindow render_window("Mancala", SCREEN_WIDTH, SCREEN_HEIGHT);

	while ( running ) {
		starting_tick = SDL_GetTicks();

		while ( SDL_PollEvent(&event) ) {
			//Event handler
			if (event.type == SDL_QUIT) {
				running = false;
				break;
			}

			if (event.type == SDL_MOUSEBUTTONDOWN) {
				//TODO: Mouse events
				int pocket_num = mouse.GetPocketNum(&event);
				try {
					board.StartMove(pocket_num);
				} catch (const std::runtime_error& error) {
					//Do stuff
				}
				std::cout << board << std::endl;
			}
		}

		// Framerate limiter
		if ( (1000 / FPS) > SDL_GetTicks() - starting_tick ) {
			SDL_Delay(1000 / FPS - (SDL_GetTicks() - starting_tick));
		}

		if (board.CheckForWinner()) running = false;

		render_window.Clear();
		render_window.RenderEntities(board);
		render_window.Display();
	}
	SDL_Quit();
	return 0;
}