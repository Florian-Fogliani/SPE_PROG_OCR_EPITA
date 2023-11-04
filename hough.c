#include "hough.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>
#include <math.h>
#include <stdlib.h>


int* Init_Mat(const int R)
{
	int* res = calloc(180*(R*2),sizeof(int));
	return res;
}

void Free_Mat(char* mat)
{
	free(mat);
}

int Fill_Mat(SDL_Surface* img, int* mat, const int diag_size)
{
	Uint32* pixels = img->pixels;
	SDL_PixelFormat * format = img->format;
	Uint8 r,g,b;
	int max=0;
	for (int h=0; h<img->h; h++)
	{
		for (int w=0; w<img->w; w++)
		{
			SDL_GetRGB(pixels[(h* img->w)+w],format,&r,&g,&b);
			if (r != 0 && g != 0 && b !=0)
			{
				for (int theta = -90; theta<=90; theta++)
				{
					int p = (int)(w*cos(theta * M_PI / 180) + h*sin(theta * M_PI/180));
					mat[(p+diag_size)*(180)+(theta+90)] += 1;
					if (mat[(p+diag_size)*(180)+(theta+90)] > max)
					{
						max = mat[(p+diag_size)*180+(theta+90)];
					}
				}
			}
		}
	}
	return max;
}

double Calculate_Diagonal(SDL_Surface* img)
{
	double p1 = pow((double)img->w,2);
	double p2 = pow((double)img->h,2);
	double res = sqrt(p1+p2);
	return res;
}

void Debug(int* mat,const int diag_size,char* img,int w, int h,int max)
{
	SDL_Window* window = SDL_CreateWindow("Debug",0,0,w,h,SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer,238,130,238,255);
	SDL_Texture* texture = IMG_LoadTexture(renderer,img);
	SDL_RenderCopy(renderer,texture,NULL,NULL);
	int seuil = max*0.4;
	for (int p=0; p<=diag_size*2; p++)
	{
		for (int t=0; t<=180; t++)
		{
			if (mat[p*(180)+t] > seuil)
			{
				printf("%d %d \n",p-diag_size,t-90);
				drawLine(renderer,p-diag_size,t-90,w,h);
			}
		}
	}
	SDL_RenderPresent(renderer);
	SDL_Event event;
	while (1)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
			case SDL_QUIT : return;
		}
	}
}
void drawLine(SDL_Renderer* renderer, int rho, int theta,int width,int height)
{
	if (theta == 0)
	{
		SDL_RenderDrawLine(renderer, rho, 1, rho, height);
	}
	else
	{
		double angleRad = theta*M_PI/180;
		int x0 = 0;
		int y0 = rho / sin(angleRad);
		int x1 = width-1;
		int y1 = x1 * -cos(angleRad)/sin(angleRad) + y0;
		SDL_RenderDrawLine(renderer,x0,y0,x1,y1);
	}
}



void Debug_GetLines(struct Line* horizontals, struct Line* verticals, int* size_horizontals, int* size_verticals,int w, int h, char* img,const int diag_size,int type)
{
	SDL_Window* window = SDL_CreateWindow("Debug GetLines",0,0,w,h,SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer,238,130,238,255);
	SDL_Texture* texture = IMG_LoadTexture(renderer,img);
	SDL_RenderCopy(renderer,texture,NULL,NULL);
	if (type == 0)
	{
		for (int i=0; i<(*size_horizontals); i++)
		{
			int p = horizontals[i].rho;
			int t = horizontals[i].theta;
			drawLine(renderer,p,t,w,h);
		}
	}
	else
	{
		for (int i=0; i<(*size_verticals); i++)
		{
			int p = horizontals[i].rho;
			int t= horizontals[i].theta;
			drawLine(renderer,p,t,w,h);
		}
	}
	SDL_RenderPresent(renderer);
	SDL_Event event;
	while(1)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
			case SDL_QUIT : return;
		}
	}
}

void GetLines(int* mat, const int diag_size, int max, struct Line** horizontals, struct Line** verticals,int* size_horizontals, int* size_verticals)
{
	int thresold = max * 0.4;
	int thresold_horizon = 6;
	for (int p=0; p<=diag_size*2; p++)
	{
		for (int t=0; t<=180; t++)
		{
			if (mat[p*(180)+t] > thresold)
			{
				int real_p = p-diag_size;
				int real_t = t-90;
				if (abs(real_t) > thresold_horizon) //Horizontals Lines
				{
						struct Line to_save = {real_p, real_t};
						Insert_Sort(horizontals, size_horizontals, &to_save);
				}
				if (abs(real_t) <= thresold_horizon) //Verticals Lines
				{
					struct Line to_save = {real_p, real_t};
					Insert_Sort(verticals, size_verticals, &to_save);
				}
			}
		}
	}
}

void insert_sort(struct Line** tab, size_t* len, struct Line* line)
{
    size_t i = 0;
    while (i < *len && line->rho > (*tab + i)->rho)
        i++;
    (*len)++;
    *tab = realloc(*tab, (*len)  * sizeof(struct Line));
    size_t index = i;
    i = (*len) - 1;;
    while (i > index)
    {
        (*tab + i)->rho = (*tab + i - 1)->rho;
        i--;
    }
    (*tab)[index] = *line;
}
void GetIntersec()
{

}
