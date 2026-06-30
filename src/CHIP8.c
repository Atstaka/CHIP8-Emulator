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

//reads from memory and
//returns instructions from memory
uint16_t fetch(chip8* chip){
	//could be written in one line 
	//added first 8 byte instruction from memory
	uint16_t instruction = chip->memory[chip->PC];
	// shifted to left 
	instruction = instruction<<8;
	// add last 8 bytes from next adress
	instruction = instruction | chip->memory[chip->PC+1];
	//moved pc to next address
	chip->PC += 2;
	
	return instruction;
}
void excecute(chip8* chip){
	uint16_t instruction = fetch(chip);
	/*
	 * Commented because i used macros to save memory 
	//First Nibble. Tells what kind of instruction it is
	uint8_t opcode = instruction & 0xF000;
	//Second Nibble. Looks for one of registers
	uint8_t X = instruction & 0x0F00;
	//Third Nibble also looks for one of registers
	uint8_t Y = instruction & 0x00F0;
	//Fourth Nibble. 4 Bit number
	uint8_t N = instruc16tion & 0x000F;
	//Second Byte, 8 bit immediate memory address
	uint8_t NN = instruction & 0x00FF;
	//Second, third and fourth Nubbles for 12 bit memory adress
	uint16_t = NNN = instruction & 0x0FFF;
*/
	switch(instruction & 0xF000){
		case 0x0000:
			// clear screen instruction
			// sets every bit from start of the array to 0
			if(instruction == 0x00E0){
				uint16_t *pdisplay = &chip->display[0][0];
				for(int i =0; i<CHIP8_SCREEN_SIZE;i++){
					*(pdisplay+i) =0;
				}				
			}
			//jumps to the last address from stack 
			else if (instruction == 0x00EE){
				chip->stackPointer--;
				chip->PC = chip->stack[chip->stackPointer];
			}
			break;
		//Jump instruction, jumps to NN
		case 0x1000:
			chip->PC = INS_NNN(instruction);
			break;
		// Saves pc in stack and changes PC. Used mostly with 0x00EE
		case 0x2000:
			chip->stack[chip->stackPointer] = chip->PC;
			chip->stackPointer++;
			chip->PC = INS_NNN(instruction);
			break;
		// skips if vx = nn
		case 0x3000:
			if(chip->V[INS_X(instruction)] == INS_NN(instruction)) chip->PC+=2;
			break;
		//skips if vx != nn
		case 0x4000:
			if(chip->V[INS_X(instruction)] != INS_NN(instruction)) chip->PC+=2;
			break;
		//skips if vx = vy
		case 0x5000:
			if(chip->V[INS_X(instruction)] == chip->V[INS_Y(instruction)]) chip->PC+=2;
			break;
		//skips if vx != vy
		case 0x9000:
			if(chip->V[INS_X(instruction)] != chip->V[INS_Y(instruction)]) chip->PC+=2;
			break;
		//Sets vx to NN
		case 0x6000:
			chip->V[INS_X(instruction)] = INS_NN(instruction);
			break;
		//Adds NN to vx
		case 0x7000:
			chip->V[INS_X(instruction)] += INS_NN(instruction);
			break;
		// Sets I to NNN
		case 0xA000:
			chip->I = INS_NNN(instruction);
			break;
		//Display instruction
		//Draws n pixel tall sprites from memory[I]
		//starts at vx and vy 
		case 0xD000:{
			// x and y coordinates
			uint8_t vx = chip->V[INS_X(instruction)];
			uint8_t vy = chip->V[INS_Y(instruction)];
			
			uint8_t n = INS_N(instruction);
			chip->V[0xF] = 0;
			
			for(int row = 0; row<n; row++){
				//for each row takes sprite from memory with basis of I
				uint8_t sprite = chip->memory[chip->I + row];
				//coordinate of y to start drawing from
				uint8_t y=(vy+row)%CHIP8_SCREEN_HEIGHT;
				for(int col = 0; col<8; col++){
					//cordinate of x to start drawing from
					uint8_t x=(vx+col)%CHIP8_SCREEN_WIDTH;
					//checks each bit in sprite and changes its state if it should 
					if(sprite & (0x80 >> col)){
						//checks collision if bit is going to be drawn an is already on
						//then it collides with another object
						//in this case sets vf flag to 1
						if(chip->display[y][x] == 1 ){
							chip->V[0xF] = 1;
						}

						//draws bit through xor
						chip->display[y][x] ^=1;

					}
					

				}
			}


			break;
			    }
		// Logical and Arithmetic Operations
		case 0x8000:{
				switch(INS_N(instruction)){
					case 0:
						chip->V[INS_X(instruction)] = chip->V[INS_Y(instruction)];
						break;
					case 1:
						chip->V[INS_X(instruction)] = chip->V[INS_Y(instruction)] | 
										chip->V[INS_X(instruction)] ;
						break;
					case 2:
						chip->V[INS_X(instruction)] = chip->V[INS_X(instruction)] &
										chip->V[INS_Y(instruction)];
						break;
					case 3:
						chip->V[INS_X(instruction)] =chip->V[INS_X(instruction)] ^
										chip->V[INS_Y(instruction)];
						break;
					case 4:{
						       //save sum in as 16 incase of overflow
						uint16_t add =chip->V[INS_X(instruction)] +
							chip->V[INS_Y(instruction)];
						//save last significant bit to vx
						chip->V[INS_X(instruction)] = add &0xFF;
						//change overflow flag
						if(add>255) chip->V[0xF] =1;
						else chip->V[0xF] =0;
						
						break;
					       }
					case 5:{
						uint8_t x =chip->V[INS_X(instruction)];
						uint8_t y = chip->V[INS_Y(instruction)];
						if(x<y) chip->V[0xF] = 0;
						else chip->V[0xF] =1;
						chip->V[INS_X(instruction)] = x-y;
						
						break;
					       }
					case 7:{
						
						uint8_t x=chip->V[INS_X(instruction)];
						uint8_t y = chip->V[INS_Y(instruction)];
						if(y<x) chip->V[0xF] = 0;
						else chip->V[0xF] =1;
						chip->V[INS_X(instruction)] = y-x;
						
						break;}
					
					//I Did not implemented case 8 and e


				}
			    	break;
			    }
		//sets Index register to value NNN
		case 0xA: chip->I = INS_NNN(instruction);
				break;
		

			    	}

}






