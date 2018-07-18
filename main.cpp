#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <math.h>
#include "Game.hpp"
#include <Winsock2.h>
#define SQRT_3 1.73205080757
#define SQRT_2 1.41421356237

sf::RenderWindow * window;
Game * game;
double aspect;

void init(){
    srand(time(NULL));
    aspect = (double)window->getSize().y/(double)window->getSize().x;
    glClearColor(0.0,0.0,0.0,0.0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
	Tile::load_textures();
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
    window = new sf::RenderWindow(sf::VideoMode(768, 432), "One Windowy Boi", sf::Style::Default, settings);
    init();
	clock_t start;
	clock_t stop;
	start = clock();
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
		game->process_input();
        game->update();
        game->draw_scene();
		stop = clock();
		double elapsed = double(stop-start)*1000.0/CLOCKS_PER_SEC;
            if (elapsed < 33) Sleep(33-elapsed);
        window->display();
		start = clock();
    }
}