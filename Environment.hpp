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
	void draw();
};

#endif // ENVIRONMENT_HPP
