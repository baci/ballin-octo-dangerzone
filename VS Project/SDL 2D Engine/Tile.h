#ifndef _TILE_H_
    #define _TILE_H_
 
#include "Define.h"
 
enum {
    TILE_TYPE_NONE = 0,
 
    TILE_TYPE_NORMAL,
    TILE_TYPE_BLOCK
};
 
/*
	Tile as part of a map with ID and type.
*/
class Tile {
    public:
        int     TileID;
        int     TypeID;
 
    public:
        Tile();
};
 
#endif