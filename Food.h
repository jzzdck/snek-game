#ifndef FOOD_H
#define FOOD_H
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "Being.h"

class Food : public Being {
public:
	Food();
	void SetPosition(World &world) override;
	void Setup(World &world) override;
	void Draw(Window &window) override;
	void Update(const sf::Time &elapsed) override;
	void HandleInput() override;
	void CollisionReaction(World & world) override;
private:
	sf::CircleShape m_model;
};

#endif

