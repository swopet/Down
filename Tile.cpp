#include "Tile.hpp"
namespace Tile {
	sf::Texture textures[3];
	
	void load_textures() {
		textures[BW].loadFromFile("../Resources/Sprites/Tiles/checker_bw.png");
		textures[RB].loadFromFile("../Resources/Sprites/Tiles/checker_rb.png");
		textures[GB].loadFromFile("../Resources/Sprites/Tiles/checker_gb.png");
	}
	
	Tile::Tile() 
	{
		type = GB;
		height = 0.0;
		pos = sf::Vector2f(0.0,0.0);
	}

	Tile::~Tile() 
	{
	}
	
	GLfloat Tile::get_height() {
		return height;
	}
	
	void Tile::set_height(GLfloat height) {
		this->height = height; 
	}
	
	TileType Tile::get_type() { 
		return type;
	}
	
	void Tile::set_type(TileType type) {
		this->type = type;
	}
	
	sf::Vector2f Tile::get_pos() {
		return pos;
	}

	void Tile::set_pos(sf::Vector2f pos) {
		this->pos = pos;
	}

	void Tile::transform() {
		glTranslatef(pos.x,height,pos.y);
	}

	void Tile::draw() {
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		glColor3f(1.0,1.0,1.0);
		glEnable(GL_TEXTURE_2D);
		sf::Texture::bind(&textures[type]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0,1.0);
		glVertex3f(0.0,0.0,0.0);
		glTexCoord2f(1.0,1.0);
		glVertex3f(0.0,0.0,1.0);
		glTexCoord2f(1.0,0.0);
		glVertex3f(1.0,0.0,1.0);
		glTexCoord2f(0.0,0.0);
		glVertex3f(1.0,0.0,0.0);
		glEnd();
		sf::Texture::bind(NULL);
		glDisable(GL_TEXTURE_2D);
	}
}
