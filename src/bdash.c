#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include "map.h"
#include "player.h"

#define TILE_CNT 7
#define WIN_WIDTH_BLOCKS 16
#define WIN_HEIGHT_BLOCKS 12
#define TILE_SIZE 64 

void cam_follow( int *cx, int *cy, map *map, player *player, int w, int h)
{
	if( player->x - *cx >= w - 2 ) *cx+=1;
	else if( player->x - *cx <= 2 ) *cx-=1;
	
	if( player->y - *cy >= h - 2 ) *cy+=1;
	else if( player->y - *cy <= 2 ) *cy-=1;
}

void map_render( map *map, int cx, int cy, int w, int h )
{
	ALLEGRO_BITMAP *t = NULL;

	al_clear_to_color( al_map_rgb( 0, 0, 0 ) );

	for( int x = 0; x < w; x++ )
	{
		for( int y = 0; y < h; y++ )
		{
			for( int z = 0; z < map->depth; z++ )
			{
				int mx = x + cx;
				int my = y + cy;
				if( mx < 0 || my < 0 || mx >= map->width || my >= map->height ) break;
				t = map_get_tile( map, mx, my, z );
				if( t != NULL )
				{
					al_draw_scaled_bitmap( t, 0, 0, 32, 32, x*TILE_SIZE, y*TILE_SIZE, TILE_SIZE, TILE_SIZE, 0 );
				}
			}
		}
	}	
}


int main( int argc, char **argv )
{
	//Init allegro
 	al_init( );
	al_init_image_addon( );
	al_install_keyboard( );

	ALLEGRO_DISPLAY *win = al_create_display( WIN_WIDTH_BLOCKS * TILE_SIZE, WIN_HEIGHT_BLOCKS * TILE_SIZE );
	ALLEGRO_FONT *font = al_create_builtin_font( );

	ALLEGRO_TIMER *draw_timer = al_create_timer( 1.0 / 60.0 );
	ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue( );
	ALLEGRO_EVENT ev;

	al_register_event_source( queue, al_get_keyboard_event_source( ) );
	al_register_event_source( queue, al_get_display_event_source( win ) );
	al_register_event_source( queue, al_get_timer_event_source( draw_timer ) );

	al_start_timer( draw_timer );

	ALLEGRO_BITMAP *tiles[TILE_CNT] =
	{
		[TILE_AIR] = al_load_bitmap( "resources/air.png" ),
		[TILE_WALL] = al_load_bitmap( "resources/wall.png" ),
		[TILE_DIRT] = al_load_bitmap( "resources/dirt.png" ),
		[TILE_DOOR] = al_load_bitmap( "resources/door.png" ),
		[TILE_DIAMOND] = al_load_bitmap( "resources/diamond.png" ),
		[TILE_BOULDER] = al_load_bitmap( "resources/boulder.png" ),
		[TILE_PLAYER] = al_load_bitmap( "resources/player.png" )
	};

	int alive = 1;
	
	//Init player
	player player;
	player_init( &player, tiles[TILE_PLAYER], 5, 5 );

	map map;
	map_init( &map, 20, 20, 2 );
	
	//Temporary map
	for( int i = 0; i < map.width; i++ )
		for( int j = 0; j < map.height; j++ )
			if( (i+j)%2 == 0 )
				map_put_tile( &map, i, j, 0, tiles[TILE_DIRT] );
			else
				map_put_tile( &map, i, j, 0, tiles[TILE_WALL] );
	
	map_put_tile( &map, player.x, player.y, 1,  player.tile );
	
	//Initialize camera position
	int cx = player.x - WIN_WIDTH_BLOCKS/2;
	int cy = player.y - WIN_HEIGHT_BLOCKS/2;

	while ( alive )
	{
		al_wait_for_event( queue, &ev );

		do
		{
			switch ( ev.type )
			{
				case ALLEGRO_EVENT_DISPLAY_CLOSE:
					alive = 0;
					break;

				case ALLEGRO_EVENT_KEY_DOWN:
					switch ( ev.keyboard.keycode )
					{
						case ALLEGRO_KEY_DOWN:
							player_move( &map, &player, 0, 1 );
							break;
						
						case ALLEGRO_KEY_UP:
							player_move( &map, &player, 0, -1);
							break;

						case ALLEGRO_KEY_RIGHT:
							player_move( &map, &player, 1, 0 );
							break;

						case ALLEGRO_KEY_LEFT:
							player_move( &map, &player, -1, 0 );
							break;

						default:
							break;

					}
					break;

				case ALLEGRO_EVENT_TIMER:
					if ( ev.timer.source == draw_timer )
					{
						cam_follow( &cx, &cy, &map, &player, WIN_WIDTH_BLOCKS, WIN_HEIGHT_BLOCKS ); 
						map_render( &map, cx, cy, WIN_WIDTH_BLOCKS, WIN_HEIGHT_BLOCKS );			
						al_flip_display( );
					}
					break;

				default:
					break;
			}
		}while( al_get_next_event( queue, &ev ) && alive );
	}

	for ( int i = 0; i < TILE_CNT; i++ )
	{
		al_destroy_bitmap( tiles[i] );
	}

	al_destroy_font( font );
	al_destroy_display( win );
	al_destroy_timer( draw_timer );
	al_destroy_event_queue( queue );

	return 0;
}
