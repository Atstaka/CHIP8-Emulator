#include "gui.h"
int main(int argc, char *argv[]){
	Scene screen;
	InitWindow(&screen,720,1200);
	bool loop = true;
	//main loop
	while (loop){
		//events loop
		while(SDL_PollEvent(&screen.event)){	
			if(screen.event.type == SDL_QUIT) {
				loop = false;
				closeWindow(&screen);
				
			}
		}
		SDL_Delay(16);
	}
	
	return 0;
}
