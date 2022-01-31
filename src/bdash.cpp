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

class world
{
public:
	world( int width, int height, const sf::Texture &bg_tex ) :
		m_map(width,height), m_bg_tex(bg_tex)
	{
		m_bg_tex.setRepeated(true);
	}
	
	void draw( sf::RenderWindow &win, int tile_size, sf::Vector2i map_pos, sf::Vector2i viewport_pos, sf::Vector2i viewport_size ) const
	{
		{
			sf::Sprite sprite;
			sprite.setTexture(m_bg_tex);
			sprite.setPosition(0,0);
			float kx = tile_size / static_cast<float>(m_bg_tex.getSize().x);
			float ky = tile_size / static_cast<float>(m_bg_tex.getSize().y);
			sprite.setScale(kx, ky);
			sprite.setColor(sf::Color(64,64,64));
			sprite.setTextureRect(sf::IntRect(0, 0, m_bg_tex.getSize().x * viewport_size.x, m_bg_tex.getSize().y * viewport_size.y));
			win.draw(sprite);
		}


		//viewport_size is in TILES!!!
		for ( int y = 0; y < viewport_size.y; y++ )
		{
			for ( int x = 0; x < viewport_size.x; x++ )
			{
				if ( auto ptr = m_map.at(map_pos.x + x, map_pos.y + y) )
				{
					sf::Sprite sprite;

					sprite.setTexture(ptr->get_texture());
					sprite.setPosition(sf::Vector2f(x*tile_size, y*tile_size));
					
					float kx = tile_size / static_cast<float>(ptr->get_texture().getSize().x);
					float ky = tile_size / static_cast<float>(ptr->get_texture().getSize().y);
					sprite.setScale(kx,ky);

					win.draw(sprite);
				}
				
			}
		}
		
	}

	const auto &at( int x, int y ) const
	{
		return m_map.at(x,y);
	}

	auto &at( int x, int y )
	{
		return m_map.at(x,y);
	}

private:
	matrix<std::shared_ptr<abstract_tile>> m_map;  
	sf::Texture m_bg_tex;
};

template <typename T>
T map_range( T x, T x1, T x2, T y1, T y2)
{
	return y1 + ((y2-y1)/(x2-x1))*(x-x1); 
}

sf::Texture load_texture( const std::string &path )
{
	sf::Texture texture;
	if ( !texture.loadFromFile(path) )
	{
		throw std::runtime_error("Error loading texture from "s + path);
	}
	
	return texture;
}

int main( )
{
	sf::RenderWindow win(sf::VideoMode(800,600), "B-dash build " __TIME__);
	sf::Clock clock;
	
	sf::Music music;
	music.openFromFile("../resources/sounds/10000.wav");
	music.setLoop(true);
	music.play();

	sf::Texture texture;
	texture.loadFromFile("../resources/graphics/player.png");

	auto player = std::make_shared<static_tile>("../resources/graphics/player.png");


	world w( 64, 64, load_texture("../resources/graphics/wall.png") );
	for( int i = 0; i < 64; i++ )
		for( int j = 0; j < 64; j++ )
			if( (i+j)%2 == 0)
				w.at(i,j) = player;



	while ( win.isOpen() )
	{

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
		w.draw( win, 64 , {0,0}, {0,0}, {32,32});
		win.display();
	}
	
	return 0;
}