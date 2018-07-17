#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "Mesh.hpp"
#include <math.h>

class Player
{
private:
	float speed;
	bool moved;
	sf::Texture texture;
	Mesh::Mesh * mesh;
	sf::Vector2f pos;
	GLfloat height;
public:
	Player();
	~Player();
	void transform();
	void draw(sf::RenderWindow *);
	void move(sf::Vector2i);
	void update();
};

#endif // PLAYER_HPP
