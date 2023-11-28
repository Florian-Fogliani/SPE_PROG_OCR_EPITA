#include <SDL2/SDL.h>
#include <math.h>

#define H 480
#define W 640
#define PI 3.14159265

void houghTransform(SDL_Surface* input, SDL_Surface* output, int threshold) {

    // Dimensions of the Hough parameter space (polar coordinates)
    int pMax = (int)sqrt(H*H + W*W); // max distance is the diagonal
    float thetaMax = PI; // range will be [0, PI]

    int* accumulator = (int*)calloc(pMax * thetaMax, sizeof(int));

    // for each point in the input space,
    for(int x=0; x<input->w; ++x)
        for(int y=0; y<input->h; ++y) {
            Uint32 pixel= getpixel(img,x,y);
            Uint8 r,g,b;
            SDL_GetRGB(pixel,img1->format,&r,&g,&b);
            
        // if the pixel is not black (edge detected), transform it in the parameter space
            if(b!=0){
            for (int tIdx = 0; tIdx < thetaMax; ++tIdx) {
                // precomputes cos and sin values
                double cosVal = cos(((double)tIdx * PI) / thetaMax);
                double sinVal = sin(((double)tIdx * PI) / thetaMax);

                // find the closest radius from the origin of this line
                int p = (int)(x * cosVal + y * sinVal);

                // increment the accumulator cell
                if (p >= 0 && p < pMax) ++accumulator[p * thetaMax + tIdx];
            }
        }
    }

    // for each cell in the accumulator,
    for (int p = 0; p < pMax; ++p)
        for (int tIdx = 0; tIdx < thetaMax; ++tIdx)
            // if the value of the cell is over the threshold, draw the line in the output image
            if (accumulator[p * thetaMax + tIdx] > threshold)
                // draw line in output image
    free(accumulator);
}
