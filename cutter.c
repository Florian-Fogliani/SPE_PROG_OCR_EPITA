#include "hough.h"
#include "stdlib.h"
#include <err.h>

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

    const int diag_size = (int)Calculate_Diagonal(surface);
    int* mat = Init_Mat(diag_size);
    int max = Fill_Mat(surface,mat,diag_size);
    struct Line* horizontals = malloc(sizeof(struct Line));
    struct Line* verticals = malloc(sizeof(struct Line));
    int size_horizontals=1;
    int size_verticals=1;
    GetLines(mat,diag_size,max,horizontals,verticals,&size_horizontals,&size_verticals);
    //Debug(mat, diag_size,argv[1], surface->w, surface->h, max);
    Debug_GetLines(horizontals,verticals,&size_horizontals,&size_verticals,surface->w,surface->h, argv[1],diag_size);
   Debug(mat, diag_size,argv[1],surface->w,surface->h,max);
}
