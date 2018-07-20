#ifndef CHUNK_HPP
#define CHUNK_HPP
#include "Tile.hpp"

#define CHUNKSIDELENGTH 20

class Chunk
{
	private:
		Tile::Tile tiles[CHUNKSIDELENGTH][CHUNKSIDELENGTH]; //20x20
	public:
		Chunk();
		~Chunk();
		void draw();
};

#endif // CHUNK_HPP
