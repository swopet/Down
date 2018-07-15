#ifndef CHUNK_HPP
#define CHUNK_HPP
#include "Tile.hpp"

class Chunk
{
private:
	Tile tiles[400]; //20x20
public:
	Chunk();
	~Chunk();
	void draw();
};

#endif // CHUNK_HPP
