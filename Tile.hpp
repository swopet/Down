#ifndef TILE_HPP
#define TILE_HPP
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
class Tile
{
private:
	sf::Vector2f pos;
	GLfloat height;
public:
	Tile();
	~Tile();
	void set_pos(sf::Vector2f);
	void transform();
	void draw();
};

#endif // TILE_HPP
