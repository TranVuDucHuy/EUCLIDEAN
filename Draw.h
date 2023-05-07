#ifndef DRAW_H
#define DRAW_H

//Using SDL, SDL_image, SDL_ttf, standard IO, math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "ButtonTexture.h"
#include "Line.h"
#include "Point.h"
#include "Const.h"

/// Starts up SDL and creates window
bool init( SDL_Window* &window, SDL_Renderer* &renderer, int screenWidth, int screenHeight );

/// Loads font for main board
bool loadFont( SDL_Renderer* renderer, TTF_Font* font, ButtonTexture ButtonTools[], ButtonTexture ButtonPoints[], ButtonTexture ButtonLines[] );

///Frees media and shuts down SDL
void close( SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font, ButtonTexture ButtonTools[],
            ButtonTexture ButtonPoints[], ButtonTexture ButtonLines[], ButtonTexture ButtonMenu[] );

/// Bold
void inDamDoc( SDL_Renderer * renderer, int x1, int y1, int x2, int y2 );

void inDamNgang( SDL_Renderer * renderer, int x1, int y1, int x2, int y2 );

/// Draw main board
void inMau( SDL_Renderer * renderer );

void inKhung( SDL_Renderer * renderer );

void inDiem( SDL_Renderer * renderer, Point Points[], int currentPoints );

void inDoan( SDL_Renderer * renderer, Line Lines[], int currentLines );

/// Buttons for tools
void setButtonTools( ButtonTexture ButtonTools[] );

/// Buttons for points
void setButtonPoints( ButtonTexture ButtonPoints[] );

/// Buttons for lines
void setButtonLines( ButtonTexture ButtonLines[] );

/// Text inside buttons
void renderText( SDL_Renderer * renderer, ButtonTexture ButtonText[], int start, int finish );

/// Paint the chosen buttons
void renderColor( SDL_Renderer * renderer, ButtonTexture ButtonText[], int start, int finish );

/// Paint the buttons avalible to be used
void renderColorAvalible( SDL_Renderer * renderer, ButtonTexture ButtonText[], int start, int finish, SDL_Color RectColor );

/// Paint the chosen points
void renderColorPoint( SDL_Renderer * renderer, ButtonTexture ButtonPoints[], Point Points[], int start, int finish );

/// Paint the chosen lines
void renderColorLine( SDL_Renderer * renderer, ButtonTexture ButtonLines[], Line Lines[], int start, int finish );

/// Load font for menu text
bool loadFontMenu( SDL_Renderer* renderer, TTF_Font* font, ButtonTexture ButtonMenu[] );

/// Draw menu
void inMauMenu( SDL_Renderer * renderer );

void inKhungMenu( SDL_Renderer * renderer );

/// Draw end
void inEnd( SDL_Renderer * renderer );

/// Button for menu
void setButtonMenu( ButtonTexture ButtonMenu[] );

/// Draw before choosing button
void inMauDiemDoan( SDL_Renderer * renderer, Point Points[], Line Lines[], int currentPoints, int currentLines );

/// Draw after choosing button
void renderAll( SDL_Renderer * renderer, ButtonTexture ButtonTools[], ButtonTexture ButtonPoints[],
                 ButtonTexture ButtonLines[], Point Points[], Line Lines[], int currentPoints, int currentLines, int Content );
#endif
