#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <math.h>
#include "Scene.hpp"
#define SQRT_3 1.73205080757
#define SQRT_2 1.41421356237

sf::RenderWindow * window;
double aspect;
int frame = 0;

Player * player;

Scene * demo_scene;

void update(){
    frame++;
    demo_scene->update(frame);
}


void draw_scene(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glViewport(0,0,window->getSize().x,window->getSize().y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0,1.0,-aspect,aspect,-100.0,100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glScalef(0.1,0.1,0.1);
    glRotatef(30.0,1.0,0.0,0.0);
    player->transform();
	
	player->draw();
    demo_scene->draw(player);
}

void init(){
    srand(time(NULL));
    aspect = (double)window->getSize().x/(double)window->getSize().y;
    demo_scene = new Scene(20,20);
	player = new Player();
    glClearColor(0.0,0.0,0.0,1.0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

int main()
{
    sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 0;
	settings.antialiasingLevel = 8;
	settings.majorVersion = 3;
	settings.minorVersion = 0;
    window = new sf::RenderWindow(sf::VideoMode(800, 600), "One Windowy Boi", sf::Style::Default, settings);
    init();
    while (window->isOpen())
    {
        sf::Event event;
        bool moved = false;
		sf::Vector2f move_dir(0.0,0.0);
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
            }
        }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
			move_dir += sf::Vector2f(0.0,1.0);
			moved = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
			move_dir += sf::Vector2f(0.0,-1.0);
			moved = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
			player->rotate(-0.5);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
			player->rotate(0.5);
		}
		if (moved){
			player->move(move_dir);
		}
        update();
        draw_scene();
        window->display();
    }
}