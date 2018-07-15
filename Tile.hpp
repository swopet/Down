#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <math.h>
#define SQRT_3 1.73205080757
#define SQRT_2 1.41421356237

class Tile {
	private:
		GLfloat color[3];
		GLfloat base_height;
		GLfloat height;
	public:
		Tile ();
		~Tile ();
		void set_color(GLfloat new_color[]);
		void set_height(GLfloat new_height);
		void draw(bool highlight);
		void update(int t);
};

#endif