#include <stdint.h>

#define CHIP8_MEMORY_SIZE = 4096;
#define CHIP8_SCREEN_HEIGHT = 64;
#define CHIP8_SCREEN_WIDTH = 32;
#define DELAY_TIMER = 60;//frames per sec 60hz
#define V_REGISTER_AMOUNT = 16;
#define PC_START = 200;
#define IKEY_AMOUNT = 16;
#define STACK_AMOUNT = 16;
#define CHIP8_SCREEN_SIZE = CHIP8_SCREEN_HEIGHT * CHIP8_SCREEN_WIDTH;
typdef struct chip8{
	uint8_t memory[4096];
	uint16_t I; //index register
	uint16_t stack[STACK_AMOUNT];
	uint8_t stackPointer;
	uint8_t delayTimer;
	uint8_t soundTimer;
	uint16_t V[V_REGISTER_AMOUNT];
	uint16_t PC;
	uint8_t keys[IKEY_AMOUNT];
	uint16_t display[CHIP8_SCREEN_SIZE];
} chip8;
