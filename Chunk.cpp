#include "Chunk.hpp"

Chunk::Chunk()
{
	for (int x = 0; x < 20; x++){
		for (int y = 0; y < 20; y++){
			tiles[x*20+y].set_pos(sf::Vector2f(x,y));
		}
	}
}

Chunk::~Chunk()
{
}

void Chunk::draw(){
	for (int i = 0; i < 400; i++){
		glPushMatrix();
		tiles[i].transform();
		tiles[i].draw();
		glPopMatrix();
	}
}

