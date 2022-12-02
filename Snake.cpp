#include "Snake.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>

Snake::Snake() :
	m_dir(Direction::None),
	has_lost(false),
	m_score(0)
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
	tail.setPosition({-100,-100});
	
	m_model.push_back(tail);
	std::stringstream ss;
	ss << "You now are " << m_model.size() << " parts long.";
	Messages.push_back(ss.str());
}

void Snake::Update (const sf::Time & elapsed) {
	if (has_lost) return;	
	this->checkIfCutsItself();
	this->move();
}

void Snake::HandleInput ( ) {
	auto real_dir = this->getDirection();
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && real_dir != Direction::Down) {
		m_dir = Direction::Up;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && real_dir != Direction::Up) {
		m_dir = Direction::Down;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && real_dir != Direction::Left) {
		m_dir = Direction::Right;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && real_dir != Direction::Right) {
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
	if (has_lost) return;
	
	if (!world.CheckBoundaries(m_gridpos)) {
		has_lost = true;
		std::stringstream ss;
		ss << "You lost!   Score: " << m_score;
		Messages.push_back(ss.str());
		Messages.push_back("Press R to restart...");
	} else {
		m_model.front().setFillColor(sf::Color::Yellow);
		m_model.push_front(m_model.back());
		m_model.pop_back();
		m_model.front().setFillColor(sf::Color::Green);
		m_model.front().setPosition(world.GetPosition(m_gridpos));
	}
}

void Snake::CollisionReaction (World & world) {
	++m_score;
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

Direction Snake::getDirection ( ) const {
	if (m_model.size() == 1) return Direction::None;
	
	auto head_pos = m_model.front().getPosition();
	auto neck_pos = next(m_model.begin())->getPosition();
	if (head_pos.y == neck_pos.y) {
		return head_pos.x > neck_pos.x ? Direction::Right : Direction::Left; 
	} else {
		return head_pos.y > neck_pos.y ? Direction::Down : Direction::Up;
	}
}

void Snake::checkIfCutsItself ( ) {
	auto osize = m_model.size();
	auto cut_start = this->getCutStart();
	if (cut_start != m_model.end()) {
		m_model.erase(cut_start,m_model.end());
	}
	
	auto nsize = m_model.size();
	if (nsize != osize) { 
		std::stringstream ss;
		auto dif = osize - nsize;
		m_score -= dif;
		ss << "You ate " << osize-nsize << " parts of yourself...";
		Messages.push_back(ss.str());
	}
}

