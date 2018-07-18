#include "Tile.hpp"
namespace Tile{
	sf::Texture textures[3];
	void load_textures(){
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

	void Tile::set_pos(sf::Vector2f new_pos){
		pos = new_pos;
	}

	void Tile::transform(){
		glTranslatef(pos.x,height,pos.y);
	}

	void Tile::draw(){
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
