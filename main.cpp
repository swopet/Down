#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <math.h>
#include "Game.hpp"
#define SQRT_3 1.73205080757
#define SQRT_2 1.41421356237

sf::RenderWindow * window;
Game * game;
double aspect;

void init(){
    srand(time(NULL));
    aspect = (double)window->getSize().y/(double)window->getSize().x;
    glClearColor(0.0,0.0,0.0,1.0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
	game = new Game();
}

int main()
{
    sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 0;
	settings.antialiasingLevel = 8;
	settings.majorVersion = 3;
	settings.minorVersion = 0;
    window = new sf::RenderWindow(sf::VideoMode(1280, 720), "One Windowy Boi", sf::Style::Default, settings);
    init();
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
            }
			if (event.type == sf::Event::Resized)
			{
				aspect = (double)window->getSize().y/(double)window->getSize().x;
			}
        }
        game->update();
        game->draw_scene();
        window->display();
    }
}