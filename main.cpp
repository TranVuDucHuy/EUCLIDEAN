//Using SDL, SDL_image, SDL_ttf, standard IO, math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "ButtonTexture.h"
#include "Line.h"
#include "Point.h"
#include "Draw.h"
#include "Game.h"
#include "Const.h"

int main( int argc, char* args[] )
{
    //The window we'll be rendering to
    SDL_Window* window = NULL;

    //The window renderer
    SDL_Renderer* renderer = NULL;

    //Globally used font
    TTF_Font *font = NULL;

    //Rendered texture
    ButtonTexture ButtonTools[TOTAL_TOOLS];
    ButtonTexture ButtonPoints[TOTAL_POINTS];
    ButtonTexture ButtonLines[TOTAL_LINES];
    ButtonTexture ButtonMenu[TOTAL_MENU];

    Status gameStatus = IS_MENU;
    int Content = 0;

    int From[2];
    int had = 0;

    int currentPoints = 1;
    int currentLines = 2;

    int CurrentPoints[TOTAL_CONTENTS];
    int CurrentLines[TOTAL_CONTENTS];

    setCurrentPoints( CurrentPoints );
    setCurrentLines( CurrentLines );

    int MAX_POINTS = 2;
    int MAX_LINES = 4;

    int MaxPoints[TOTAL_CONTENTS];
    int MaxLines[TOTAL_CONTENTS];

    setMaxPoints( MaxPoints );
    setMaxLines( MaxLines );

    Point TestPoints[TOTAL_CONTENTS];
    Line TestLines[TOTAL_CONTENTS];

    setTestPoints( TestPoints );
    setTestLines( TestLines );

    Point Points[TOTAL_CONTENTS][TOTAL_POINTS];
    Line Lines[TOTAL_CONTENTS][TOTAL_LINES];

    setPoints( Points );
    setLines( Lines );

	//Start up SDL and create window
	if( !init( window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT) )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadFont( renderer, font , ButtonTools, ButtonPoints, ButtonLines) || !loadFontMenu(renderer, font, ButtonMenu))
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
			{
                //Clear screen
				SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
				SDL_RenderClear( renderer );



                switch ( gameStatus )
                {
                    case IS_CREATING_NOTHING:
                    chooseTool( renderer, e, ButtonTools, ButtonPoints, ButtonLines, Points[ Content ], Lines[ Content ], gameStatus, quit, MaxPoints[ Content ], MaxLines[ Content ],
                                currentPoints, currentLines, TestPoints[ Content ], TestLines[ Content ], Content );
                    break;

                    case IS_CREATING_POINT:
                    makePoint( renderer, e, ButtonTools, ButtonPoints, ButtonLines, Points[ Content ], Lines[ Content ], gameStatus, quit, From, had, currentPoints, currentLines, Content );
                    break;

                    case IS_CREATING_LINE:
                    makeLine( renderer, e, ButtonTools, ButtonPoints, ButtonLines, Points[ Content ], Lines[ Content ], gameStatus, quit, From, had, currentPoints, currentLines, Content );
                    break;

                    case IS_MENU:
                        chooseMenu( renderer, e, ButtonMenu, gameStatus, quit, Content, currentPoints, currentLines, CurrentPoints, CurrentLines );
                        break;

                    case IS_WIN:
                        endResult( renderer, e, ButtonMenu, gameStatus, quit );
                        break;

                    case IS_LOSE:
                        endResult( renderer, e, ButtonMenu, gameStatus, quit );
                        break;
                }

				//Update screen
				SDL_RenderPresent( renderer );
			}
		}
	}

	//Free resources and close SDL
	close(window, renderer, font, ButtonTools, ButtonPoints, ButtonLines, ButtonMenu );

	return 0;
}
