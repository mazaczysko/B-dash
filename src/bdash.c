#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

typedef enum
{
	TILE_AIR,
	TILE_WALL,
 	TILE_DIRT,
	TILE_DIAMOND,
	TILE_PLAYER
}tile_id;

typedef struct
{
	int x, y;
	ALLEGRO_BITMAP *tile;
}player;

typedef struct
{
	int width, height;
	ALLEGRO_BITMAP **tile;
}map;


void player_init( player *player, ALLEGRO_BITMAP *tile, int x, int y )
{
	player->tile = tile;
	player->x = x;
	player->y = y;
}

void map_init( map *map, int width, int height )
{
	map->width = width;
	map->height = height;
	map->tile = calloc( width * height, sizeof( ALLEGRO_BITMAP *) );
}

ALLEGRO_BITMAP *map_get_tile( map *map, int x, int y )
{
	if( x < 0 || y < 0 || x > map->width || y > map->height ) return NULL;
	return map->tile[x+y*map->width]; 
}

int map_put_tile( map *map, int x, int y, ALLEGRO_BITMAP *tile )
{
	if( x < 0 || y < 0 || x > map->width || y > map->height ) return 1;
	
	map->tile[x+y*map->width] = tile;
	return 0;
}

int player_move( map *map, player *player, int dx, int dy )
{
	if( player->x + dx >= map->width 
		|| player->y + dy >= map->height 
		|| player->x + dx < 0 
		|| player->y + dy < 0 
		|| map_put_tile( map, player->x + dx, player->y + dy, player->tile )
		|| map_put_tile( map, player->x, player->y, NULL )
		) return 1;

	player->x += dx;
	player->y += dy;
	return 0;
}


int main( int argc, char **argv )
{
	//Init allegro
 	al_init( );
	al_init_image_addon( );
	al_install_keyboard( );

	ALLEGRO_DISPLAY *win = al_create_display( 800, 600 );
	ALLEGRO_FONT *font = al_create_builtin_font( );

	ALLEGRO_TIMER *draw_timer = al_create_timer( 1.0 / 60.0 );
	ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue( );
	ALLEGRO_EVENT ev;

	al_register_event_source( queue, al_get_keyboard_event_source( ) );
	al_register_event_source( queue, al_get_display_event_source( win ) );
	al_register_event_source( queue, al_get_timer_event_source( draw_timer ) );

	al_start_timer( draw_timer );

	ALLEGRO_BITMAP *tiles[5] =
	{
		[TILE_AIR] = al_load_bitmap( "resources/air.png" ),
		[TILE_WALL] = al_load_bitmap( "resources/wall.png" ),
		[TILE_DIRT] = al_load_bitmap( "resources/dirt.png" ),
		[TILE_DIAMOND] = al_load_bitmap( "resources/diamond.png" ),
		[TILE_PLAYER] = al_load_bitmap( "resources/player.png" )
	};

	int alive = 1;

	player player;
	player_init( &player, tiles[TILE_PLAYER], 5, 5 );

	map map;
	map_init( &map, 20, 20 );

	ALLEGRO_BITMAP *t;

	map_put_tile( &map, player.x, player.y, player.tile );
	

	while( alive )
	{
		al_wait_for_event( queue, &ev );

		do
		{
			switch( ev.type )
			{
				case ALLEGRO_EVENT_DISPLAY_CLOSE:
					alive = 0;
					break;

				case ALLEGRO_EVENT_KEY_DOWN:
					switch( ev.keyboard.keycode )
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
					if( ev.timer.source == draw_timer )
					{
							al_clear_to_color( al_map_rgb( 0, 0, 0 ) );
							for( int i = 0; i < map.width; i++ )
							{
								for( int j = 0; j < map.height; j++ )
								{
									t = map_get_tile( &map, i, j );
									if( t != NULL )
									{
										al_draw_scaled_bitmap( t, 0, 0, 32, 32, i*64, j*64, 64, 64, 0 );
									}
								}
							}	
								
							al_flip_display( );
					}
					break;

				default:
					break;
			}
		}while( al_get_next_event( queue, &ev ) && alive );
	}

	for( int i = 0; i < 5; i++ )
	{
		al_destroy_bitmap( tiles[i] );
	}

	al_destroy_font( font );
	al_destroy_display( win );
	al_destroy_timer( draw_timer );
	al_destroy_event_queue( queue );

	return 0;
}
