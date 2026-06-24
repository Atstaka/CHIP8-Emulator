#include <SDL.h>
#include <stdbool.h>
#include "gui.h"


bool InitWindow(Scene* scene, int height, int width){
	SDL_Init(SDL_INIT_EVERYTHING);

	scene->window = SDL_CreateWindow( "Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

	if(scene->window == NULL) printf("oops see this-> %s\n", SDL_GetError());
	scene->surface = SDL_GetWindowSurface(scene->window);
	if(scene->surface == NULL) printf("There was an error  See ->: %s \n", SDL_GetError());
	
	SDL_UpdateWindowSurface(scene->window);
	return true;
}

bool deleteWindow(SDL_Window* window){

}


