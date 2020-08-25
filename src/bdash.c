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

int main( int argc, char **argv )
{
	//Init allegro
 	al_init( );
	al_init_image_addon( );
	al_install_keyboard( );

	ALLEGRO_DISPLAY *win = al_create_display( 800, 600 );
	ALLEGRO_FONT *font = al_create_builtin_font( );

	ALLEGRO_TIMER *draw_timer = al_create_timer( 1.0 / 30.0 );
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

	int alive = 1, draw = 0;

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
					draw = 1;
					break;

				case ALLEGRO_EVENT_TIMER:
					if( ev.timer.source == draw_timer )
					{
						if( !draw )
						{
							al_clear_to_color( al_map_rgb( 125, 16, 127 ) );
							al_draw_text( font, al_map_rgb( 255, 255, 255 ), 0, 0, 0, "Hit your keyboard, come on!" );
							al_flip_display( );
						}
						else
						{
							// al_clear_to_color( al_map_rgb( 125, 40, 200 ) );
							// al_draw_text( font, al_map_rgb( 255, 255, 255 ), 0, 0, 0, "Hopefully it works!" );
							// al_draw_text( font, al_map_rgb( 255, 255, 255 ), 0, 10, 0, "Good job, but how do you close the window?" );
							// al_flip_display( );
							for( int i = 0; i < 5; i++ )
								al_draw_scaled_bitmap( tiles[i], 0, 0, 32, 32, 50 + i*64, 100, 64, 64, 0 );
							al_flip_display( );
						}
					}
					break;

				default:
					break;
			}
		}while( al_get_next_event( queue, &ev ) );
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
