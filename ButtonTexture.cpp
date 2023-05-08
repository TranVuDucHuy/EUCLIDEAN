/// Using SDL, SDL_image, SDL_ttf, standard IO, math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "ButtonTexture.h"

using namespace std;

ButtonTexture::ButtonTexture()
{
	/// Initialize
	Texture = NULL;
	Width = 0;
	Height = 0;
	Name = "";
	Position.x = 0;
	Position.y = 0;
    Position.w = 0;
	Position.h = 0;
	CurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

ButtonTexture::~ButtonTexture()
{
	/// Deallocate
	free();
}

bool ButtonTexture::loadFromRenderedText( SDL_Renderer* renderer, TTF_Font* font, SDL_Color textColor )
{
	/// Get rid of preexisting texture
	free();

	/// Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( font, Name.c_str(), textColor );
	if( textSurface == NULL )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		/// Create texture from surface pixels
        Texture = SDL_CreateTextureFromSurface( renderer, textSurface );
		if( Texture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			/// Get image dimensions
			Width = textSurface->w;
			Height = textSurface->h;
		}

		/// Get rid of old surface
		SDL_FreeSurface( textSurface );
	}

	/// Return success
	return Texture != NULL;
}

void ButtonTexture::free()
{
	/// Free texture if it exists
	if( Texture != NULL )
	{
		SDL_DestroyTexture( Texture );
		Texture = NULL;
		Width = 0;
		Height = 0;
		Name = "";
        Position.x = 0;
        Position.y = 0;
        Position.w = 0;
        Position.h = 0;
        CurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
	}
}

void ButtonTexture::render( SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	/// Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, Width, Height };

	/// Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	/// Render to screen
	SDL_RenderCopyEx( renderer, Texture, clip, &renderQuad, angle, center, flip );
}

void ButtonTexture::setName(string s)
{
    Name = s;
}

void ButtonTexture::setPosition( int x, int y, int w, int h )
{
	Position.x = x;
	Position.y = y;
	Position.w = w;
	Position.h = h;
}

void ButtonTexture::handleEvent( SDL_Event* e )
{
	/// If mouse event happened
	if( e->type == SDL_MOUSEBUTTONDOWN )
	{
		/// Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		/// Check if mouse is in button
		bool inside = true;

		/// Mouse is left of the button
		if( x < Position.x )
		{
			inside = false;
		}
		/// Mouse is right of the button
		else if( x > Position.x + Position.w )
		{
			inside = false;
		}
		/// Mouse above the button
		else if( y < Position.y )
		{
			inside = false;
		}
		/// Mouse below the button
		else if( y > Position.y + Position.h )
		{
			inside = false;
		}

		/// Mouse is outside button
		if( !inside )
		{
			CurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		/// Mouse is inside button
		else
		{
			/// Set mouse over sprite
			switch( e->type )
			{
				case SDL_MOUSEBUTTONDOWN:
				CurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
				break;
			}
		}
	}
}
