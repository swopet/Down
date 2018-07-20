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

void Game::run_loop() {
	process_input();
	update();
	draw_scene();
}

void Game::process_input(){
	sf::Vector2i player_movement(0,0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		player_movement += sf::Vector2i(-1,0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		player_movement += sf::Vector2i(1,0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		player_movement += sf::Vector2i(0,1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		player_movement += sf::Vector2i(0,-1);
	}
	player->move(player_movement);
}

void Game::update(){
	player->update();
}

void Game::draw_scene(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glViewport(0,0,window->getSize().x,window->getSize().y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0,1.0,-aspect,aspect,-1000.0,1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
	double scale_fac = SQRT_2/16.0; //16 tiles diagonally across
    glScalef(scale_fac,scale_fac,scale_fac);
    glRotatef(30.0,1.0,0.0,0.0);
	glRotatef(45.0,0.0,1.0,0.0);
	GLfloat light_position[] = {1.0, 0.5, 1.0, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	
	glPushMatrix();
		player->transform();
		env->draw();
	glPopMatrix();
	
	player->draw(window);
}

