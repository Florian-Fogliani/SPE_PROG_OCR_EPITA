#ifndef HOUGH
#define HOUGH

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

double Calculate_Diagonal(SDL_Surface* img);
char* Init_Mat(const int R);
void Fill_Mat(SDL_Surface* img, char* mat, const int diag_size);
void Debug(SDL_Surface* img, char* mat, const int diag_size);
void drawLine(SDL_Renderer* renderer, int rho, int theta);


#endif 
