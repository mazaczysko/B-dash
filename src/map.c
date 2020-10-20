#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include "map.h"


void map_init( map *map, int width, int height, int depth )
{
	map->width = width;
	map->height = height;
	map->depth = depth;
	map->tile = calloc( width * height * depth, sizeof( ALLEGRO_BITMAP *) );
}

ALLEGRO_BITMAP *map_get_tile( map *map, int x, int y, int z )
{
	if ( x < 0 
		|| y < 0
		|| z < 0 
		|| x >= map->width 
		|| y >= map->height 
		|| z >= map->depth
		) return NULL;
	
	return map->tile[x * map->depth + y * map->depth * map->width + z]; 
}

int map_put_tile( map *map, int x, int y, int z, ALLEGRO_BITMAP *tile )
{
	if ( x < 0 
		|| y < 0 
		|| z < 0 
		|| x >= map->width 
		|| y >= map->height
		|| z >= map->depth 
		) return 1;
	
	map->tile[x * map->depth + y * map->depth * map->width + z] = tile;
	return 0;
}