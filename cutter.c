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

int main(int argc, char** argv){
    if (argc != 2)
    {
	    return EXIT_FAILURE;
    }
    else
    {
    if (SDL_Init(SDL_INIT_VIDEO) !=0) errx(EXIT_FAILURE,"%s",SDL_GetError());
      SDL_Window* window = SDL_CreateWindow("Window",0,0,20,20,SDL_WINDOW_SHOWN| SDL_WINDOW_RESIZABLE);
     if (window==NULL) errx(EXIT_FAILURE, "%s", SDL_GetError());
     SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
     if (renderer == NULL) errx(EXIT_FAILURE, "%s", SDL_GetError());
     SDL_Surface* surface = load_image(argv[1]);
     if (surface == NULL) errx(EXIT_FAILURE, "%s",SDL_GetError());
     SDL_SetWindowSize(window,surface->w,surface->h);
      SDL_Texture* texture_colored = SDL_CreateTextureFromSurface(renderer,surface);
      surface_to_grayscale(surface);
      SDL_Texture* texture_grayscale = SDL_CreateTextureFromSurface(renderer,surface);
      SDL_FreeSurface(surface);
      event_loop(renderer,texture_colored,texture_grayscale);
      SDL_DestroyTexture(texture_colored);
      SDL_DestroyTexture(texture_grayscale);
      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(window);
      SDL_Quit();

    return EXIT_SUCCESS;
    }
}
