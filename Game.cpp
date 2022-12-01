#include "Game.h"

int row = 25, col = 25;

Game::Game() : 
	m_window("kowloon jag",{640,640},false), 
	m_world(m_window.GetSize(), row, col),
	m_frametime(2.f)
{
	this->start();
}

void Game::Run ( ) {
	while(!m_window.IsDone()) {
		this->handleInput();
		this->update();
		this->render();
		m_elapsed += m_clock.restart();
	}
}

void Game::handleInput ( ) {
	m_beings[Index::iSnake]->HandleInput();
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		this->clear();
		this->start();
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		this->clear();
		m_window.Close();
	}
}

void Game::update ( ) {
	if (m_elapsed.asSeconds() >= 1.f/m_frametime) {
		m_window.Update();
		for(size_t i=0;i<m_beings.size();i++) { 
			m_beings[i]->SetPosition(m_world);
			m_beings[i]->Update(m_elapsed);
		}
		
		bool collides = false;
		if (m_beings[Index::iSnake]->CollidesWith(*m_beings[Index::iFood])) {
			m_beings[Index::iSnake]->CollisionReaction(m_world);
			m_beings[Index::iFood]->CollisionReaction(m_world);
			m_messager.Add("An apple was eaten.");
			collides = true;
		}
		
		m_elapsed -= sf::seconds(1.f/m_frametime);
		if (collides) m_frametime += 0.5f;
	}
	
	m_messager.Update();
	this->retrieveMessages();
}

void Game::render ( ) {
	m_window.BeginDraw();
	for(size_t i=0;i<m_beings.size();i++) { 
		m_beings[i]->Draw(m_window);
	}
	
	m_messager.Draw(m_window);
	m_window.EndDraw();
}

Game::~Game ( ) {
	this->clear();
}

void Game::clear ( ) {
	for(size_t i=0;i<m_beings.size();i++) delete m_beings[i];
	
	m_frametime = 2.f;
	m_beings.clear();
	m_messager.Clear();
}

void Game::start ( ) {
	m_beings.push_back(new Snake);
	m_beings.push_back(new Food);
	for(size_t i=0;i<m_beings.size();i++) {
		m_beings[i]->Setup(m_world);
		m_beings[i]->SetPosition(m_world);
	}
}

void Game::retrieveMessages ( ) {
	for(size_t i=0;i<m_beings.size();i++) { 
		for(size_t j=0;j<m_beings[i]->Messages.size();j++) { 
			m_messager.Add(m_beings[i]->Messages[j]);
		}
		
		m_beings[i]->Messages.clear();
	}
}

