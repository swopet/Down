#include "Player.hpp"

Player::Player()
{
	pos = sf::Vector2f(10.0,10.0);
	height = 0.0;
}

Player::~Player()
{
}

void Player::transform(){
	glTranslatef(-pos.x,-height,-pos.y);
}

void Player::draw(){
	
}