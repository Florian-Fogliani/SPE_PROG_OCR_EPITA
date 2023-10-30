#include "hough.h"
#include "stdlib.h"

int main(int argc, char** argv){
    if (argc != 2)
    {
	    return EXIT_FAILURE;
    }
    else
    {
	    SDL_Init(SDL_INIT_VIDEO);
	    IMG_Init(IMG_INIT_PNG);
	    SDL_Surface* surf = IMG_Load(argv[1]);
	    if (surf == NULL)
	    {
		    errx(EXIT_FAILURE, "Erreur de chargement de la surface");
	    }
	    printf("%s\n",argv[1]);
	    printf("%f\n",surf->w);
	    printf("%f\n",surf->h);

    }
}
