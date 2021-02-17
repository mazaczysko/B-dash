#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include "map.h"
#include "player.h"


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

int map_load( map *map, ALLEGRO_BITMAP **tiles, player *player, const char *path )
{
	char c;
	int x = 0, y = 0, w = 0, h = 0;
	FILE *file = fopen( path, "r" );
	ALLEGRO_BITMAP * tile;

	if ( file == NULL )
	{
		fprintf( stderr, "%s: fopen() error!\n", __FILE__ );
		return 0;
	}

	fscanf( file, "%d", &w );
	fscanf( file, "%d", &h );
	
	map_init( map, w, h, 2 );


	while( (c = getc( file ))!= EOF )
	{
		switch ( c )
		{
			case '\n':
			case '\r':
				x = 0;
				y++;
				break;

			case 'W':
				tile = tiles[TILE_WALL];
				break;

			case '.':
				tile = tiles[TILE_DIRT];
				break;
			
			case 'd':
				tile = tiles[TILE_DIAMOND];
				break;

			case 'r':
				tile = tiles[TILE_BOULDER];
				break;

			case 'X':
				tile = tiles[TILE_DOOR];
				break;

			case 'P':
				player_init( player, tiles[TILE_PLAYER], x, y );
				break;
		
			default:
				tile = tiles[TILE_AIR];
				break;
		}

		map_put_tile( map, x++, y, 0, tile );
	}

	fclose( file );

	return 0;
}