#ifndef SNAKE_H
#define SNAKE_H
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Being.h"
#include <list>

enum Direction { None=0, Right=1, Left=2, Up=3, Down=4 };

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
	Direction getDirection() const;
	void move();
	void grow();
	void checkIfCutsItself();
	std::list<sf::RectangleShape>::iterator getCutStart();
	bool has_lost;
	int m_dir;
	int m_score;
	std::list<sf::RectangleShape> m_model;
};

#endif

