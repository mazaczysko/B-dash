#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include "map.h"
#include "player.h"


void player_init( player *player, ALLEGRO_BITMAP *tile, int x, int y )
{
	player->tile = tile;
	player->x = x;
	player->y = y;
}

int player_move( map *map, player *player, int dx, int dy )
{
	if ( player->x + dx >= map->width 
		|| player->y + dy >= map->height 
		|| player->x + dx < 0 
		|| player->y + dy < 0 
		|| map_put_tile( map, player->x + dx, player->y + dy, 1, player->tile )
		|| map_put_tile( map, player->x, player->y, 1, NULL )
		) return 1;

	player->x += dx;
	player->y += dy;
	return 0;
}