#include "hough.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>
#include <math.h>

char* Init_Mat(const int R)
{
	char* res = calloc(180*(R*2),sizeof(char));
	return res;
}

void Free_Mat(char* mat)
{
	free(mat);
}

void Fill_Mat(SDL_Surface* img, char* mat, const int diag_size)
{
	Uint32* pixels = img->pixels;
	SDL_PixelFormat * format = img->format;
	Uint8 r,g,b;
	for (int h=0; h<img->h; h++)
	{
		for (int w=0; w<img->w; w++)
		{
			SDL_GetRGB(pixels[(h* img->w)+w],format,&r,&g,&b);
			if (r != 0 && g != 0 && b !=0)
			{
				for (int theta = 0; theta<=180; theta++)
				{
					int p = (int)(h*cos(theta * M_PI / 180) + w*sin(theta * M_PI/180));
					mat[theta*(diag_size*2)+p] += 1;
				}
			}
		}
	}
}

void Detect_Max() {}

double Calculate_Diagonal(SDL_Surface* img)
{
	double p1 = pow((double)img->w,2);
	double p2 = pow((double)img->h,2);
	double res = sqrt(p1+p2);
	return res;
}


//detect max -> enregistrement ou ?
//debug : draw line
//cutter -> in : enregistrement en pls images
//
