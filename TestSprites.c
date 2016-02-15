#include <SDL.h>
#include <SDL_image.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define false   0
#define true    1
#define bool    short int

#define WINDOWS_SIZE_X    500
#define WINDOWS_SIZE_Y    500

//#define START_IMG           "images/background.bmp"
#define START_IMG           "images/bleue_mer.jpg"
/*
#define SPRITE              "images/PetitBateau1.bmp"
#define IMG_SIZE_X          48
#define IMG_SIZE_Y          48
#define NB_COLONNE          3
enum { UP, RIGHT, DOWN, LEFT };
*/
/*
#define SPRITE              "images/bateau.png"
#define IMG_SIZE_X          64
#define IMG_SIZE_Y          64
#define NB_COLONNE          4
enum { DOWN, LEFT, RIGHT, UP };
*/
/*
#define SPRITE              "images/surfvolanttest8qj.png"
#define IMG_SIZE_X          110
#define IMG_SIZE_Y          60
#define NB_COLONNE          4
enum { DOWN, LEFT, RIGHT, UP };
*/
/*
#define SPRITE              "images/LOS-LargePirate_1504x1400.png"
#define IMG_SIZE_X          376
#define IMG_SIZE_Y          350
#define NB_COLONNE          4
enum { UP, RIGHT, DOWN, LEFT };
*/
/*
//#define SPRITE              "images/LOS-SinglePirate.png"

#define IMG_SIZE_X          77
#define IMG_SIZE_Y          62
#define NB_COLONNE          4
enum { UP, RIGHT, DOWN, LEFT };
*/


#define SPRITE              "images/Enemy-Bateau_soleil_61x55.png"
#define IMG_SIZE_X          61
#define IMG_SIZE_Y          55
#define NB_COLONNE          9
enum { UP, RIGHT, DOWN, LEFT };



#define NB_TOUR             3       // nombre de cycle avant changement d'image
#define SPEED                3
#define FPS                 30



int main( int argc, char* args[] )
{
    printf("Hello world!\n");

    bool my_exit                = false;
    bool my_pause               = true;
    int x                       = WINDOWS_SIZE_X / 2;
    int y                       = WINDOWS_SIZE_Y / 2;
    int current_image           = 0;
    int current_direction       = 0;
    int current_tour            = 0;

    SDL_Window *pWindow             = NULL;
    SDL_Renderer *pRenderer         = NULL;
    SDL_Surface *pSurface           = NULL;
    SDL_Texture *pTexture           = NULL;
    SDL_Texture *pTextureANIM       = NULL;

    SDL_Event event;

    SDL_Rect Src;
    SDL_Rect Dst;



    /******************************************************************************************************************
                                                INIT SDL 2
    *******************************************************************************************************************/
    // Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO) != 0 ) {  SDL_Log( "SDL_Init ERREUR ! SDL_GetError: %s\n", SDL_GetError() ); return -1; }

    pWindow = SDL_CreateWindow( "TEST" , SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOWS_SIZE_X, WINDOWS_SIZE_Y, SDL_WINDOW_SHOWN );

    // Création du Renderer
    pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
    if(!pRenderer) { SDL_Log( "SDL_Renderer ERREUR! SDL_GetError: %s\n", SDL_GetError() ); return -1;}

    /******************************************************************************************************************
                                                INIT SDL 2  -  Affichage d'une image de chargement ...
    *******************************************************************************************************************/
    pSurface = IMG_Load (START_IMG);
    if(!pSurface) {  SDL_Log( "SDL_Surface ERREUR! SDL_GetError: %s\n", SDL_GetError() ); return -1;}

    // Création de la texture (texture = surface dans le GPU)
    pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
    if(!pTexture) { SDL_Log( "SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); return -1;}



    /******************************************************************************************************************
                                                INIT Animation
    *******************************************************************************************************************/

    SDL_Surface *pSurface_tmp = IMG_Load ( SPRITE );
            if(!pSurface_tmp) { SDL_Log( "IMG_Load ERROR : %s\n", SDL_GetError() ); exit(1);}

    SDL_SetColorKey(pSurface_tmp, SDL_TRUE, SDL_MapRGB(pSurface_tmp->format, 255, 255, 255));

    pTextureANIM = SDL_CreateTextureFromSurface(pRenderer, pSurface_tmp);
        if(!pTextureANIM) { SDL_Log( "SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); exit(1);}

    SDL_FreeSurface(pSurface_tmp);


    /******************************************************************************************************************
                                                Boucle principale
    *******************************************************************************************************************/
    while (!my_exit) {


            /******************************************************************************************************************
                                                        GESTION DES EVENEMENTS
            *******************************************************************************************************************/
            while (SDL_PollEvent(&event)) {

                switch (event.type){

                    case SDL_QUIT:
                        my_exit = true;
                        break;
                    case SDL_KEYDOWN:
                       switch( event.key.keysym.sym ){
                            case SDLK_ESCAPE:
                                my_exit = true;
                                break;
                            case SDLK_UP:
                                current_direction = UP;
                                break;
                            case SDLK_RIGHT:
                                current_direction = RIGHT;
                                break;
                            case SDLK_DOWN:
                                current_direction = DOWN;
                                break;
                            case SDLK_LEFT:
                                current_direction = LEFT;
                                break;
                            case SDLK_SPACE:
                                if ( my_pause ) {  my_pause = false; } else { my_pause = true; }
                         }
                        break;
                }
            }

            /******************************************************************************************************************
                                                            CALCULS
            *******************************************************************************************************************/
            Src.x = current_image * IMG_SIZE_X;
            Src.y = current_direction * IMG_SIZE_Y;
            Src.w = IMG_SIZE_X;
            Src.h = IMG_SIZE_Y;

            Dst.x = x - IMG_SIZE_X/2;     // permet de center le sprite sur les coordonnées
            Dst.y = y - IMG_SIZE_Y/2;
            Dst.w = IMG_SIZE_X;
            Dst.h = IMG_SIZE_Y;

            current_tour++;
            if (current_tour >= NB_TOUR) {

                    current_image++;
                    if (current_image >= NB_COLONNE ) { current_image = 0; }
                    current_tour = 0;
            }

            if ( !my_pause ) {
                switch (current_direction){
                    case UP:        if ( y > 0 + IMG_SIZE_Y/2 ) { y -= SPEED; }                                 break;
                    case RIGHT:     if ( x < WINDOWS_SIZE_X - IMG_SIZE_X/2 ) { x += SPEED; }                    break;
                    case DOWN:      if ( y < WINDOWS_SIZE_Y - IMG_SIZE_Y/2 ) { y += SPEED; }                    break;
                    case LEFT:     if ( x > 0 + IMG_SIZE_X/2 ) { x -= SPEED; }                                 break;
                }
            }


            /******************************************************************************************************************
                                                            AFFICHAGE
            *******************************************************************************************************************/
            SDL_RenderClear     (pRenderer);

            SDL_RenderCopy ( pRenderer, pTexture , NULL, NULL);
            SDL_RenderCopy ( pRenderer, pTextureANIM , &Src, &Dst);

            SDL_RenderPresent (pRenderer);


            /******************************************************************************************************************/
            SDL_Delay( 1000 / FPS );
    }



    /******************************************************************************************************************
                                                    FIN
    *******************************************************************************************************************/

    SDL_DestroyTexture(pTexture);
    SDL_DestroyTexture(pTextureANIM);
    SDL_FreeSurface(pSurface);
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow( pWindow );


    SDL_Quit();



    return 0;
}
