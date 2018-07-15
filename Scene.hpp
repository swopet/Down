#ifndef SCENE_HPP
#define SCENE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <math.h>
#include "Tile.hpp"
#include "Player.hpp"
#define SQRT_3 1.73205080757
#define SQRT_2 1.41421356237

class Scene {
	private:
		Tile * tiles;
		int width;
		int length;
	public:
		Scene(int new_width, int new_length);
		~Scene();
		void draw(Player *player);
		void update(int frame);
};

#endif