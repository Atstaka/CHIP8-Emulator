#include <stdint.h>
#include <stdbool.h>
#define CHIP8_MEMORY_SIZE 4096
#define CHIP8_SCREEN_HEIGHT 64
#define CHIP8_SCREEN_WIDTH 32
#define DELAY_TIMER 60//frames per sec 60hz
#define V_REGISTER_AMOUNT 16
#define PC_START 0x200
#define IKEY_AMOUNT 16
#define STACK_AMOUNT 16
#define CHIP8_SCREEN_SIZE (CHIP8_SCREEN_HEIGHT * CHIP8_SCREEN_WIDTH)

//Decoding macros
#define INS_X(instruction) ((instruction& 0x0F00) >>8)
#define INS_Y(instruction) ((instruction & 0x00F0) >> 4)
#define INS_N(instruction) (instruction & 0x000F)
#define INS_NN(instruction) (instruction & 0x00FF)
#define INS_NNN(instruction) (instruction & 0x0FFF)


typedef struct chip8{
	uint8_t memory[4096];
	uint16_t I; //index register
	uint16_t stack[STACK_AMOUNT];
	uint8_t stackPointer;
	uint8_t delayTimer;
	uint8_t soundTimer;
	uint8_t V[V_REGISTER_AMOUNT];
	uint16_t PC;
	uint8_t keys[IKEY_AMOUNT];
	uint16_t display[CHIP8_SCREEN_SIZE];
} chip8;

void initialize(chip8* chip);
bool loadROM(chip8* chip, const char* file);
uint16_t decode(chip8* chip);
void excecute(chip8* chip);


