#include "Environment.hpp"
#include "SFML/OpenGL.hpp"

Environment::Environment()
{
	chunks.insert(std::pair<std::pair<int,int>,Chunk *>(std::pair<int,int>(0,0),new Chunk()));
}

Environment::~Environment()
{
}

Chunk* Environment::get_chunk(std::pair<int, int> chunk_location) {
	return chunks[chunk_location];
}

void Environment::set_chunk(std::pair<int, int> chunk_location, Chunk* chunk) {
	chunks[chunk_location] = chunk;
}

void Environment::draw(){
	for (std::map<std::pair<int,int>,Chunk *>::iterator iter = chunks.begin(); iter != chunks.end(); iter++){
		glPushMatrix();
			glTranslatef(iter->first.first,0.0,iter->first.second);
			iter->second->draw();
		glPopMatrix();
	}
}

