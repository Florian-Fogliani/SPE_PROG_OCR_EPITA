#include <SDL.h>
#include <SDL_image.h>

void resizeImage(const char* inputFileName, const char* outputFileName, int newWidth, int newHeight) {
    // Initialiser SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Erreur lors de l'initialisation de SDL: %s\n", SDL_GetError());
        return;
    }

    // Initialiser SDL_image
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        fprintf(stderr, "Erreur lors de l'initialisation de SDL_image: %s\n", IMG_GetError());
        SDL_Quit();
        return;
    }

    // Charger l'image avec SDL_image
    SDL_Surface* originalSurface = IMG_Load(inputFileName);
    if (originalSurface == NULL) {
        fprintf(stderr, "Erreur lors du chargement de l'image avec SDL_image: %s\n", IMG_GetError());
        IMG_Quit();
        SDL_Quit();
        return;
    }

    // Créer une nouvelle surface redimensionnée
    SDL_Surface* resizedSurface = SDL_CreateRGBSurface(0, newWidth, newHeight,
                                                      originalSurface->format->BitsPerPixel,
                                                      originalSurface->format->Rmask,
                                                      originalSurface->format->Gmask,
                                                      originalSurface->format->Bmask,
                                                      originalSurface->format->Amask);

    // Redimensionner l'image
    SDL_BlitScaled(originalSurface, NULL, resizedSurface, NULL);

    // Sauvegarder la nouvelle surface dans un fichier PNG
    IMG_SavePNG(resizedSurface, outputFileName);

    // Libérer la mémoire et quitter SDL et SDL_image
    SDL_FreeSurface(originalSurface);
    SDL_FreeSurface(resizedSurface);
    IMG_Quit();
    SDL_Quit();
}

int main() {
    resizeImage("mat_1_1", "mat_1_1_resized.png", 28, 28);
    return 0;
}
