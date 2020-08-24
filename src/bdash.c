#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

int main( int argc, char **argv )
{
	//Init allegro
 	al_init( );
	al_install_keyboard( );

	ALLEGRO_DISPLAY *win = al_create_display( 500, 200);
	ALLEGRO_FONT *font = al_create_builtin_font( );

	ALLEGRO_TIMER *timer = al_create_timer( 1.0/ 30.0 );
	ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue( );
	ALLEGRO_EVENT ev;

	al_register_event_source( queue, al_get_keyboard_event_source( ) );
	al_register_event_source( queue, al_get_display_event_source( win ) );
	al_register_event_source( queue, al_get_timer_event_source( timer ) );

	al_start_timer( timer );

	al_clear_to_color( al_map_rgb( 125, 16, 127 ) );
	al_draw_text( font, al_map_rgb( 255, 255, 255 ), 0, 0, 0, "Hit your keyboard, come on!" );
	al_flip_display( );

	int alive = 1;

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
					al_clear_to_color( al_map_rgb( 125, 40, 200 ) );
					al_draw_text( font, al_map_rgb( 255, 255, 255 ), 0, 0, 0, "Hopefully it works!");
					al_draw_text( font, al_map_rgb( 255, 255, 255 ), 0, 10, 0, "Good job, but how do you close the window?" );
					al_flip_display( );
					break;

				default:
					al_flip_display( );
					break;
			}
		}while( al_get_next_event( queue, &ev ) );
	}

	al_destroy_font( font );
	al_destroy_display( win );
	al_destroy_timer( timer );
	al_destroy_event_queue( queue );

	return 0;
}
