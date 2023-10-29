#include "hough.h"
#include <SDL2/SDL.h>
#include <err.h>
SDL_Surface* Init_Surface(char* path)
{
	SDL_Surface* res = IMG_Load(path);
	if (!res)
	{
		errx("Init_Surface : ERROR");
		return EXIT_FAILURE;
	}
	return res;
}

char* Init_Mat()
{
	//PARAM : const diagonal length
	//calcul diagonale
	//return mat
}

void Fill_Mat()
{
	//ITERATION
	//DETECT MAX
	//
}

const long Calculate_Diagonal(SDL_Surface* img)
{

}

//MAIN
//Init surface
//Define const diagonal length
//init mat 
//fill_mat
//detect max -> enregistrement ou ?
//debug : draw line
//cutter -> in : enregistrement en pls images
//
