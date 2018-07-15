#include "Scene.hpp"


Scene::Scene(int new_width = 10, int new_length = 10) {
	width = new_width;
	length = new_length;
	tiles = (Tile *)malloc(width*length*sizeof(Tile));
	GLfloat heights[width*length];
	GLfloat new_height;
	for (int x = 0; x < width; x++){
		for (int z = 0; z < length; z++){
			new_height = 5.0;
			
			heights[x*length+z] = new_height;
			
		}
	}
	for (int x = 0; x < width; x++){
		for (int z = 0; z < length; z++){
			int curr_x;
			int curr_z;
			//smooth it out a bit here
			new_height = 0.0;
			curr_x = x;
			curr_z = z;
			new_height += 0.4*heights[curr_x*length+curr_z];
			if (x == 0) curr_x = x;
			else curr_x = x-1;
			new_height += 0.15*heights[curr_x*length+curr_z];
			if (x == width-1) curr_x = x;
			else curr_x = x+1;
			new_height += 0.15*heights[curr_x*length+curr_z];
			curr_x = x;
			if (z == 0) curr_z = z;
			else curr_z = z-1;
			new_height += 0.15*heights[curr_x*length+curr_z];
			if (z == length-1) curr_z = z;
			else curr_z = z+1;
			new_height += 0.15*heights[curr_x*length+curr_z];
			GLfloat new_color[] = {1.0-new_height/10.0,0.0,new_height/10.0};
			tiles[x*length+z].set_height(new_height);
			tiles[x*length+z].set_color(new_color);
		}
	}
}

Scene::~Scene() {
	//Destructor
}

void Scene::draw(Player *player) {
	for (int x = 0; x < width; x++){
		for (int z = 0; z < length; z++){
			glPushMatrix();
			glTranslatef(x,0.0,z);
			tiles[x*length+z].draw(((int)player->pos.x ==x && (int)player->pos.z==z));
			glPopMatrix();
		}
	}
}

void Scene::update(int frame) {
	for (int x = 0; x < width; x++){
		for (int z = 0; z < length; z++){
			tiles[x*length+z].update(frame);
		}
	}
}
