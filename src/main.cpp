#include "render_window.hpp"
#include "entity.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
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

	SDL_Texture* grass_texture = render_window.LoadTexture("res/grass.png");

	Entity platform(50, 100, grass_texture);

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
		render_window.Render(platform);
		render_window.Display();
	}

	SDL_DestroyTexture(grass_texture);
	render_window.CleanUp();
	SDL_Quit();
	return 0;
}