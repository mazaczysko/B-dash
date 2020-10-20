#ifndef PLAYER_H
#define PLAYER_H

#include <allegro5/allegro_image.h>

typedef struct
{
	int x, y;
	ALLEGRO_BITMAP *tile;
}player;

extern void player_init( player *player, ALLEGRO_BITMAP *tile, int x, int y );
extern int player_move( map *map, player *player, int dx, int dy );

#endif