#include <SDL.h>
#include <stdbool.h>
typedef struct{
	SDL_Window* window;
	SDL_Surface* surface;
	SDL_Event event;
} Scene;

bool InitWindow(Scene* scene, int height, int width);

bool closeWindow(Scene* scene);
