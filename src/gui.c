#include <SDL.h>
#include <stdbool.h>
#include "gui.h"

//
//Initializes window and surface using Scene struct where holds adresses of created SDL Windows etc.
//
bool InitWindow(Scene* scene, int height, int width,
		int textureHeight,int textureWidth){

	SDL_Init(SDL_INIT_EVERYTHING);
	
	scene->window = SDL_CreateWindow( "CHIP-8 Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			width, height,
			SDL_WINDOW_SHOWN);
	//returns an error if window is not created
	if(scene->window == NULL) printf("oops see this-> %s\n", SDL_GetError());


	//scene->surface = SDL_GetWindowSurface(scene->window);
	//returns an error if surface is not created
	//if(scene->surface == NULL) printf("There was an error  See ->: %s \n", SDL_GetError());
	
	scene->renderer = SDL_CreateRenderer(scene->window,-1,SDL_RENDERER_ACCELERATED);
	if(scene->renderer == NULL) printf("There was an error with renderer -> %s \n",SDL_GetError());
	
	scene->texture = SDL_CreateTexture(scene->renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_STREAMING,
			textureWidth,textureHeight);
	SDL_RenderClear(scene->renderer);
	return true;
}

//
//Closes the application 
//
bool closeWindow(Scene* scene){
	SDL_DestroyTexture(scene->texture);
	SDL_DestroyRenderer(scene->renderer);
	SDL_DestroyWindow(scene->window);
	SDL_Quit();
}

void render(Scene* scene,chip8* chip){
	int pixelW = PIXEL_SCALE;
	int pixelH = PIXEL_SCALE;

		SDL_Rect rect;

		rect.w = pixelW;
		rect.h = pixelH;
		SDL_SetRenderDrawColor(scene->renderer,0,0,230,255);
		SDL_RenderClear(scene->renderer);
	//
	//if lags dont draw every off pixel just make everything black at the beginning	
	//
		for(int y = 0; y<CHIP8_SCREEN_HEIGHT;y++){
			for(int x = 0; x<CHIP8_SCREEN_WIDTH;x++){
				rect.x = x*PIXEL_SCALE;
				rect.y = y*PIXEL_SCALE;
				if(chip->display[y][x] == 0){
				
				}
				else{
					SDL_SetRenderDrawColor(scene->renderer,255,255,255,255);

					SDL_RenderFillRect(scene->renderer,&rect);
				}
			}
		}
	
	
	SDL_RenderPresent(scene->renderer);

}


