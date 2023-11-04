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
    if (argc != 3)
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
    if (strcmp(argv[2],"debug")==0)
    {
	    Debug(mat, diag_size, argv[1], surface->w, surface->h, max);
    }
    else if (strcmp(argv[2],"all")==0)
    {
        struct Line* horizontals = malloc(sizeof(struct Line));
        struct Line* verticals = malloc(sizeof(struct Line));
        int size_h=0;
        int size_v=0;
        GetLines
            (mat, diag_size,max,&horizontals, &verticals, 
             &size_h, &size_v);
        Cut(&horizontals,&verticals,&size_h,&size_v,surface,diag_size);
    }
    else
    {
    	int type_debug = 0;
    	if (strcmp(argv[2],"vertical")==0)
    	{
		    type_debug = 1;
    	}
    	struct Line* horizontals = malloc(sizeof(struct Line));
    	struct Line* verticals = malloc(sizeof(struct Line));
    	int size_horizontals=1;
    	int size_verticals=1;
    	GetLines
            (mat,diag_size,max, &horizontals, &verticals,
             &size_horizontals,&size_verticals);
    	Debug_GetLines(horizontals,verticals,&size_horizontals,&size_verticals,
                surface->w,surface->h, argv[1],type_debug);
    }
}
