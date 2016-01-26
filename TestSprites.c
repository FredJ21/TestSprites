#include <SDL.h>
#include <SDL_image.h>
#include <time.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define IMG         "images/PetitBateau1.bmp"
#define TAILLE_X    500
#define TAILLE_Y    500


int main( int argc, char* args[] )
{
    printf("Hello world!\n");

    SDL_Window *pWindow             = NULL;
    SDL_Renderer *pRenderer         = NULL;
    SDL_Surface *pSurface           = NULL;
    SDL_Texture *pTexture           = NULL;

    SDL_Event event;

    /******************************************************************************************************************
                                                INIT SDL 2
    *******************************************************************************************************************/
    // Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO) != 0 ) {  SDL_Log( "SDL_Init ERREUR ! SDL_GetError: %s\n", SDL_GetError() ); return -1; }

    pWindow = SDL_CreateWindow( "TEST" , SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, TAILLE_X, TAILLE_Y, SDL_WINDOW_SHOWN );

    // Création du Renderer
    pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
    if(!pRenderer) { SDL_Log( "SDL_Renderer ERREUR! SDL_GetError: %s\n", SDL_GetError() ); return -1;}

    /******************************************************************************************************************
                                                INIT SDL 2  -  Affichage d'une image de chargement ...
    *******************************************************************************************************************/
    // Chargement de l'image
    //pSurface = SDL_LoadBMP (START_IMG);
    pSurface = SDL_LoadBMP (IMG);
    if(!pSurface) {  SDL_Log( "SDL_Surface ERREUR! SDL_GetError: %s\n", SDL_GetError() ); return -1;}

    // Création de la texture (texture = surface dans le GPU)
    pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
    if(!pTexture) { SDL_Log( "SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); return -1;}


    SDL_RenderCopy (pRenderer, pTexture, NULL, NULL);
    SDL_RenderPresent (pRenderer);

    SDL_Delay( 3000 );






    /******************************************************************************************************************
                                                    FIN
    *******************************************************************************************************************/

    SDL_DestroyTexture(pTexture);
    SDL_FreeSurface(pSurface);
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow( pWindow );


    SDL_Quit();



    return 0;
}
