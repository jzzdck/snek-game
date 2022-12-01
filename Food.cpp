#include "Food.h"
#include <SFML/Graphics/Color.hpp>

Food::Food() 
	: m_model(0.5f)
{
	m_model.setFillColor(sf::Color::Red);
}

void Food::Draw (Window & window) {
	window.Draw(m_model);
}

void Food::Update (const sf::Time & elapsed) {
	
}

void Food::HandleInput ( ) {
	
}

void Food::Setup (World & world) {
	m_model.setScale(world.GetBlockSize());
	m_gridpos = world.GetRandomPosition(0);
}

void Food::SetPosition (World & world) {
	m_model.setPosition(world.GetPosition(m_gridpos));
}

void Food::CollisionReaction (World & world) {
	m_gridpos = world.GetRandomPosition(0);
}

