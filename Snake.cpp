#include "Snake.h"
#include <algorithm>
#include <iomanip>
#include <iostream>

Snake::Snake() : m_dir(Direction::None), has_lost(false) {
	sf::RectangleShape head({1.f,1.f});
	head.setFillColor(sf::Color::Green);
	m_model.push_back(head);
}

void Snake::move ( ) {
	switch (m_dir) {
	case Direction::Right:
		++m_gridpos.y; break;
	case Direction::Left:
		--m_gridpos.y; break;
	case Direction::Down:
		++m_gridpos.x; break;
	case Direction::Up:
		--m_gridpos.x; break;
	case Direction::None: break;
	default:
		throw std::logic_error("invalid direction"); 
		break;
	}
}

void Snake::Draw (Window & window) {
	for( std::list<sf::RectangleShape>::iterator it=m_model.begin(); it!=m_model.end(); ++it ) { 
		window.Draw(*it);
	}
}

void Snake::grow ( ) {
	sf::RectangleShape tail = m_model.front();
	tail.setFillColor(sf::Color::Yellow);
	m_model.push_back(tail);
}

void Snake::Update (const sf::Time & elapsed) {
	if (collidesWithItself()) { 
		has_lost = true;
	} else {
		this->move();
	}
}

void Snake::HandleInput ( ) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_dir != Direction::Down) {
		m_dir = Direction::Up;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_dir != Direction::Up) {
		m_dir = Direction::Down;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_dir != Direction::Left) {
		m_dir = Direction::Right;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_dir != Direction::Right) {
		m_dir = Direction::Left;
	}
}

void Snake::Setup (World & world) {
	auto blocksize = world.GetBlockSize();
	for( std::list<sf::RectangleShape>::iterator it=m_model.begin(); it!=m_model.end(); ++it ) { 
		it->setScale(blocksize);
	}
	
	m_gridpos = world.GetRandomPosition(1);
}

void Snake::SetPosition (World & world) {
	m_model.front().setFillColor(sf::Color::Yellow);
	m_model.push_front(m_model.back());
	m_model.pop_back();
	m_model.front().setFillColor(sf::Color::Green);
	if (!world.CheckBoundaries(m_gridpos)) {
		has_lost = true;
	} else {
		m_model.front().setPosition(world.GetPosition(m_gridpos));
	}
}

void Snake::CollisionReaction (World & world) {
	this->grow();
}

bool Snake::collidesWithItself ( ) {
	for( std::list<sf::RectangleShape>::iterator it=m_model.begin(); it!=m_model.end(); ++it ) { 
		for( std::list<sf::RectangleShape>::iterator it2=m_model.begin(); it2!=m_model.end(); ++it2 ) { 
			if (it!=it2 && it->getPosition() == it2->getPosition()) {
				return true;
			}
		}	
	}
	
	return false;
}

