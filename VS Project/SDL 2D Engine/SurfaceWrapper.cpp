#include "SurfaceWrapper.h"

SurfaceWrapper::SurfaceWrapper()
{
}

SDL_Surface* SurfaceWrapper::Load(char* file)
{
    SDL_Surface* surfTmp = NULL;
    SDL_Surface* surfRet = NULL;

    if((surfTmp = IMG_Load(file)) == NULL)
        return NULL;

    surfRet = SDL_DisplayFormatAlpha(surfTmp);
    SDL_FreeSurface(surfTmp);

    return surfRet;
}

bool SurfaceWrapper::Draw(SDL_Surface* surfDest, SDL_Surface* surfSrc, int x, int y)
{
    if(surfDest==NULL || surfSrc==NULL)
        return false;

    SDL_Rect destR;
    destR.x = x;
    destR.y = y;

    SDL_BlitSurface(surfSrc, NULL, surfDest, &destR);

    return true;
}

bool SurfaceWrapper::Draw(SDL_Surface* surfDest, SDL_Surface* surfSrc, int x, int y, int x2, int y2, int w, int h)
{
    if(surfDest==NULL || surfSrc==NULL)
        return false;

    SDL_Rect destR;
    destR.x = x;
    destR.y = y;

    SDL_Rect srcR;
    srcR.x = x2;
    srcR.y = y2;
    srcR.w = w;
    srcR.h = h;

    SDL_BlitSurface(surfSrc, &srcR, surfDest, &destR);

    return true;
}

bool SurfaceWrapper::SetTransparency(SDL_Surface* Surf_Dest, int R, int G, int B, bool alpha) {
    if(Surf_Dest == NULL) {
        return false;
    }
 
    SDL_SetColorKey(Surf_Dest, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(Surf_Dest->format, R, G, B));
	if(!alpha)
		SDL_SetAlpha(Surf_Dest, SDL_RLEACCEL, 255);

    return true;
}
