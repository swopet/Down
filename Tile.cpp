#include "Tile.hpp"

Tile::Tile()
{
	height = 0.0;
	pos = sf::Vector2f(0.0,0.0);
}

Tile::~Tile()
{
}

void Tile::set_pos(sf::Vector2f new_pos){
	pos = new_pos;
}

void Tile::transform(){
	glTranslatef(pos.x,height,pos.y);
}

void Tile::draw(){
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_QUADS);
	glVertex3f(0.0,0.0,0.0);
	glVertex3f(0.0,0.0,1.0);
	glVertex3f(1.0,0.0,1.0);
	glVertex3f(1.0,0.0,0.0);
	glEnd();
}

