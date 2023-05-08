/// Using SDL, SDL_image, SDL_ttf, standard IO, math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "Draw.h"
#include "Line.h"
#include "Point.h"
#include "Const.h"

/// Starts up SDL and creates window
bool init( SDL_Window* &window, SDL_Renderer* &renderer, int screenWidth, int screenHeight )
{
	/// Initialization flag
	bool success = true;

	/// Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		/// Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		/// Create window
		window = SDL_CreateWindow( "EUCLIDEAN", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			/// Create vsynced renderer for window
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( renderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				/// Initialize renderer color
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

				/// Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

                /// Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

/// Loads font for main board
bool loadFont( SDL_Renderer* renderer, TTF_Font* font, ButtonTexture ButtonTools[], ButtonTexture ButtonPoints[], ButtonTexture ButtonLines[]  )
{
	/// Loading success flag
	bool success = true;

	/// Loading button text and position
    setButtonTools(ButtonTools);
    setButtonPoints(ButtonPoints);
    setButtonLines(ButtonLines);

	/// Open the font
	font = TTF_OpenFont( "Roboto-Medium.ttf", 30 );
	if( font == NULL )
	{
		printf( "Failed to load Roboto font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		/// Render tools text
		SDL_Color textColor = { 0, 0, 0 };
		for( int i = 0; i < TOTAL_TOOLS; i += 1 )
        {
            if( !ButtonTools[ i ].loadFromRenderedText( renderer, font, textColor ) )
            {
			printf( "Failed to render TOOL texture!\n" );
			success = false;
            }
		}
	}

	font = TTF_OpenFont( "Roboto-Medium.ttf", 24 );
	if( font == NULL )
	{
		printf( "Failed to load Roboto font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
        /// Render points and lines text
        SDL_Color textColor = { 0, 0, 0 };
        for( int i = 49; i < TOTAL_POINTS; i += 1 )
        {
            if( !ButtonPoints[ i ].loadFromRenderedText( renderer, font, textColor ) )
            {
                printf( "Failed to render text POINT texture!\n" );
                success = false;
            }
        }
        for( int i = 14; i < TOTAL_LINES; i += 1 )
        {
            if( !ButtonLines[ i ].loadFromRenderedText( renderer, font, textColor ) )
            {
                printf( "Failed to render text LINE texture!\n" );
                success = false;
            }
        }
	}
	return success;
}

/// Load font for menu text
bool loadFontMenu( SDL_Renderer* renderer, TTF_Font* font, ButtonTexture ButtonMenu[] )
{
    /// Loading success flag
	bool success = true;

	/// Loading button text and position
	setButtonMenu( ButtonMenu );

	/// Open the font
	font = TTF_OpenFont( "Roboto-Medium.ttf", 96 );
	if( font == NULL )
	{
		printf( "Failed to load Roboto font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		/// Render text
		SDL_Color textColor = { 0, 0, 0 };
        if( !ButtonMenu[ 0 ].loadFromRenderedText( renderer, font, textColor ) )
        {
			printf( "Failed to render MENU texture!\n" );
			success = false;
        }
	}

    font = TTF_OpenFont( "Roboto-Medium.ttf", 80 );
	if( font == NULL )
	{
		printf( "Failed to load Roboto font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		/// Render text
		SDL_Color textColor = { 0, 0, 0 };
		for( int i = 36; i < 39; i += 1 )
        {
            if( !ButtonMenu[ i ].loadFromRenderedText( renderer, font, textColor ) )
            {
                printf( "Failed to render MENU 36 37 38 texture!\n" );
                success = false;
            }
		}
	}

    font = TTF_OpenFont( "Roboto-Medium.ttf", 40 );
	if( font == NULL )
	{
		printf( "Failed to load Roboto font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		/// Render text
		SDL_Color textColor = { 0, 0, 0 };
        if( !ButtonMenu[ 1 ].loadFromRenderedText( renderer, font, textColor ) )
        {
			printf( "Failed to render MENU 1 texture!\n" );
			success = false;
        }
        if( !ButtonMenu[ 10 ].loadFromRenderedText( renderer, font, textColor ) )
        {
			printf( "Failed to render MENU 10 texture!\n" );
			success = false;
        }
        if( !ButtonMenu[ 27 ].loadFromRenderedText( renderer, font, textColor ) )
        {
			printf( "Failed to render MENU 27 texture!\n" );
			success = false;
        }
        if( !ButtonMenu[ 39 ].loadFromRenderedText( renderer, font, textColor ) )
        {
			printf( "Failed to render MENU 39 texture!\n" );
			success = false;
        }
	}

	font = TTF_OpenFont( "Roboto-Medium.ttf", 20 );
	if( font == NULL )
	{
		printf( "Failed to load Roboto font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
        /// Render text
        SDL_Color textColor = { 0, 0, 0 };
        for( int i = 2; i < 10; i += 1 )
        {
            if( !ButtonMenu[ i ].loadFromRenderedText( renderer, font, textColor ) )
            {
                printf( "Failed to render text MENU 2 9 texture!\n" );
                success = false;
            }
        }
        for( int i = 11; i < 27; i += 1 )
        {
            if( !ButtonMenu[ i ].loadFromRenderedText( renderer, font, textColor ) )
            {
                printf( "Failed to render text MENU 11 26 texture!\n" );
                success = false;
            }
        }
        for( int i = 28; i < 36; i += 1 )
        {
            if( !ButtonMenu[ i ].loadFromRenderedText( renderer, font, textColor ) )
            {
                printf( "Failed to render text MENU 28 35 texture!\n" );
                success = false;
            }
        }
	}
	return success;
}

///Frees media and shuts down SDL
void close( SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font, ButtonTexture ButtonTools[],
            ButtonTexture ButtonPoints[], ButtonTexture ButtonLines[], ButtonTexture ButtonMenu[] )
{
	/// Free loaded
    for( int i = 0; i < TOTAL_MENU; i += 1 )
    {
        ButtonMenu[ i ].free();
	}
	for( int i = 0; i < TOTAL_TOOLS; i += 1 )
	{
        ButtonTools[ i ].free();
	}
    for( int i = 0; i < TOTAL_POINTS; i += 1 )
    {
        ButtonPoints[ i ].free();
	}
	for( int i = 0; i < TOTAL_LINES; i += 1 )
	{
        ButtonLines[ i ].free();
	}

	/// Free global font
	TTF_CloseFont( font );
	font = NULL;

	/// Destroy window
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;

	/// Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

/// Bold
void inDamDoc (SDL_Renderer * renderer, int x1, int y1, int x2, int y2 )
{
    for( int i = -1; i < 2; i += 1 )
    {
        SDL_RenderDrawLine( renderer, x1 + i, y1, x2 + i, y2 );
    }
}

void inDamNgang (SDL_Renderer * renderer, int x1, int y1, int x2, int y2 )
{
    for( int i = -1; i < 2; i += 1 )
    {
        SDL_RenderDrawLine( renderer, x1, y1 + i, x2, y2 + i );
    }
}

/// Draw main board
void inMau (SDL_Renderer * renderer)
{
    /// Paint
    SDL_SetRenderDrawColor( renderer, BROWN.r, BROWN.g, BROWN.b, 0 );
    SDL_Rect bang1 = { 0, 0, 1040, 640};
    SDL_RenderFillRect( renderer, &bang1 );

    SDL_SetRenderDrawColor( renderer, ORANGE.r, ORANGE.g, ORANGE.b, 0 );
    SDL_Rect bang2 = { 40, 40, 960, 560};
    SDL_RenderFillRect( renderer, &bang2 );

    SDL_SetRenderDrawColor( renderer, GREY.r, GREY.g, GREY.b, 0 );
    SDL_Rect bang3 = { 40, 160, 960, 440};
    SDL_RenderFillRect( renderer, &bang3 );

    SDL_SetRenderDrawColor( renderer, YELLOW.r, YELLOW.g, YELLOW.b, 0 );
    SDL_Rect bang4 = { 200, 120, 480, 480};
    SDL_RenderFillRect( renderer, &bang4 );
}

void inKhung (SDL_Renderer * renderer)
{
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );

    /// Vertical lines
    inDamDoc( renderer, 40, 40, 40, 600 );
    for( int i = 0; i < 7; i += 1 )
    {
        SDL_RenderDrawLine( renderer, 200 + i*80, 120, 200 + i*80, 600 );
    }
    inDamDoc( renderer, 200, 120, 200, 600 );
    inDamDoc( renderer, 200 + 6*80, 120, 200 + 6*80, 600 );
    SDL_RenderDrawLine( renderer, 200 + 7*80, 160, 200 + 7*80, 600 );
    inDamDoc( renderer, 200 + 8*80, 120, 200 + 8*80, 600 );
    SDL_RenderDrawLine( renderer, 920, 160, 920, 600 );
    inDamDoc( renderer, 1000, 40, 1000, 600 );

    /// Horizontal lines
    inDamNgang( renderer, 40, 40, 1000, 40 );
    inDamNgang( renderer, 40, 120, 1000, 120 );
    for( int i = 1; i < 11; i += 1 )
    {
        SDL_RenderDrawLine( renderer, 680, 160 + i*40, 1000, 160 + i*40 );
    }
    inDamNgang( renderer, 680, 160, 1000, 160 );
    inDamNgang( renderer, 680, 160 + 11*40, 1000, 160 + 11*40 );
    inDamNgang( renderer, 40, 160, 200, 160 );
    SDL_RenderDrawLine( renderer, 40, 160 + 40, 200, 160 + 40 );
    inDamNgang( renderer, 40, 160 + 2*40, 200, 160 + 2*40 );
    for( int i = 8; i < 12; i += 1 )
    {
        inDamNgang( renderer, 40, 160 + i*40, 200, 160 + i*40 );
    }
    for( int i = 0; i < 6; i += 1 )
    {
        SDL_RenderDrawLine( renderer, 200 , 200 + i*80 , 680, 200 + i*80 );
    }
    inDamNgang( renderer, 40, 600, 1000, 600 );
}

void inDiem ( SDL_Renderer * renderer, Point Points[], int currentPoints )
{
    for( int i = 0; i < currentPoints; i += 1 )
    {
        int px = Points[ i ].x/ratioHomothety;
        int py = Points[ i ].y/ratioHomothety;

        SDL_Rect bang = { px - 1, py - 1, 3, 3 };

        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );
        SDL_RenderFillRect( renderer, &bang );
    }
}

void inDoan ( SDL_Renderer * renderer, Line Lines[], int currentLines )
{
    for( int i = 0; i < currentLines; i += 1 )
    {
        int lAx = Lines[ i ].A.x/ratioHomothety;
        int lAy = Lines[ i ].A.y/ratioHomothety;
        int lBx = Lines[ i ].B.x/ratioHomothety;
        int lBy = Lines[ i ].B.y/ratioHomothety;

        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );
        SDL_RenderDrawLine( renderer, lAx, lAy, lBx, lBy );
    }
}

/// Draw menu
void inMauMenu ( SDL_Renderer * renderer )
{
    /// Paint
    SDL_SetRenderDrawColor( renderer, BROWN.r, BROWN.g, BROWN.b, 0 );
    SDL_Rect bang1 = { 0, 0, 1080, 640};
    SDL_RenderFillRect( renderer, &bang1 );

    SDL_SetRenderDrawColor( renderer, LIGHT_BROWN.r, LIGHT_BROWN.g, LIGHT_BROWN.b, 0 );
    SDL_Rect bang2 = { 40, 40, 960, 560};
    SDL_RenderFillRect( renderer, &bang2 );

    SDL_SetRenderDrawColor( renderer, GREY.r, GREY.g, GREY.b, 0 );
    SDL_Rect bang3 = { 360, 280, 320, 320};
    SDL_RenderFillRect( renderer, &bang3 );

    SDL_SetRenderDrawColor( renderer, YELLOW.r, YELLOW.g, YELLOW.b, 0 );
    SDL_Rect bang4 = { 40, 280, 240, 320};
    SDL_Rect bang5 = { 760, 280, 240, 320};
    SDL_RenderFillRect( renderer, &bang4 );
    SDL_RenderFillRect( renderer, &bang5 );

    SDL_SetRenderDrawColor( renderer, ORANGE.r, ORANGE.g, ORANGE.b, 0 );
    SDL_Rect bang6 = { 200, 40, 640, 120};
    SDL_Rect bang7 = { 40, 200, 240, 80};
    SDL_Rect bang8 = { 360, 200, 320, 80};
    SDL_Rect bang9 = { 760, 200, 240, 80};
    SDL_RenderFillRect( renderer, &bang6 );
    SDL_RenderFillRect( renderer, &bang7 );
    SDL_RenderFillRect( renderer, &bang8 );
    SDL_RenderFillRect( renderer, &bang9 );
}

void inKhungMenu ( SDL_Renderer * renderer )
{
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );

    /// Vertical lines
    inDamDoc( renderer, 200, 40, 200, 160 );
    inDamDoc( renderer, 840, 40, 840, 160 );

    inDamDoc( renderer, 40, 200, 40, 600 );
    inDamDoc( renderer, 280, 200, 280, 600 );
    inDamDoc( renderer, 360, 200, 360, 600 );
    inDamDoc( renderer, 680, 200, 680, 600 );
    inDamDoc( renderer, 760, 200, 760, 600 );
    inDamDoc( renderer, 1000, 200, 1000, 600 );

    SDL_RenderDrawLine( renderer, 520, 280, 520, 600 );

    /// Horizontal lines
    inDamNgang( renderer, 200, 40, 840, 40 );
    inDamNgang( renderer, 200, 160, 840, 160 );

    inDamNgang( renderer, 40, 200, 280, 200 );
    inDamNgang( renderer, 40, 280, 280, 280 );
    inDamNgang( renderer, 40, 600, 280, 600 );

    inDamNgang( renderer, 360, 200, 680, 200 );
    inDamNgang( renderer, 360, 280, 680, 280 );
    inDamNgang( renderer, 360, 600, 680, 600 );

    inDamNgang( renderer, 760, 200, 1000, 200 );
    inDamNgang( renderer, 760, 280, 1000, 280 );
    inDamNgang( renderer, 760, 600, 1000, 600 );

    for( int i = 0; i < 7; i += 1 )
    {
        SDL_RenderDrawLine( renderer, 40, 320 + i*40, 280, 320 + i*40 );
        SDL_RenderDrawLine( renderer, 360, 320 + i*40, 680, 320 + i*40 );
        SDL_RenderDrawLine( renderer, 760, 320 + i*40, 1000, 320 + i*40 );
    }
}

/// Draw end
void inEnd ( SDL_Renderer * renderer )
{
    /// Paint
    SDL_SetRenderDrawColor( renderer, BROWN.r, BROWN.g, BROWN.b, 0 );
    SDL_Rect bang1 = { 0, 0, 1080, 640};
    SDL_RenderFillRect(renderer, &bang1);

    SDL_SetRenderDrawColor( renderer, LIGHT_BROWN.r, LIGHT_BROWN.g, LIGHT_BROWN.b, 0 );
    SDL_Rect bang2 = { 40, 40, 960, 560};
    SDL_RenderFillRect(renderer, &bang2);

    SDL_SetRenderDrawColor( renderer, DARK_RED.r, DARK_RED.g, DARK_RED.b, 0 );
    SDL_Rect bang3 = { 360, 440, 320, 120};
    SDL_RenderFillRect(renderer, &bang3);

    SDL_SetRenderDrawColor( renderer, ORANGE.r, ORANGE.g, ORANGE.b, 0 );
    SDL_Rect bang4 = { 200, 120, 240, 160};
    SDL_Rect bang5 = { 600, 120, 240, 160};
    SDL_RenderFillRect(renderer, &bang4);
    SDL_RenderFillRect(renderer, &bang5);


    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );

    /// Vertical lines
    inDamDoc( renderer, 200, 120, 200, 280 );
    inDamDoc( renderer, 440, 120, 440, 280 );

    inDamDoc( renderer, 600, 120, 600, 280 );
    inDamDoc( renderer, 840, 120, 840, 280 );

    inDamDoc( renderer, 360, 440, 360, 560 );
    inDamDoc( renderer, 680, 440, 680, 560 );

    /// Horizontal lines
    inDamNgang( renderer, 200, 120, 440, 120 );
    inDamNgang( renderer, 200, 280, 440, 280 );

    inDamNgang( renderer, 600, 120, 840, 120 );
    inDamNgang( renderer, 600, 280, 840, 280 );

    inDamNgang( renderer, 360, 440, 680, 440 );
    inDamNgang( renderer, 360, 560, 680, 560 );
}

/// Buttons for tools
void setButtonTools ( ButtonTexture ButtonTools[] )
{
    /// Text
    ButtonTools[ 0 ].setName("I love TVDH hihihi");
    ButtonTools[ 1 ].setName("Tools");
    ButtonTools[ 2 ].setName("Points");
    ButtonTools[ 3 ].setName("Lines");
    ButtonTools[ NEW_POINT ].setName("New point");
    ButtonTools[ NEW_LINE ].setName("New line");
    ButtonTools[ CREAT ].setName("Create");
    ButtonTools[ DELETE ].setName("Delete");
    ButtonTools[ DONE ].setName("DONE!!!");

    /// Request
    for( int i = 9; i < 25; i += 1 )
    {
		ButtonTools[ i ].setName("Thay oi cho con game nay 10 diem duoc khong a");
		ButtonTools[ i ].setPosition( 40 + 1, 40 + 1, 960 - 1, 80 - 1 );
    }

    ButtonTools[ 9 ].setName("Draw a line through A1 and parallel d1 with at most 2 lines and 1 point");
    ButtonTools[ 10 ].setName("Draw an angle bisector of the angle with at most 2 lines and 1 point");

    /// Position
    ButtonTools[ 0 ].setPosition( 40 + 1, 40 + 1, 960 - 1, 80 - 1 );
    ButtonTools[ 1 ].setPosition( 40 + 1, 120 + 1, 160 - 1, 40 - 1 );
    ButtonTools[ 2 ].setPosition( 680 + 1, 120 + 1, 160 - 1, 40 - 1 );
    ButtonTools[ 3 ].setPosition( 840 + 1, 120 + 1, 160 - 1, 40 - 1 );
    ButtonTools[ 4 ].setPosition( 40 + 1, 160 + 1, 160 - 1, 40 - 1 );
    ButtonTools[ 5 ].setPosition( 40 + 1, 200 + 1, 160 - 1, 40 - 1 );
    ButtonTools[ 6 ].setPosition( 40 + 1, 480 + 1, 160 - 1, 40 - 1 );
    ButtonTools[ 7 ].setPosition( 40 + 1, 520 + 1, 160 - 1, 40 - 1 );
    ButtonTools[ 8 ].setPosition( 40 + 1, 560 + 1, 160 - 1, 40 - 1 );
}

/// Buttons for points
void setButtonPoints ( ButtonTexture ButtonPoints[] )
{
    /// Text
    ButtonPoints[ 49 ].setName("A1");
    ButtonPoints[ 50 ].setName("A2");
    ButtonPoints[ 51 ].setName("A3");
    ButtonPoints[ 52 ].setName("A4");
    ButtonPoints[ 53 ].setName("A5");
    ButtonPoints[ 54 ].setName("A6");
    ButtonPoints[ 55 ].setName("A7");
    ButtonPoints[ 56 ].setName("A8");
    ButtonPoints[ 57 ].setName("A9");
    ButtonPoints[ 58 ].setName("A10");
    ButtonPoints[ 59 ].setName("A11");
    ButtonPoints[ 60 ].setName("A12");
    ButtonPoints[ 61 ].setName("A13");
    ButtonPoints[ 62 ].setName("A14");
    ButtonPoints[ 63 ].setName("A15");
    ButtonPoints[ 64 ].setName("A16");
    ButtonPoints[ 65 ].setName("A17");
    ButtonPoints[ 66 ].setName("A18");
    ButtonPoints[ 67 ].setName("A19");
    ButtonPoints[ 68 ].setName("A20");
    ButtonPoints[ 69 ].setName("A21");
    ButtonPoints[ 70 ].setName("A22");

    /// 4 points at corners
    ButtonPoints[ 0 ].setPosition( 200, 120, 15, 15 );
    ButtonPoints[ 6 ].setPosition( 665, 120, 15, 15 );
    ButtonPoints[ 42 ].setPosition( 200, 585, 15, 15 );
    ButtonPoints[ 48 ].setPosition( 665, 585, 15, 15 );

    /// 5 points on the top horizontal line
    for( int i = 1; i < 6; i += 1 )
    {
        ButtonPoints[ i ].setPosition( 185 + i*80, 120, 30, 15 );
    }

    /// 5 points on the left vertical line
    for( int i = 1; i < 6; i += 1 )
    {
        ButtonPoints[ i*7 ].setPosition( 200, 105 + i*80, 15, 30 );
    }

    /// 5 points on the right vertical line
    for( int i = 1; i < 6; i += 1 )
    {
        ButtonPoints[ i*7 + 6 ].setPosition( 665, 105 + i*80, 15, 30 );
    }

    /// 5 points on the down horizontal line
    for( int i = 1; i < 6; i += 1 )
    {
        ButtonPoints[ i+42 ].setPosition( 185 + i*80, 585, 30, 15 );
    }

    /// 25 points inside
    for( int i = 1; i < 6; i += 1 )
    {
        for ( int j = 1; j < 6; j += 1 )
        {
            ButtonPoints[ i*7 + j ].setPosition( 185 + j*80, 105 + i*80, 30, 30 );
        }
    }

    /// 22 new points
    for( int i = 49; i < 71; i += 1 )
    {
        ButtonPoints[ i ].setPosition( 680 + ( (i-49)/11 )*80 + 1, 160 + ( (i-49)%11 )*40 + 1, 80 - 1, 40 - 1 );
    }
}

/// Buttons for lines
void setButtonLines( ButtonTexture ButtonLines[] )
{
    /// Text
    ButtonLines[ 14 ].setName("d1");
    ButtonLines[ 15 ].setName("d2");
    ButtonLines[ 16 ].setName("d3");
    ButtonLines[ 17 ].setName("d4");
    ButtonLines[ 18 ].setName("d5");
    ButtonLines[ 19 ].setName("d6");
    ButtonLines[ 20 ].setName("d7");
    ButtonLines[ 21 ].setName("d8");
    ButtonLines[ 22 ].setName("d9");
    ButtonLines[ 23 ].setName("d10");
    ButtonLines[ 24 ].setName("d11");
    ButtonLines[ 25 ].setName("d12");
    ButtonLines[ 26 ].setName("d13");
    ButtonLines[ 27 ].setName("d14");
    ButtonLines[ 28 ].setName("d15");
    ButtonLines[ 29 ].setName("d16");
    ButtonLines[ 30 ].setName("d17");
    ButtonLines[ 31 ].setName("d18");
    ButtonLines[ 32 ].setName("d19");
    ButtonLines[ 33 ].setName("d20");
    ButtonLines[ 34 ].setName("d21");
    ButtonLines[ 35 ].setName("d22");

    /// 7 horizontal lines
    ButtonLines[ 0 ].setPosition( 220, 120, 40, 15 );
    ButtonLines[ 6 ].setPosition( 220, 585, 40, 15 );

    for( int i = 1; i < 6; i += 1 )
    {
        ButtonLines[ i ].setPosition( 220, 105 + i*80, 40, 30 );
    }

    /// 7 vertical lines
    ButtonLines[ 7 ].setPosition( 200, 140, 15, 40 );
    ButtonLines[ 13 ].setPosition( 665, 140, 15, 40 );

    for( int i = 1; i < 6; i += 1 )
    {
        ButtonLines[ i+7 ].setPosition( 185 + i*80, 140, 30, 40 );
    }

    /// 22 new lines
    for( int i = 14; i < 36; i += 1 )
    {
        ButtonLines[ i ].setPosition( 840 + ( (i-14)/11 )*80 + 1 , 160 + ( (i-14)%11 )*40 + 1, 80 - 1, 40 - 1 );
    }
}

/// Button for menu
void setButtonMenu ( ButtonTexture ButtonMenu[] )
{
    /// Text
    ButtonMenu[ 0 ].setName("EUCLIDEAN");

    ButtonMenu[ 1 ].setName("Glossary");
    ButtonMenu[ 2 ].setName("Directed Line Segment");
    ButtonMenu[ 3 ].setName("Signed Angle");
    ButtonMenu[ 4 ].setName("Power of a point");
    ButtonMenu[ 5 ].setName("Conjugate");
    ButtonMenu[ 6 ].setName("Transformation");
    ButtonMenu[ 7 ].setName("Complete Quadrangle");
    ButtonMenu[ 8 ].setName("Barycentric Coordinates");
    ButtonMenu[ 9 ].setName("Trigonometric Laws");

    ButtonMenu[ 10 ].setName("Contents");
    ButtonMenu[ 11 ].setName("Length, Distant");
    ButtonMenu[ 12 ].setName("Angle Bisector");
    ButtonMenu[ 13 ].setName("Pole, Polar");
    ButtonMenu[ 14 ].setName("Isogonal");
    ButtonMenu[ 15 ].setName("Inversion");
    ButtonMenu[ 16 ].setName("Inscribed");
    ButtonMenu[ 17 ].setName("Centroid");
    ButtonMenu[ 18 ].setName("Perimeter");
    ButtonMenu[ 19 ].setName("Cross-ratio");
    ButtonMenu[ 20 ].setName("Parallel");
    ButtonMenu[ 21 ].setName("Coaxal");
    ButtonMenu[ 22 ].setName("Isotomic");
    ButtonMenu[ 23 ].setName("Homothety");
    ButtonMenu[ 24 ].setName("Orthocenter");
    ButtonMenu[ 25 ].setName("Median");
    ButtonMenu[ 26 ].setName("Area");

    ButtonMenu[ 27 ].setName("Techniques");
    ButtonMenu[ 28 ].setName("Harmonic Range");
    ButtonMenu[ 29 ].setName("Pascal's Theorem");
    ButtonMenu[ 30 ].setName("Radical Center");
    ButtonMenu[ 31 ].setName("Ceva's Theorem");
    ButtonMenu[ 32 ].setName("Monge' Theorem");
    ButtonMenu[ 33 ].setName("Brocard' Theorem");
    ButtonMenu[ 34 ].setName("Newton-Gauss Line");
    ButtonMenu[ 35 ].setName("Heron's Formula");

    ButtonMenu[ 36 ].setName("YOU");
    ButtonMenu[ 37 ].setName("WIN");
    ButtonMenu[ 38 ].setName("LOSE");
    ButtonMenu[ 39 ].setName("BACK TO MENU");

    /// Position
    ButtonMenu[ 0 ].setPosition( 200, 40, 640, 120 );

    ButtonMenu[ 1 ].setPosition( 40, 200, 240, 80 );

    for( int i = 2; i < 10; i += 1 )
    {
        ButtonMenu[ i ].setPosition( 40, 280 + (i-2)*40, 240, 40 );
    }

    ButtonMenu[ 10 ].setPosition( 360, 200, 320, 80 );

    for( int i = 11; i < 27; i += 1 )
    {
        ButtonMenu[ i ].setPosition( 360 + ((i-11)/8)*160, 280 + ((i-11)%8)*40, 160 , 40 );
    }

    ButtonMenu[ 27 ].setPosition( 760, 200, 240, 80 );

    for( int i = 28; i < 36; i += 1 )
    {
        ButtonMenu[ i ].setPosition( 760, 280 + (i-28)*40, 240, 40 );
    }

    ButtonMenu[ 36 ].setPosition( 200, 120, 240, 160 );
    ButtonMenu[ 37 ].setPosition( 600, 120, 240, 160 );
    ButtonMenu[ 38 ].setPosition( 600 + 2, 120 + 2, 240 - 4, 160 - 4 );
    ButtonMenu[ 39 ].setPosition( 360, 440, 320, 120 );
}

/// Text inside buttons
void renderText ( SDL_Renderer * renderer, ButtonTexture ButtonText[], int start, int finish )
{
    for( int i = start; i < finish; i += 1 )
    {
        ButtonText[ i ].render( renderer, ButtonText[i].Position.x + (ButtonText[i].Position.w - ButtonText[i].Width)/2 , ButtonText[i].Position.y + (ButtonText[i].Position.h - ButtonText[i].Height)/2 );
    }
}

/// Paint the buttons avalible to be used
void renderColorAvalible ( SDL_Renderer * renderer, ButtonTexture ButtonText[], int start, int finish, SDL_Color RectColor )
{
    for( int i = start; i < finish; i += 1)
    {
        SDL_SetRenderDrawColor( renderer, RectColor.r, RectColor.g, RectColor.b, 0 );
        SDL_RenderFillRect( renderer, &ButtonText[i].Position );
    }
}

/// Paint the chosen buttons
void renderColor ( SDL_Renderer * renderer, ButtonTexture ButtonText[], int start, int finish )
{
    for( int i = start; i < finish; i += 1 )
    {
        if(ButtonText[ i ].CurrentSprite == BUTTON_SPRITE_MOUSE_DOWN)
        {
            SDL_SetRenderDrawColor( renderer, RED.r, RED.g, RED.b, 0 );
            SDL_RenderFillRect( renderer, &ButtonText[i].Position );
        }
    }
}

/// Paint the chosen points
void renderColorPoint ( SDL_Renderer * renderer, ButtonTexture ButtonPoints[], Point Points[], int start, int finish )
{
    for( int i = start; i < finish; i += 1 )
    {
        if(ButtonPoints[ i ].CurrentSprite == BUTTON_SPRITE_MOUSE_DOWN)
        {
            int px = Points[i].x/ratioHomothety;
            int py = Points[i].y/ratioHomothety;

            SDL_Rect bang = { px - 3, py - 3, 7, 7 };

            SDL_SetRenderDrawColor( renderer, CRIMSON.r, CRIMSON.g, CRIMSON.b, 0 );
            SDL_RenderFillRect( renderer, &bang );
        }
    }
}

/// Paint the chosen lines
void renderColorLine ( SDL_Renderer * renderer, ButtonTexture ButtonLines[], Line Lines[], int start, int finish )
{
    for( int i = start; i < finish; i += 1 )
    {
        if(ButtonLines[ i ].CurrentSprite == BUTTON_SPRITE_MOUSE_DOWN)
        {
            int lAx = Lines[i].A.x/ratioHomothety;
            int lAy = Lines[i].A.y/ratioHomothety;
            int lBx = Lines[i].B.x/ratioHomothety;
            int lBy = Lines[i].B.y/ratioHomothety;

            SDL_SetRenderDrawColor( renderer, CRIMSON.r, CRIMSON.g, CRIMSON.b, 0 );
            SDL_RenderDrawLine( renderer, lAx, lAy, lBx, lBy );
        }
    }
}

/// Draw before choosing button
void inMauDiemDoan ( SDL_Renderer * renderer, Point Points[], Line Lines[], int currentPoints, int currentLines )
{
    inMau( renderer );
    inDiem( renderer, Points, 49 + currentPoints );
    inDoan( renderer, Lines, 14 + currentLines );
}

/// Draw after choosing button
void renderAll ( SDL_Renderer * renderer, ButtonTexture ButtonTools[], ButtonTexture ButtonPoints[], ButtonTexture ButtonLines[],
                 Point Points[], Line Lines[], int currentPoints, int currentLines, int Content )
{
    renderColor( renderer, ButtonTools, 0, TOTAL_TOOLS );
    renderColor( renderer, ButtonPoints, 49, 49 + currentPoints );
    renderColor( renderer, ButtonLines, 14, 14 + currentLines );

    inKhung( renderer );

    renderColorPoint ( renderer, ButtonPoints, Points, 0, 49 + currentPoints );
    renderColorLine ( renderer, ButtonLines, Lines, 0, 14 + currentLines );

    renderText( renderer, ButtonTools, 1, 9);
    renderText( renderer, ButtonTools, Content + 9, Content + 10);
    renderText( renderer, ButtonPoints, 0, 49 + currentPoints);
    renderText( renderer, ButtonLines, 14, 14 + currentLines);
}
