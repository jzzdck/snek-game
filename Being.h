#ifndef BEING_H
#define BEING_H
#include <SFML/System/Time.hpp>
#include "Window.h"
#include "World.h"
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <string>

class Being {
public:
	Being();
	virtual void SetPosition(World &world) = 0;
	virtual void Setup(World &world) = 0;
	virtual void Draw(Window &window) = 0;
	virtual void Update(const sf::Time & elapsed) = 0;
	virtual void HandleInput() = 0;
	virtual void CollisionReaction(World & world) = 0;
	bool CollidesWith(const Being & another);
	
	std::vector<std::string> Messages;
protected:
	sf::Vector2u m_gridpos;
};

#endif

