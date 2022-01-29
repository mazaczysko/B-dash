#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
using namespace std::string_literals;

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

class abstract_tile
{
public:
	virtual const sf::Texture &get_texture( ) const = 0;

};

class static_tile : public abstract_tile
{
public:
	static_tile( const std::string &path )
	{
		if ( !m_texture.loadFromFile(path) )
		{
			throw std::runtime_error("Error loading texture from "s + path);
		}
	}

	const sf::Texture &get_texture( ) const override 
	{
		return m_texture;
	}

protected:
	sf::Texture m_texture;

};

template <typename T>
class matrix
{
public:
	matrix( int w, int h ) :
		m_width(w), m_height(h), m_data(w*h)
	{
	}

	const T &at( int x, int y ) const
	{
		return m_data.at(x+y*m_width);
	}

	T &at( int x, int y )
	{
		return m_data.at(x+y*m_width);
	}

private:
	int m_width, m_height;
	std::vector<T> m_data;
};



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
		// double t = clock.getElapsedTime().asSeconds();

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
			
		win.clear( sf::Color::Cyan);
		s1.setOrigin(sf::Vector2f(16.f,16.f));
		s1.setPosition(sf::Vector2f(400.f,300.f));
		s1.setScale({5.f, 5.f});
		win.draw(s1);
		win.display();

		

	}
	
	return 0;
}