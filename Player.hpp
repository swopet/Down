#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "Mesh.hpp"

class Player
{
private:
	Mesh::Mesh * mesh;
	sf::Vector2f pos;
	GLfloat height;
public:
	Player();
	~Player();
	void transform();
	void draw();
};

#endif // PLAYER_HPP
