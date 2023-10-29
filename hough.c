#include "hough.h"
#include <SDL2/SDL.h>
#include <err.h>
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

long Calculate_Diagonal(SDL_Surface* img)
{
	return;
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
