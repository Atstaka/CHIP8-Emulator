#include <SDL.h>
#include <stdbool.h>
#include "gui.h"

//
//Initializes window and surface using Scene struct where holds adresses of created SDL Windows etc.
//
bool InitWindow(Scene* scene, int height, int width){
	SDL_Init(SDL_INIT_EVERYTHING);
	
	scene->window = SDL_CreateWindow( "Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	//returns an error if window is not created
	if(scene->window == NULL) printf("oops see this-> %s\n", SDL_GetError());
	scene->surface = SDL_GetWindowSurface(scene->window);
	//returns an error if surface is not created
	if(scene->surface == NULL) printf("There was an error  See ->: %s \n", SDL_GetError());

	SDL_UpdateWindowSurface(scene->window);
	return true;
}

//
//Closes the application 
//
bool closeWindow(Scene* scene){

	SDL_DestroyWindow(scene->window);
	SDL_Quit();
}


