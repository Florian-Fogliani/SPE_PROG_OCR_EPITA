#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>
#include <math.h>

void renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, double angle, SDL_RendererFlip flip)
{
    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);

    int textureWidth, textureHeight;
    SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);

    // Convertir l'angle en radians
    double radianAngle = angle * M_PI / 180.0;

    // Calculer la nouvelle largeur et hauteur de l'image orientée
    double rotatedWidth = fabs(textureWidth * cos(radianAngle)) + fabs(textureHeight * sin(radianAngle));

    double rotatedHeight = fabs(textureWidth * sin(radianAngle)) + fabs(textureHeight * cos(radianAngle));

    // Calculer l'échelle pour que l'image s'ajuste à la fenêtre sans déformation
    double scaleX = (double)windowWidth / rotatedWidth;
    double scaleY = (double)windowHeight / rotatedHeight;

    // Choisir l'échelle la plus petite pour conserver la proportion
    double scale = fmin(scaleX, scaleY);

    // Calculer la taille de destination en fonction de l'échelle
    double dstWidth = textureWidth * scale;
    double dstHeight = textureHeight * scale;

    SDL_Rect dstRect;
    dstRect.w = dstWidth;
    dstRect.h = dstHeight;
    dstRect.x = (windowWidth - dstWidth) / 2;
    dstRect.y = (windowHeight - dstHeight) / 2;

    SDL_RenderCopyEx(renderer, texture, NULL, &dstRect, angle, NULL, flip);

}


// Updates the display.
//
// renderer: Renderer to draw on.
// texture: Texture that contains the image.
void draw(SDL_Renderer* renderer, SDL_Texture* texture)
{
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}



// Rotation
// Rotation
void rotation(SDL_Renderer* renderer, SDL_Texture* texture, double angle)
{
/*
    SDL_RenderClear(renderer);
    renderTexture(renderer, texture, angle, SDL_FLIP_NONE);
    SDL_RenderPresent(renderer);

    // Récupérer la taille de la fenêtre
    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);

    // Créer une surface pour l'image
    SDL_Surface *image_surface = SDL_CreateRGBSurface(0, windowWidth, windowHeight, 32, 0, 0, 0, 0);
    if (image_surface == NULL)
        errx(EXIT_FAILURE, "SDL_CreateRGBSurface: %s", SDL_GetError());

    // Copier le contenu du rendu sur la surface
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, image_surface->pixels, image_surface->pitch);

    // Ajuster le canal alpha de tous les pixels à 255 (entièrement opaque)
    Uint32 *pixels = (Uint32 *)image_surface->pixels;
    int len = image_surface->w * image_surface->h;
    for (int i = 0; i < len; i++) {
        pixels[i] |= 0xFF000000;
    }

    // Enregistrer la surface sous forme d'image PNG
    if (IMG_SavePNG(image_surface, "img_oriented.png") != 0)
        errx(EXIT_FAILURE, "IMG_SavePNG: %s", IMG_GetError());

    SDL_FreeSurface(image_surface);
*/

    // Rotation de l'image
    renderTexture(renderer, texture, angle, SDL_FLIP_NONE);

    // Récupérer la taille de la fenêtre
    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);

    // Créer une surface pour l'image
    SDL_Surface *image_surface = SDL_CreateRGBSurface(0, windowWidth, windowHeight, 32, 0, 0, 0, 0);
    if (image_surface == NULL)
        errx(EXIT_FAILURE, "SDL_CreateRGBSurface: %s", SDL_GetError());

    // Copier le contenu du rendu sur la surface
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, image_surface->pixels, image_surface->pitch);

    // Ajuster le canal alpha de tous les pixels à 255 (entièrement opaque)
    Uint32 *pixels = (Uint32 *)image_surface->pixels;
    int len = image_surface->w * image_surface->h;
    for (int i = 0; i < len; i++) {
        pixels[i] |= 0xFF000000;
    }

    // Enregistrer la surface sous forme d'image PNG
    if (IMG_SavePNG(image_surface, "img_oriented.png") != 0)
        errx(EXIT_FAILURE, "IMG_SavePNG: %s", IMG_GetError());

    SDL_FreeSurface(image_surface);
}


// Loads an image in a surface.
// The format of the surface is SDL_PIXELFORMAT_RGB888.
//
// path: Path of the image.
SDL_Surface* load_image(const char* path)
{
    SDL_Surface *tmp = IMG_Load(path);
    if (tmp == NULL)
        errx(EXIT_FAILURE, "IMG_Load: %s", SDL_GetError());

    SDL_Surface *surface = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGB888, 0);
    if (surface == NULL)
        errx(EXIT_FAILURE, "SDL_ConvertSurfaceFormat: %s", SDL_GetError());

    SDL_FreeSurface(tmp);

    return surface;
}


// Converts a colored pixel into grayscale.
Uint32 pixel_to_grayscale(Uint32 pixel_color, SDL_PixelFormat* format)
{
    Uint8 r, g, b;
    SDL_GetRGB(pixel_color, format, &r, &g, &b);
    Uint8 average = 0.3 * r + 0.59 * g + 0.11 * b;
    return SDL_MapRGB(format, average, average, average);
}

// Convert the image surface to grayscale
SDL_Surface* surface_to_grayscale(SDL_Surface* surface)
{
    Uint32* pixels = surface->pixels;
    int len = surface->w * surface->h;
    SDL_PixelFormat* format = surface->format;

    for (int i = 0; i < len; i++)
        pixels[i] = pixel_to_grayscale(pixels[i], format);

    return surface;
}
/*

// Event loop that calls the relevant event handler.
// renderer: Renderer to draw on.
// texture: Texture that contains the image.
void event_loop(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Window* window, double angle)
{
    SDL_Event event;

    while (1)
    {
        SDL_WaitEvent(&event);

        switch (event.type)
        {
            case SDL_QUIT:
                return;

            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                {
                    // Obtenir la taille de la fenêtre
                    int windowWidth, windowHeight;
                    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

                    // Effacer le rendu
                    SDL_RenderClear(renderer);

                    // Dessiner l'image centrée
                    renderTexture(renderer, texture, angle, SDL_FLIP_NONE);

                    // Rafraîchir l'écran
                    SDL_RenderPresent(renderer);

                }
                break;
        }

        if (angle != 0.0)
        {
            rotation(renderer, texture, angle);
        }
    }
}

*/

int main(int argc, char* argv[])
{
    if (argc != 3)
        errx(EXIT_FAILURE, "Usage: image-file rotation_angle");

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        errx(EXIT_FAILURE, "SDL_Init: %s", SDL_GetError());

    SDL_Window* window = SDL_CreateWindow("Rotated Image", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);
    if (window == NULL)
        errx(EXIT_FAILURE, "SDL_CreateWindow: %s", SDL_GetError());

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
        errx(EXIT_FAILURE, "SDL_CreateRenderer: %s", SDL_GetError());
    SDL_Surface* surface = NULL;
    if (strcmp(argv[1],"img_01.png") == 0)
    	surface = load_image("image01.png");
    else if (strcmp(argv[1], "img_02.png") == 0)
        surface = load_image("image02.png");
    else if (strcmp(argv[1], "img_03.png") == 0)
        surface = load_image("image03.png");
    else if (strcmp(argv[1], "img_04.png") == 0)
        surface = load_image("image04.png");
    else if (strcmp(argv[1], "img_05.png")== 0)
        surface = load_image("image05.png");
    else if (strcmp(argv[1], "img_06.png")==0)
        surface = load_image("image06.png");
    if (surface == NULL)
        errx(EXIT_FAILURE, "load_image: %s", SDL_GetError());

    double rotation_angle = atof(argv[2]);

    // Convert the surface to grayscale
    surface = surface_to_grayscale(surface);

    // Create a texture from the grayscale surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL)
        errx(EXIT_FAILURE, "SDL_CreateTextureFromSurface: %s", SDL_GetError());

    if (rotation_angle == 0.0)
    {
	rotation_angle = 360;
    }
    rotation (renderer, texture, rotation_angle);
    // Save the rotated and grayscale image as "img_oriented.png"
/*    SDL_Surface *image_surface = SDL_CreateRGBSurface(0, 800, 800, 32, 0, 0, 0, 0);
   if (image_surface == NULL)
       errx(EXIT_FAILURE, "SDL_CreateRGBSurface: %s", SDL_GetError());

    // Copy the renderer's content to the surface
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, image_surface->pixels, image_surface->pitch);

    // Adjust the alpha channel of all pixels to 255 (fully opaque)
    Uint32 *pixels = (Uint32 *)image_surface->pixels;
    int len = image_surface->w * image_surface->h;
    for (int i = 0; i < len; i++) {
        pixels[i] |= 0xFF000000;
    }

    // Save the surface as a PNG image
    if (IMG_SavePNG(image_surface, "img_oriented.png") != 0)
        errx(EXIT_FAILURE, "IMG_SavePNG: %s", IMG_GetError());

    SDL_FreeSurface(image_surface);
*/
    // Destroy objects and quit SDL
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
