#ifndef GAME_H
#define GAME_H
#include "Window.h"
#include "Food.h"
#include "Snake.h"
#include "World.h"
#include "Being.h"
#include "MessageBox.h"

enum Index { iSnake = 0, iFood = 1 };

class Game {
public:
	Game();
	~Game();
	void Run();
private:
	void retrieveMessages();
	void handleInput();
	void update();
	void render();
	void clear();
	void start();
	
	Window m_window;
	sf::Clock m_clock;
	sf::Time m_elapsed;
	float m_frametime;
	MessageBox m_messager;
	
	std::vector<Being*> m_beings;
	World m_world;
};

#endif

