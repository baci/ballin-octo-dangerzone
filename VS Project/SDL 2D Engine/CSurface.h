#ifndef CSURFACE_H
#define CSURFACE_H

#include <SDL.h>
#include <SDL_image.h>

/**
	Wrapper class for SDL_Surface.
*/
class CSurface
{
    public:
        CSurface();

        /*
        loads a surface from a file in the used display format
        */
        static SDL_Surface* OnLoad(char* file);

        /*
        draws an image as a surface on another surface with the specified bounds
        */
        static bool OnDraw(SDL_Surface* surfDest, SDL_Surface* surfSrc, int x, int y);

        /*
        draws a tile as a surface on another surface with the specified bounds
        */
        static bool OnDraw(SDL_Surface* surfDest, SDL_Surface* surfSrc, int x, int y, int x2, int y2, int w, int h);

		static bool Transparent(SDL_Surface* Surf_Dest, int R, int G, int B, bool alpha);
    protected:
    private:
};

#endif // CSURFACE_H
