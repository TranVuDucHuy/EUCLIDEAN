#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "ButtonTexture.h"
#include "Line.h"
#include "Point.h"
#include "Draw.h"
#include "Const.h"

/// Choose tool
void chooseTool ( SDL_Renderer * renderer, SDL_Event e, ButtonTexture ButtonTools[], ButtonTexture ButtonPoints[], ButtonTexture ButtonLines[], Point Points[], Line Lines[],
                 Status &gameStatus, bool &quit, int &MAX_POINTS, int &MAX_LINES, int &currentPoints, int &currentLines, Point TestPoints, Line TestLines, int Content );

/// Make point
void makePoint ( SDL_Renderer * renderer, SDL_Event e, ButtonTexture ButtonTools[], ButtonTexture ButtonPoints[], ButtonTexture ButtonLines[], Point Points[], Line Lines[],
                 Status &gameStatus, bool &quit, int From[], int &had, int &currentPoints, int &currentLines, int Content );

/// Make line
void makeLine ( SDL_Renderer * renderer, SDL_Event e, ButtonTexture ButtonTools[], ButtonTexture ButtonPoints[], ButtonTexture ButtonLines[], Point Points[], Line Lines[],
                 Status &gameStatus, bool &quit, int From[], int &had, int &currentPoints, int &currentLines, int Content );

/// Choose content
void chooseMenu ( SDL_Renderer * renderer, SDL_Event e, ButtonTexture ButtonMenu[], Status &gameStatus, bool &quit,
                 int &Content, int &currentPoints, int &currentLines, int CurrentPoints[], int CurrentLines[] );

/// Result
void endResult ( SDL_Renderer * renderer, SDL_Event e, ButtonTexture ButtonMenu[], Status &gameStatus, bool &quit );

#endif
