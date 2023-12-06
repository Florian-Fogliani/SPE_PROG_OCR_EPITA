#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int width;
    int height;
    uint8_t* data; // Tableau unidimensionnel représentant les pixels (chaque composant de pixel consécutif : R, G, B, etc.)
} Image;

float cubic(float t) {
    return t * t * (3.0 - 2.0 * t);
}

float bicubicInterpolation(float p[4], float x) {
    return p[1] +
           0.5 * x * (p[2] - p[0] +
                      x * (2.0 * p[0] - 5.0 * p[1] + 4.0 * p[2] - p[3] +
                           x * (3.0 * (p[1] - p[2]) + p[3] - p[0])));
}

void resizeBicubicSDL(const SDL_Surface* src, int newWidth, int newHeight, SDL_Surface* dst) {
    float scale_x = (float)(src->w - 1) / newWidth;
    float scale_y = (float)(src->h - 1) / newHeight;

    for (int y = 0; y < newHeight; y++) {
        for (int x = 0; x < newWidth; x++) {
            float srcX = x * scale_x;
            float srcY = y * scale_y;

            int x0 = (int)srcX - 1;
            int x1 = x0 + 1;
            int x2 = x0 + 2;
            int x3 = x0 + 3;
            int y0 = (int)srcY - 1;
            int y1 = y0 + 1;
            int y2 = y0 + 2;
            int y3 = y0 + 3;

            float dx = srcX - (float)x0;
            float dy = srcY - (float)y0;

            // Make sure indices are within bounds
            x0 = (x0 < 0) ? 0 : (x0 >= src->w) ? src->w - 1 : x0;
            x1 = (x1 < 0) ? 0 : (x1 >= src->w) ? src->w - 1 : x1;
            x2 = (x2 < 0) ? 0 : (x2 >= src->w) ? src->w - 1 : x2;
            x3 = (x3 < 0) ? 0 : (x3 >= src->w) ? src->w - 1 : x3;
            y0 = (y0 < 0) ? 0 : (y0 >= src->h) ? src->h - 1 : y0;
            y1 = (y1 < 0) ? 0 : (y1 >= src->h) ? src->h - 1 : y1;
            y2 = (y2 < 0) ? 0 : (y2 >= src->h) ? src->h - 1 : y2;
            y3 = (y3 < 0) ? 0 : (y3 >= src->h) ? src->h - 1 : y3;

            for (int c = 0; c < 3; c++) {
                float values[4];
                for (int i = 0; i < 4; i++) {
                    uint8_t* pixel = (uint8_t*)src->pixels + ((y0 + i) * src->pitch + x0 * src->format->BytesPerPixel);
                    float p[4] = {
                        pixel[c],
                        ((uint8_t*)pixel + src->format->BytesPerPixel)[c],
                        ((uint8_t*)pixel + 2 * src->format->BytesPerPixel)[c],
                        ((uint8_t*)pixel + 3 * src->format->BytesPerPixel)[c]
                    };
                    values[i] = bicubicInterpolation(p, dx);
                }
                float result = bicubicInterpolation(values, dy);
                uint8_t* resultPixel = (uint8_t*)dst->pixels + (y * dst->pitch + x * dst->format->BytesPerPixel);
                resultPixel[c] = (uint8_t)result;
            }
        }
    }
}

SDL_Surface* loadImage(const char* filename) {
    SDL_Surface* image = IMG_Load(filename);
    if (!image) {
        fprintf(stderr, "Erreur lors du chargement de l'image : %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    }
    return image;
}

void freeImageSDL(SDL_Surface* img) {
    SDL_FreeSurface(img);
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Erreur lors de l'initialisation de SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        fprintf(stderr, "Erreur lors de l'initialisation de SDL_Image : %s\n", IMG_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Surface* srcImage = loadImage("mat_1_1");

    int newWidth = 260;
    int newHeight = 260;

    SDL_Surface* resizedImage = SDL_CreateRGBSurface(0, newWidth, newHeight,
                                                    srcImage->format->BitsPerPixel,
                                                    0xFF000000,
                                                    0x00FF0000,
                                                    0x0000FF00,
                                                    0x000000FF);

    resizeBicubicSDL(srcImage, newWidth, newHeight, resizedImage);

    SDL_Window* window = SDL_CreateWindow("SDL Bicubic Resize Example",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          srcImage->w * 2, srcImage->h,
                                          SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        SDL_FreeSurface(srcImage);
        SDL_FreeSurface(resizedImage);
        IMG_Quit();
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        fprintf(stderr, "Erreur lors de la création du rendu : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_FreeSurface(srcImage);
        SDL_FreeSurface(resizedImage);
        IMG_Quit();
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Texture* resizedTexture = SDL_CreateTextureFromSurface(renderer, resizedImage);

    int quit = 0;
    while (!quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        SDL_RenderClear(renderer);

        SDL_Rect srcRect = { 0, 0, srcImage->w, srcImage->h };
        SDL_Rect dstRect = { 0, 0, srcImage->w, srcImage->h };
        SDL_RenderCopy(renderer, SDL_CreateTextureFromSurface(renderer, srcImage), &srcRect, &dstRect);

        dstRect.x = srcImage->w;
        SDL_RenderCopy(renderer, resizedTexture, NULL, &dstRect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(resizedTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_FreeSurface(srcImage);
    SDL_FreeSurface(resizedImage);
    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
