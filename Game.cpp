#include "Game.hpp"

extern sf::RenderWindow * window;
extern double aspect;

Game::Game()
{
	env = new Environment();
	player = new Player();
}

Game::~Game()
{
}

void Game::update(){
	
}

void Game::draw_scene(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glViewport(0,0,window->getSize().x,window->getSize().y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0,1.0,-aspect,aspect,-100.0,100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glScalef(0.2,0.2,0.2);
    glRotatef(30.0,1.0,0.0,0.0);
	glRotatef(45.0,0.0,1.0,0.0);
	GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	player->draw();
	player->transform();
	env->draw();
}

