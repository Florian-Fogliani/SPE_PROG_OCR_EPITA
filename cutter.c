#include "hough.h"
#include "stdlib.h"

SDL_Surface* load_image(const char* path)
{
    SDL_Surface* temp = IMG_Load(path);
    if (temp == NULL) errx(EXIT_FAILURE,"%s",SDL_GetError());
    SDL_Surface* res = SDL_ConvertSurfaceFormat(temp,SDL_PIXELFORMAT_RGB888,0);
    if (res==NULL) errx(EXIT_FAILURE,"%s",SDL_GetError());
    SDL_FreeSurface(temp);
    return res;
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
	    return EXIT_FAILURE;
    }
   

    if (SDL_Init(SDL_INIT_VIDEO) !=0)
    {
	errx(EXIT_FAILURE,"%s",SDL_GetError());
    }
    SDL_Surface* surface = load_image(argv[1]);
    if (surface == NULL)
    {
	    errx(EXIT_FAILURE, "%s",SDL_GetError());
    
    }
    double diag_size = Calculate_Diagonal(surface);
    printf("%f \n", diag_size);
}
