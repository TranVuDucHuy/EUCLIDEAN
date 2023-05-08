#ifndef BUTTONTEXTURE_H
#define BUTTONTEXTURE_H

/// Using SDL, SDL_image, SDL_ttf, standard IO, math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "Const.h"

using namespace std;

/// Texture wrapper class
struct ButtonTexture
{
    /// Top left position
    SDL_Rect Position;

    /// Currently used global sprite
    Button CurrentSprite;

    /// The actual hardware texture
    SDL_Texture* Texture;

    /// Text
    string Name;

    /// Image dimensions
    int Width;
    int Height;

    /// Initializes variables
    ButtonTexture();

    /// Deallocates memory
    ~ButtonTexture();

    /// Creates image from font string
    bool loadFromRenderedText( SDL_Renderer* renderer, TTF_Font* font,  SDL_Color textColor );

    /// Deallocates texture
    void free();

    /// Renders texture at given point
    void render( SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

    /// Sets name
    void setName(string s);

    /// Sets top left position
    void setPosition( int x, int y, int w, int h );

    /// Handles mouse event
    void handleEvent( SDL_Event* e );
};

#endif
