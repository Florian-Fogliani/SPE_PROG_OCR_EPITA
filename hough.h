#ifndef HOUGH
#define HOUGH

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

double Calculate_Diagonal(SDL_Surface* img);
int* Init_Mat(const int R);
int Fill_Mat(SDL_Surface* img, int* mat, const int diag_size);
void Debug(int* mat, const int diag_size,char* img,int w,int h,int max);
void drawLine(SDL_Renderer* renderer, int rho, int theta, int width,int height);
void Debug_GetLines(struct Line* horizontals, struct Line* verticals, int* size_horizontals, int* size_verticals,int w, int h, char* img);
void GetLines(int* mat, const int diag_size, int max, struct Line* horizontals, struct Line* verticals,int* size_horizontals, int* size_verticals);
struct Point();
struct Line();


#endif 
