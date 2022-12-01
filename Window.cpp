#include "Window.h"
#include <SFML/Graphics/Color.hpp>

Window::Window() {
	
}

Window::~Window ( ) {
	destroy();
}

Window::Window (const std::string & title, const sf::Vector2u & size, bool fullscreen) 
	: m_title(title), m_size(size), m_fullscreen(fullscreen), m_done(false)
{
	this->create();
}

void Window::BeginDraw ( ) {
	m_window.clear(sf::Color::Black);
}

void Window::Update ( ) {
	sf::Event event;
	
	while(m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			m_done = true;
		} else if (event.type == sf::Event::KeyPressed &&
				   event.key.code == sf::Keyboard::F5) 
		{
			this->ToggleFullScreen();
		}
	}
}

void Window::EndDraw ( ) {
	m_window.display();
}

bool Window::IsDone ( ) const {
	return m_done;
}

bool Window::IsFullScreen ( ) const {
	return m_fullscreen;
}

sf::Vector2u Window::GetSize ( ) const {
	return m_size;
}

void Window::ToggleFullScreen ( ) {
	m_fullscreen = !m_fullscreen;
	this->destroy();
	this->create();
}

void Window::Draw (sf::Drawable & to_draw) {
	m_window.draw(to_draw);
}

std::string Window::GetTitle ( ) const {
	return m_title;
}

void Window::create ( ) {
	auto style = (m_fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	m_window.create({m_size.x, m_size.y, 32}, m_title, style);
	m_window.setFramerateLimit(60);
}

void Window::destroy ( ) {
	m_window.close();
}

void Window::Close ( ) {
	this->destroy();
}

