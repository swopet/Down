#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <math.h>
#define SQRT_3 1.73205080757
#define SQRT_2 1.41421356237

class Player {
	private:
		double angle;
		float speed;
	public:
		sf::Vector3f pos;
		Player();
		~Player();
		void transform();
		void move(sf::Vector2f);
		void rotate(double);
		void draw();
};
#endif