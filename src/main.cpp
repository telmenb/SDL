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

void Init() {
	if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) 
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());

	if ( !IMG_Init(IMG_INIT_PNG) )
		printf("SDL_Image could not be initialized! SDL_Error: %s\n", SDL_GetError());
}

int main( int argc, char* args[] ) {
	Init();

	RenderWindow render_window("Mancala", SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_Texture* board_texture = render_window.LoadTexture("res/board.png");

	Entity board(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, board_texture); //special constructor

	SDL_Texture* stone_sprite = render_window.LoadTexture("res/stone_sprite.png");

	std::vector<Entity> entities;

	//TODO:
	//Move initialization and changing of entites to render_window
	//Possibly handle by passing in board array by reference
	for (size_t i = 0; i < 6; i++) {
		entities.push_back(Entity(245 + (i * 210), 20, 160 * 3, 0, stone_sprite));
		entities.push_back(Entity(245 + (i * 210), 200, 160 * 3, 0, stone_sprite));
	}

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

		render_window.Render(board);
		for (size_t i = 0; i < entities.size(); i++) {
			render_window.Render(entities.at(i));
		}
		render_window.Display();
	}

	SDL_DestroyTexture(board_texture);
	SDL_DestroyTexture(stone_sprite);
	render_window.CleanUp();
	SDL_Quit();
	return 0;
}