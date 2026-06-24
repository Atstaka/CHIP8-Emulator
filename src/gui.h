#include <SDL.h>
#include <stdbool.h>
#include "CHIP8.h"

#define PIXEL_SCALE 10
typedef struct{
	SDL_Window* window;
	SDL_Event event;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
} Scene;

bool InitWindow(Scene* scene, int height, int width, int textureHeight, int textureWidth);

bool closeWindow(Scene* scene);

void render(Scene* scene, chip8* chip);

