#ifndef CONST_H
#define CONST_H

#include <SDL.h>

/// Screen dimension constants
const int SCREEN_WIDTH = 1040;
const int SCREEN_HEIGHT = 640;

/// Color constants
const SDL_Color YELLOW = {250, 250, 230};
const SDL_Color LIGHT_ORANGE = {250, 210, 180};
const SDL_Color RED = {250, 150, 140};
const SDL_Color ORANGE = {250, 190, 100}; //240 120 50
const SDL_Color DARK_RED = {240, 140, 80}; // 240 60 10
const SDL_Color BROWN = {200, 120, 70};
const SDL_Color GREY = {250, 250, 250};
const SDL_Color LIGHT_BROWN = {220, 180, 150};

/// Homothety constants
const int ratioHomothety = 2079; // 3*3*3*7*11

/// Button constants
const int TOTAL_TOOLS = 25;
const int TOTAL_POINTS = 71;
const int TOTAL_LINES = 36;
const int TOTAL_MENU = 40;
const int TOTAL_CONTENTS = 16;

/// Button status
enum Button
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_DOWN = 1,
	BUTTON_SPRITE_TOTAL = 2
};

/// Tool options
enum Tools
{
	NEW_POINT = 4,
    NEW_LINE = 5,
	CREAT = 6,
	DELETE = 7,
	DONE = 8,
};

/// Game status
enum Status
{
	IS_CREATING_NOTHING = 0,
	IS_CREATING_POINT = 1,
	IS_CREATING_LINE = 2,
	IS_WIN = 3,
	IS_LOSE = 4,
	IS_MENU = 5
};

#endif
