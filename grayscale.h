#ifndef _GRAYSCALE_H
#define _GRAYSCALE_H


#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>
#include <math.h>

void renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, double angle, SDL_RendererFlip flip);

void draw(SDL_Renderer* renderer, SDL_Texture* texture);

void rotation(SDL_Renderer* renderer, SDL_Texture* texture, double angle);

SDL_Surface* load_image(const char* path);

Uint32 pixel_to_grayscale(Uint32 pixel_color, SDL_PixelFormat* format);

SDL_Surface* surface_to_grayscale(SDL_Surface* surface);

int main(int argc, char* argv[]);



#endif
