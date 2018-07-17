#include "Player.hpp"

Player::Player()
{
	pos = sf::Vector2f(10.5,10.5);
	height = 0.5;
	mesh = new Mesh::Mesh(Mesh::CUBE_MESH);
}

Player::~Player()
{
}

void Player::transform(){
	glTranslatef(-pos.x,-height,-pos.y);
}

void Player::draw(){
	glPushMatrix();
	mesh->draw();
	glPopMatrix();
}