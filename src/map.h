#ifndef MAP_H
#define MAP_H

#include <allegro5/allegro_image.h>

typedef struct
{
	int width, height, depth;
	ALLEGRO_BITMAP **tile;
}map;

extern void map_init( map *map, int width, int height, int depth );
extern ALLEGRO_BITMAP *map_get_tile( map *map, int x, int y, int z );
extern int map_put_tile( map *map, int x, int y, int z, ALLEGRO_BITMAP *tile ); 


#endif