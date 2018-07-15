#ifndef GAME_HPP
#define GAME_HPP
#include "Environment.hpp"
#include "Player.hpp"
class Game
{
private:
	Player *player;
	Environment *env;
public:
	Game();
	~Game();
	void update();
	void draw_scene();
};

#endif // GAME_HPP
