#ifndef MAP_H
#define MAP_H

#include <allegro5/allegro_image.h>

typedef enum
{
	TILE_AIR,
	TILE_WALL,
 	TILE_DIRT,
	TILE_DOOR,
	TILE_DIAMOND,
	TILE_BOULDER,
	TILE_PLAYER
}tile_id;

typedef struct
{
	int width, height, depth;
	ALLEGRO_BITMAP **tile;
}map;

extern void map_init( map *map, int width, int height, int depth );
extern ALLEGRO_BITMAP *map_get_tile( map *map, int x, int y, int z );
extern int map_put_tile( map *map, int x, int y, int z, ALLEGRO_BITMAP *tile ); 


#endif