#include "gui.h"
int main(int argc, char *argv[]){
	Scene screen;
	chip8 chip;
	initialize(&chip);

	InitWindow(&screen,320,640,20,20);
	bool loop = true;
	
	bool ttemp =loadROM(&chip,"/home/Atstaka/Documents/Projects/C/CHIP-8/1-chip8-logo.ch8");	
	//loadROM(&chip,"/home/Atstaka/Documents/Projects/C/CHIP-8/IBMLogo.ch8");
	#//main loop
	while (loop){
		//events loop
		while(SDL_PollEvent(&screen.event)){	
			if(screen.event.type == SDL_QUIT) {
				loop = false;
				
			}
			
		}
			excecute(&chip);
			render(&screen,&chip);
		
		SDL_Delay(16);
	}

	closeWindow(&screen);
	
	return 0;
}
