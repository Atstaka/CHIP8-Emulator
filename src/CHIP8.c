#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "CHIP8.h"

void initialize(chip8* chip){
	chip->PC = PC_START;
	chip->I = 0;
	chip->stackPointer = 0;
}

bool loadROM(chip8* chip, const char* filepath){
	FILE *file= fopen(filepath,"rb");
	if(file == NULL){
		fprintf(stderr, "Couldn't open the file \n");
		return false;
	}
	//checking if file size is small enough
	fseek(file,0,SEEK_END);
	long file_size = ftell(file);
	fseek(file,0,SEEK_SET);
	size_t max_size = CHIP8_MEMORY_SIZE - PC_START;
	if(file_size> max_size){
		fprintf(stderr,"File is too big\n");
		fclose(file);
		return false;
	}
	//loading ROM to memory
	int index = 0;
	while(index<file_size){

		chip->memory[PC_START + index] = fgetc(file);
		index++;
	}	
	fclose(file);
	return true;
}

void cycle(chip8* chip){
	//TODO	
}


