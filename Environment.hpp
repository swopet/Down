#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <map>
#include "Chunk.hpp"
#include "Tile.hpp"

class Environment
{
	private:
		std::map<std::pair<int,int>,Chunk *> chunks;
	public:
		Environment();
		~Environment();
		
		Chunk* get_chunk(std::pair<int, int>);
		void set_chunk(std::pair<int, int>, Chunk* );
		
		void draw();
};

#endif // ENVIRONMENT_HPP
