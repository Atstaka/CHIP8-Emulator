#include <SDL.h>
#include <stdbool.h>
typedef struct{
	SDL_Window* window;
	SDL_Surface* surface
} Scene;

bool InitWindow(Scene* scene, int height, int width);
