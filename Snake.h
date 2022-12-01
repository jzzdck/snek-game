#ifndef SNAKE_H
#define SNAKE_H
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Being.h"
#include <list>

enum Direction { None, Right, Left, Up, Down };

class Snake : public Being {
public:
	Snake();
	void SetPosition(World &world) override;
	void Setup(World &world) override;
	void Draw(Window &window) override;
	void Update(const sf::Time &elapsed) override;
	void HandleInput() override;
	void CollisionReaction(World & world) override;
private:
	void move();
	void grow();
	bool collidesWithItself();
	bool has_lost;
	int m_dir;
	std::list<sf::RectangleShape> m_model;
};

#endif

