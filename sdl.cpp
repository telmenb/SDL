#include "sdl.hpp"

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 480;
//Game refresh rate
const int FPS = 60;

//The window we'll be rendering to
SDL_Window* window = NULL;
	
//The surface contained by the window
SDL_Surface* screen_surface = NULL;

//The image we will load and show on the screen
SDL_Surface* tmp_surface = NULL;

//Event handler
SDL_Event event;

//Game loop flag
bool running = true;

//Framerate-limiter
Uint32 starting_tick = 0;

int main( int argc, char* args[] ) {
	//Start up SDL and create window
	if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());

	//Create window
	window = SDL_CreateWindow("Mancala",
								SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED,
								SCREEN_WIDTH,
								SCREEN_HEIGHT,
								0);
	if( window == NULL ) {
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
	}

	//Get window surface
	screen_surface = SDL_GetWindowSurface(window);
	if ( screen_surface == NULL ) printf("Unable to obtain screen_surface: %s\n", SDL_GetError());

	//Load splash image
	tmp_surface = SDL_LoadBMP("mancala.bmp");
	if( tmp_surface == NULL ) printf("Unable to load image %s! SDL Error: %s\n", "mancala_board.bmp", SDL_GetError());

	while ( running ) {
		//Runtime used to limit framerate
		starting_tick = SDL_GetTicks();

		//Apply the image
		SDL_BlitSurface(tmp_surface, NULL, screen_surface, NULL);
	
		//Update the surface
		SDL_UpdateWindowSurface(window);

		while ( SDL_PollEvent(&event) ) {
			//Event handler
			switch ( event.type ) {
				case SDL_QUIT:
					running = false;
					break;
			}
			
			//Framerate limiter
			if ( (1000 / FPS) > SDL_GetTicks() - starting_tick ) {
				SDL_Delay(1000 / FPS - (SDL_GetTicks() - starting_tick));
			}
		}
	}

	//Deallocate surface
	SDL_FreeSurface(tmp_surface);
	SDL_FreeSurface(screen_surface);
	tmp_surface = NULL;
	screen_surface = NULL;

	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	//Quit SDL subsystems
	SDL_Quit();
	return 0;
}