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

/// Choose tool
void chooseTool ( SDL_Renderer * renderer, SDL_Event e, ButtonTexture ButtonTools[], ButtonTexture ButtonPoints[], ButtonTexture ButtonLines[], Point Points[], Line Lines[],
                 Status &gameStatus, bool &quit, int &MAX_POINTS, int &MAX_LINES, int &currentPoints, int &currentLines, Point testPoints, Line testLines, int Content )
{
    /// Draw before choosing button
    inMauDiemDoan ( renderer, Points, Lines, currentPoints, currentLines );

    /// Paint the buttons avalible to be used
    renderColorAvalible( renderer, ButtonPoints, 49, 49 + currentPoints, LIGHT_ORANGE );
    renderColorAvalible( renderer, ButtonLines, 14, 14 + currentLines, LIGHT_ORANGE );

    /// Paint the buttons avalible to be used
    if( currentPoints < MAX_POINTS )
    {
        renderColorAvalible( renderer, ButtonTools, NEW_POINT, NEW_POINT + 1, LIGHT_ORANGE );
    }

    if( currentLines < MAX_LINES )
    {
        renderColorAvalible( renderer, ButtonTools, NEW_LINE, NEW_LINE + 1, LIGHT_ORANGE );
    }

    renderColorAvalible( renderer, ButtonTools, DONE, DONE + 1, DARK_RED );

    /// Handle events on queue
    while( SDL_PollEvent( &e ) != 0 )
    {
        /// User requests quit
        if( e.type == SDL_QUIT )
        {
            quit = true;
        }

        /// Handle button events
        for( int i = 0; i < 14 + currentLines; i += 1 )
        {
            ButtonLines[ i ].handleEvent( &e );
        }

        for( int i = 0; i < 49 + currentPoints; i += 1 )
        {
            ButtonPoints[ i ].handleEvent( &e );
        }

        if( currentPoints < MAX_POINTS )
        {
            ButtonTools[ NEW_POINT ].handleEvent( &e );
        }

        if( currentLines < MAX_LINES )
        {
            ButtonTools[ NEW_LINE ].handleEvent( &e );
        }

        ButtonTools[ DONE ].handleEvent( &e );
    }

    /// Change status
    if( ButtonTools[ NEW_POINT ].CurrentSprite == BUTTON_SPRITE_MOUSE_DOWN )
    {
        gameStatus = IS_CREATING_POINT;
    }

    if( ButtonTools[ NEW_LINE ].CurrentSprite == BUTTON_SPRITE_MOUSE_DOWN )
    {
        gameStatus = IS_CREATING_LINE;
    }

    if( ButtonTools[ DONE ].CurrentSprite == BUTTON_SPRITE_MOUSE_DOWN )
    {
        gameStatus = IS_LOSE;

        if( isExistLine( testLines, Lines, 14 + currentLines ) && isExistPoint( testPoints, Points, 49 + currentPoints ) )
        {
            gameStatus = IS_WIN;
        }

        ButtonTools[ DONE ].CurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
    }

    /// Draw after choosing button
    renderAll ( renderer, ButtonTools, ButtonPoints, ButtonLines, Points, Lines, currentPoints, currentLines, Content );
}

/// Make point
void makePoint ( SDL_Renderer * renderer, SDL_Event e, ButtonTexture ButtonTools[], ButtonTexture ButtonPoints[], ButtonTexture ButtonLines[], Point Points[], Line Lines[],
                 Status &gameStatus, bool &quit, int From[], int &had, int &currentPoints, int &currentLines, int Content )
{
    /// Draw before choosing button
    inMauDiemDoan ( renderer, Points, Lines, currentPoints, currentLines );

    /// Paint the buttons avalible to be used
    if( had <= 1 )
    {
        renderColorAvalible( renderer, ButtonLines, 14, 14 + currentLines, LIGHT_ORANGE );
    }

    if( had == 2 )
    {
        renderColorAvalible( renderer, ButtonTools, CREAT, CREAT + 1, LIGHT_ORANGE );
    }

    renderColorAvalible( renderer, ButtonTools, DELETE, DELETE + 1, LIGHT_ORANGE );

    /// Handle events on queue
    while( SDL_PollEvent( &e ) != 0 )
    {
        /// User requests quit
        if( e.type == SDL_QUIT )
        {
            quit = true;
        }

        /// Handle button events
        if( had == 0 )
        {
            for( int i = 0; i < 14 + currentLines; i += 1 )
            {
                ButtonLines[ i ].handleEvent( &e );
            }
        }

        if( had == 1 )
        {
            for( int i = 0; i < 14 + currentLines; i += 1 )
            {
                if ( i != From[0] ) { ButtonLines[ i ].handleEvent( &e ); }
            }
        }

        if( had == 2 )
        {
            ButtonTools[ CREAT ].handleEvent( &e );
        }

        ButtonTools[ DELETE ].handleEvent( &e );
    }

    /// Chosen buttons
    if( had == 0 )
    {
        for( int i = 0; i < 14 + currentLines; i += 1 )
        {
            if( ButtonLines[ i ].CurrentSprite == BUTTON_SPRITE_MOUSE_DOWN )
            {
                From[ 0 ] = i;
                had = 1;
            }
        }
    }

    if( had == 1 )
    {
        for( int i = 0; i < 14 + currentLines; i += 1 )
        {
            if( i != From[0] && ButtonLines[ i ].CurrentSprite == BUTTON_SPRITE_MOUSE_DOWN )
            {
                From[ 1 ] = i;
                had = 2;
            }
        }
    }

    /// Delete chosen buttons
    if( ButtonTools[ DELETE ].CurrentSprite == BUTTON_SPRITE_MOUSE_DOWN )
    {
        for( int i = 0; i < had; i += 1 )
        {
            ButtonLines[ From[ i ] ].CurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        }

        gameStatus = IS_CREATING_NOTHING;

        had = 0;

        From[0] = -1 ;
        From[1] = -1 ;

        ButtonTools[ NEW_POINT ].CurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        ButtonTools[ DELETE ].CurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
    }

    /// Create new points
    if( ButtonTools[ CREAT ].CurrentSprite == BUTTON_SPRITE_MOUSE_DOWN )
    {
        if ( !isParallel( Lines[ From[ 0 ] ], Lines[ From[ 1 ] ] ) )
        {
            Point p = intersection( Lines[ From[ 0 ] ], Lines[ From[ 1 ] ] );
            if ( !isExistPoint ( p, Points, 49 + currentPoints ) && isInside( p ) )
            {
                Points[ 49 + currentPoints ] = p;
                currentPoints += 1;
                printf( "Point %d : (%1.2f, %1.2f) \n", currentPoints, ( p.x/ratioHomothety - 40 )/80 - 2 , 7 - ( p.y/ratioHomothety - 40 )/80 );
                //printf( "Point %d : (%1.2f, %1.2f) \n", currentPoints, p.x , p.y);
            }
        }

        ButtonLines[ From[ 0 ] ].CurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        ButtonLines[ From[ 1 ] ].CurrentSprite = BUTTON_SPRITE_MOUSE_OUT;

        gameStatus = IS_CREATING_NOTHING;

        had = 0;

        From[0] = -1 ;
        From[1] = -1 ;

        ButtonTools[ NEW_POINT ].CurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        ButtonTools[ CREAT ].CurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
    }

    /// Draw after choosing button
    renderAll ( renderer, ButtonTools, ButtonPoints, ButtonLines, Points, Lines, currentPoints, currentLines, Content );

}

/// Make line
void makeLine ( SDL_Renderer * renderer, SDL_Event e, ButtonTexture ButtonTools[], ButtonTexture ButtonPoints[], ButtonTexture ButtonLines[], Point Points[], Line Lines[],
                 Status &gameStatus, bool &quit, int From[], int &had, int &currentPoints, int &currentLines, int Content )
{
    /// Draw before choosing button
    inMauDiemDoan ( renderer, Points, Lines, currentPoints, currentLines );

    /// Paint the buttons avalible to be used
    if( had <= 1 )
    {
        renderColorAvalible( renderer, ButtonPoints, 49, 49 + currentPoints, LIGHT_ORANGE );
    }

    if( had == 2 )
    {
        renderColorAvalible( renderer, ButtonTools, CREAT, CREAT + 1, LIGHT_ORANGE );
    }

    renderColorAvalible( renderer, ButtonTools, DELETE, DELETE + 1, LIGHT_ORANGE );

    /// Handle events on queue
    while( SDL_PollEvent( &e ) != 0 )
    {
        /// User requests quit
        if( e.type == SDL_QUIT )
        {
            quit = true;
        }

        /// Handle button events
        if( had == 0 )
        {
            for( int i = 0; i < 49 + currentPoints; i += 1 )
            {
                ButtonPoints[ i ].handleEvent( &e );
            }
        }

        if( had == 1 )
        {
            for( int i = 0; i < 49 + currentPoints; i += 1 )
            {
                if ( i != From[0] ) { ButtonPoints[ i ].handleEvent( &e ); }
            }
        }

        if( had == 2 )
        {
            ButtonTools[ CREAT ].handleEvent( &e );
        }

        ButtonTools[ DELETE ].handleEvent( &e );

    }

    /// Chosens buttons
    if( had == 0 )
    {
        for( int i = 0; i < 49 + currentPoints; i += 1 )
        {
            if( ButtonPoints[ i ].CurrentSprite == BUTTON_SPRITE_MOUSE_DOWN )
            {
                From[ 0 ] = i;
                had = 1;
            }
        }
    }

    if( had == 1 )
    {
        for( int i = 0; i < 49 + currentPoints; i += 1 )
        {
            if( i != From[0] && ButtonPoints[ i ].CurrentSprite == BUTTON_SPRITE_MOUSE_DOWN )
            {
                From[ 1 ] = i;
                had = 2;
            }
        }
    }

    /// Delete chosen buttons
    if( ButtonTools[ DELETE ].CurrentSprite == BUTTON_SPRITE_MOUSE_DOWN )
    {
        for( int i = 0; i < had; i += 1 )
        {
            ButtonPoints[ From[ i ] ].CurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        }

        gameStatus = IS_CREATING_NOTHING;

        had = 0;

        From[0] = -1 ;
        From[1] = -1 ;

        ButtonTools[ NEW_LINE ].CurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        ButtonTools[ DELETE ].CurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
    }

    /// Create new lines
    if( ButtonTools[ CREAT ].CurrentSprite == BUTTON_SPRITE_MOUSE_DOWN )
    {
        if( ! ( Points[ From[ 0 ] ] == Points[ From[ 1 ] ] ) )
        {
            Line l = through( Points[ From[ 0 ] ], Points[ From[ 1 ] ] );
            if( !isExistLine( l, Lines, 14 + currentLines ) )
            {
                Lines[ 14 + currentLines ] = l;
                currentLines += 1;
                printf( "Line %d : (%1.2f, %1.2f); (%1.2f, %1.2f) \n", currentLines, ( l.A.x/ratioHomothety - 40 )/80 - 2 , 7 - ( l.A.y/ratioHomothety - 40 )/80 , ( l.B.x/ratioHomothety - 40 )/80 - 2 , 7 - ( l.B.y/ratioHomothety - 40 )/80 ) ;
                //printf( "Line %d : (%1.2f, %1.2f); (%1.2f, %1.2f) \n", currentLines, l.A.x, l.A.y, l.B.x, l.B.y ) ;
            }
        }

        ButtonPoints[ From[ 0 ] ].CurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        ButtonPoints[ From[ 1 ] ].CurrentSprite = BUTTON_SPRITE_MOUSE_OUT;

        gameStatus = IS_CREATING_NOTHING;

        had = 0;

        From[0] = -1 ;
        From[1] = -1 ;

        ButtonTools[ NEW_LINE ].CurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        ButtonTools[ CREAT ].CurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
    }

    /// Draw after choosing button
    renderAll ( renderer, ButtonTools, ButtonPoints, ButtonLines, Points, Lines, currentPoints, currentLines, Content );
}

/// Choose content
void chooseMenu ( SDL_Renderer * renderer, SDL_Event e, ButtonTexture ButtonMenu[], Status &gameStatus, bool &quit,
                 int &Content, int &currentPoints, int &currentLines, int CurrentPoints[], int CurrentLines[] )
{
    /// Draw before choosing button
    inMauMenu( renderer );

    /// Paint the buttons avalible to be used
    renderColorAvalible( renderer, ButtonMenu, 11, 13 , LIGHT_ORANGE);

    /// Handle events on queue
    while( SDL_PollEvent( &e ) != 0 )
    {
        /// User requests quit
        if( e.type == SDL_QUIT )
        {
            quit = true;
        }

        /// Handle button events
        for( int i = 11; i < 13; i += 1 )
        {
            ButtonMenu[ i ].handleEvent( &e );
        }
    }

    /// Prepare for game
    for( int i = 11; i < 27; i += 1 )
    {
        if( ButtonMenu[ i ].CurrentSprite == BUTTON_SPRITE_MOUSE_DOWN )
        {
            gameStatus = IS_CREATING_NOTHING;

            ButtonMenu[ i ].CurrentSprite = BUTTON_SPRITE_MOUSE_OUT;

            Content = i - 11;

            currentPoints = CurrentPoints[ Content ];
            currentLines = CurrentLines[ Content ];
        }
    }

    /// Draw after choosing button
    renderColor( renderer, ButtonMenu, 0, 36);

    renderText ( renderer, ButtonMenu, 0, 36);

    inKhungMenu ( renderer );
}

/// Result
void endResult ( SDL_Renderer * renderer, SDL_Event e, ButtonTexture ButtonMenu[], Status &gameStatus, bool &quit )
{
    /// Draw before choosing button
    inEnd( renderer );

    /// Handle events on queue
    while( SDL_PollEvent( &e ) != 0 )
    {
        /// User requests quit
        if( e.type == SDL_QUIT )
        {
            quit = true;
        }

        /// Handle button events
        ButtonMenu[39].handleEvent( &e );
    }

    /// Change status
    if(ButtonMenu[ 39 ].CurrentSprite == BUTTON_SPRITE_MOUSE_DOWN)
    {
        gameStatus = IS_MENU;

        ButtonMenu[ 39 ].CurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
    }

    /// Draw after choosing button
    renderText ( renderer, ButtonMenu, 36, 37);
    renderText ( renderer, ButtonMenu, 39, 40);

    if ( gameStatus == IS_WIN )
    {
        renderText( renderer, ButtonMenu, 37, 38);
    }

    if ( gameStatus == IS_LOSE )
    {
        SDL_SetRenderDrawColor( renderer, GREY.r, GREY.g, GREY.b, 0 );
        SDL_RenderFillRect( renderer, &ButtonMenu[38].Position );
        renderText( renderer, ButtonMenu, 38, 39);
    }
}
