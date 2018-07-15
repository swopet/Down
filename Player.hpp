#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

class Player
{
private:
	sf::Vector2f pos;
	GLfloat height;
public:
	Player();
	~Player();
	void transform();
	void draw();
};

#endif // PLAYER_HPP
