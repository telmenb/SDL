#include "render_window.hpp"
#include "entity.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <vector>

//Screen dimension constants
const int SCREEN_WIDTH = 1700;
const int SCREEN_HEIGHT = 380;
//Game refresh rate
const int FPS = 60;

//Event handler
SDL_Event event;

//Game loop flag
bool running = true;

//Framerate-limiter
Uint32 starting_tick = 0;

int main( int argc, char* args[] ) {
	if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) 
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());

	if ( !IMG_Init(IMG_INIT_PNG) )
		printf("SDL_Image could not be initialized! SDL_Error: %s\n", SDL_GetError());

	RenderWindow render_window("Mancala", SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_Texture* board_texture = render_window.LoadTexture("res/board_reduced.png");

	Entity board(0, 0, board_texture);

	// std::vector<Entity> entities;

	// for (int i = 0; i < SCREEN_WIDTH / 64; i++) {
	// 	entities.push_back(Entity(i * 32, 288, grass_texture));
	// }

	while ( running ) {
		starting_tick = SDL_GetTicks();

		while ( SDL_PollEvent(&event) ) {
			//Event handler
			if (event.type == SDL_QUIT) {
				running = false;
				break;
			}
		}
		// Framerate limiter
		if ( (1000 / FPS) > SDL_GetTicks() - starting_tick ) {
			SDL_Delay(1000 / FPS - (SDL_GetTicks() - starting_tick));
		}

		render_window.Clear();

		// for (Entity& entity : entities) {
		// 	render_window.Render(entity);
		// }

		render_window.Render(board);

		render_window.Display();
	}

	SDL_DestroyTexture(board_texture);
	render_window.CleanUp();
	SDL_Quit();
	return 0;
}