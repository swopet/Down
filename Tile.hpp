#ifndef TILE_HPP
#define TILE_HPP
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
namespace Tile{
	enum tile_type {
		GB = 0,
		RB = 1,
		BW = 2
	};
	void load_textures();
	class Tile
	{
	private:
		tile_type type;
		sf::Vector2f pos;
		GLfloat height;
	public:
		Tile();
		~Tile();
		void set_pos(sf::Vector2f);
		void transform();
		void draw();
	};
}
#endif // TILE_HPP
