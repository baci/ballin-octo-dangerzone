#ifndef _SURFACEWRAPPER_H_
	#define _SURFACEWRAPPER_H_

#include <SDL.h>
#include <SDL_image.h>

/**
	Wrapper class for SDL_Surface.
*/
class SurfaceWrapper
{
    public:
        SurfaceWrapper();

        // loads a surface from a file in the used display format
        static SDL_Surface* Load(char* file);

        // draws an image as a surface on another surface with the specified bounds
        static bool Draw(SDL_Surface* dest, SDL_Surface* src, int x, int y);

        // draws a tile as a surface on another surface with the specified bounds
        static bool Draw(SDL_Surface* dest, SDL_Surface* src, int x, int y, int x2, int y2, int w, int h);

		// sets a transparent color for a surface
		static bool SetTransparency(SDL_Surface* dest, int R, int G, int B, bool alpha);
};

#endif
