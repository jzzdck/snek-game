#include "Snake.h"
#include <algorithm>
#include <iomanip>
#include <iostream>

Snake::Snake() :
	m_dir(Direction::None),
	has_lost(false) 
{
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
	if ((m_ndir == Direction::Up && m_dir != Direction::Down)
		|| (m_ndir == Direction::Down && m_dir != Direction::Up)
		|| (m_ndir == Direction::Left && m_dir != Direction::Right)
		|| (m_ndir ==Direction::Right && m_dir != Direction::Left)) 
	{
		m_dir = m_ndir;
	}
	
	auto cut_start = this->getCutStart();
	if (cut_start != m_model.end()) {
		m_model.erase(cut_start,m_model.end());
	}
	this->move();
}

void Snake::HandleInput ( ) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		m_ndir = Direction::Up;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		m_ndir = Direction::Down;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		m_ndir = Direction::Right;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		m_ndir = Direction::Left;
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
	if (!world.CheckBoundaries(m_gridpos)) {
		has_lost = true;
	} else {
		m_model.front().setFillColor(sf::Color::Yellow);
		m_model.push_front(m_model.back());
		m_model.pop_back();
		m_model.front().setFillColor(sf::Color::Green);
		m_model.front().setPosition(world.GetPosition(m_gridpos));
	}
}

void Snake::CollisionReaction (World & world) {
	this->grow();
}

std::list<sf::RectangleShape>::iterator Snake::getCutStart ( ) {
	auto head = m_model.begin();
	for( std::list<sf::RectangleShape>::iterator body_part=next(m_model.begin()); body_part!=m_model.end(); ++body_part ) { 
		if (head->getPosition() == body_part->getPosition()) {
			return body_part;
		}
	}
	
	return m_model.end();
}
