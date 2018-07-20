#include "Chunk.hpp"

Chunk::Chunk()
{
	for (int x = 0; x < CHUNKSIDELENGTH; x++){
		for (int y = 0; y < CHUNKSIDELENGTH; y++){
			tiles[x][y].set_pos(sf::Vector2f(x,y));
		}
	}
}

Chunk::~Chunk()
{
}

void Chunk::draw(){
	for (int i = 0; i < CHUNKSIDELENGTH; i++){
		for (int j = 0; j < CHUNKSIDELENGTH; j++) {
			glPushMatrix();
			tiles[i][j].transform();
			tiles[i][j].draw();
			glPopMatrix();
		}
	}
}

