#ifndef TILE_HPP
#define TILE_HPP
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
namespace Tile{
	enum TileType {
		GB = 0,
		RB = 1,
		BW = 2
	};
	
	void load_textures();
	
	class Tile
	{
		private:
			TileType type;
			sf::Vector2f pos;
			GLfloat height;
		public:
			Tile();
			~Tile();
			
			GLfloat get_height();
			void set_height(GLfloat);
			
			TileType get_type();
			void set_type(TileType);
			
			sf::Vector2f get_pos();
			void set_pos(sf::Vector2f);
			
			void transform();
			void draw();
	};
}
#endif // TILE_HPP
