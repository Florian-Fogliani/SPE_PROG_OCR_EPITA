#include "hough.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>
#include <math.h>
SDL_Surface* Init_Surface(char* path)
{
	SDL_Surface* res = IMG_Load(path);
	if (!res)
	{
		errx(EXIT_FAILURE,"Init_Surface : ERROR");
	}
	return res;
}

char* Init_Mat()
{
	//PARAM : const diagonal length
	//calcul diagonale
	//return mat
	return;
}

void Fill_Mat()
{
	//ITERATION
	//DETECT MAX
	//
	return;
}

double Calculate_Diagonal(SDL_Surface* img)
{
	return sqrt(pow(img->w,2)+pow(img->h,2));
}
//
//MAIN
//Init surface
//Define const diagonal length
//init mat 
//fill_mat
//detect max -> enregistrement ou ?
//debug : draw line
//cutter -> in : enregistrement en pls images
//
