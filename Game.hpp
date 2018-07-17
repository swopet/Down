#ifndef GAME_HPP
#define GAME_HPP
#include "Environment.hpp"
#include "Player.hpp"
#define SQRT_3 1.73205080757
#define SQRT_2 1.41421356237
class Game
{
private:
	Player *player;
	Environment *env;
public:
	Game();
	~Game();
	void process_input();
	void update();
	void draw_scene();
};

#endif // GAME_HPP
