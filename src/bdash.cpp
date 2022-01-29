#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>

void handle_key(sf::RenderWindow &win, sf::Event const &ev)
{
    switch ( ev.key.code )
    {
        case sf::Keyboard::Key::Q:
            win.close();
            break;


        default:
            break;
    }
}

template <typename T>
T map_range( T x, T x1, T x2, T y1, T y2)
{
    return y1 + ((y2-y1)/(x2-x1))*(x-x1); 
}
int main( )
{
    sf::RenderWindow win(sf::VideoMode(800,600), "B-dash build " __TIME__);
    sf::Clock clock;
    
    sf::Music music;
    music.openFromFile("../resources/sounds/10000.wav");
    music.setLoop(true);
    music.play();
    



    while ( win.isOpen() )
    {
        double t = clock.getElapsedTime().asSeconds();

        for ( sf::Event ev; win.pollEvent(ev);)
        {
            switch ( ev.type )
            {
                case sf::Event::Closed:
                    win.close();
                    break;

                case sf::Event::KeyPressed:
                    handle_key(win, ev);
                    break;

                default:
                    break;       
            }
        }
            
        win.clear( sf::Color( map_range(sin(2*M_PI*0.25*t),-1.0,1.0,0.0,255.0), 255, 127));
        win.display();

        

    }
    
    return 0;
}