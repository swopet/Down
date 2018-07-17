#include "Player.hpp"
#define SQRT_2 1.41421356237f

Player::Player()
{
	speed = 0.005f;
	moved = false;
	pos = sf::Vector2f(10.0,10.0);
	height = 0.5;
	mesh = new Mesh::Mesh(Mesh::CUBE_MESH);
	texture.loadFromFile("../Resources/Sprites/player.png");
}

Player::~Player()
{
}

void Player::transform(){
	glTranslatef(-pos.x,-height,-pos.y);
}

void Player::move(sf::Vector2i direction){
	if (direction.x == 0 && direction.y == 0){
		moved = false;
	}
	else {
		sf::Vector2f move_dir = SQRT_2/(float)sqrt(abs(direction.x)+abs(direction.y))*sf::Vector2f(direction.x+direction.y,direction.x-direction.y);
		pos = pos + move_dir*speed;
		moved = true;
	}
}

void Player::update(){
	if (!moved){
		double intx, inty;
		sf::Vector2f decimals(modf(pos.x,&intx),modf(pos.y,&inty));
		if (decimals.x >= 0.5) intx = intx + 1.0;
		else if (decimals.x <= -0.5) intx = intx - 1.0;
		if (decimals.y >= 0.5) inty = inty + 1.0;
		else if (decimals.y <= -0.5) inty = inty - 1.0;
		sf::Vector2f diff = sf::Vector2f(intx,inty)-pos;
		float diff_length = sqrt(diff.x*diff.x+diff.y*diff.y);
		if (diff_length < speed){
			pos = sf::Vector2f(intx,inty);
		}
		else {
			pos += diff * speed / diff_length;
		}
	}
}

void Player::draw(sf::RenderWindow * curr_window){
	glPushMatrix();
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	sf::Texture::bind(&texture);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glDisable(GL_LIGHTING);
	//draw the texture
	sf::Vector2f tex_size = sf::Vector2f(texture.getSize())*2.0f/768.0f;
	glTranslatef(-tex_size.x/2.0,-24.0/768.0,0.0); //center is center of bottom tile
	glBegin(GL_QUADS);
	glTexCoord2f(0.0,1.0);
	glVertex2f(0.0,0.0);
	glTexCoord2f(0.0,0.0);
	glVertex2f(0.0,tex_size.y);
	glTexCoord2f(1.0,0.0);
	glVertex2f(tex_size.x,tex_size.y);
	glTexCoord2f(1.0,1.0);
	glVertex2f(tex_size.x,0.0);
	glEnd();
	glDisable(GL_BLEND);
	sf::Texture::bind(NULL);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}