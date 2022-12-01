#include "MessageBox.h"
#include <algorithm>

MessageBox::MessageBox (int visible_lines,int charsize,float width,sf::Vector2f position) :
	m_visible_lines(visible_lines)
{
	// text init
	m_font.loadFromFile("DePixelHalbfett.ttf");
	m_content.setFont(m_font);
	m_content.setString("");
	m_content.setCharacterSize(charsize);
	m_content.setFillColor(sf::Color::White);
	sf::Vector2f offset(3.f,6.f);
	m_content.setPosition(position + offset);
	
	// backdrop init
	m_backdrop.setSize({width, float(visible_lines * (charsize + offset.y/2.f))});
	m_backdrop.setFillColor(sf::Color(100.f,100.f,100.f,50.f));
	m_backdrop.setPosition(position);
}
	
MessageBox::MessageBox() : MessageBox(5,12,250.f,{5.f,5.f}) {
	
}

void MessageBox::Add (std::string message) {
	m_content.setFillColor(sf::Color::White);
	m_backdrop.setFillColor(sf::Color(100.f,100.f,100.f,50.f));
	
	m_messages.push_back(message);
	if (m_messages.size() >= m_visible_lines) {
		m_messages.erase(m_messages.begin());
	}
}

void MessageBox::Clear ( ) {
	m_messages.clear();
}

void MessageBox::Draw (Window & window) {
	std::string messages;
	
	for(auto &str : m_messages) {
		messages += str + "\n";
	}
	
	if (!messages.empty()) {
		m_content.setString(messages);
		window.Draw(m_content);
		window.Draw(m_backdrop);
	}
}

sf::Color attenuate(const sf::Color &c) {
	return sf::Color(c.r,c.g,c.b,std::max(c.a*0.999998f,30.f));
}

void MessageBox::Update ( ) {
	m_content.setFillColor(attenuate(m_content.getFillColor()));
	m_backdrop.setFillColor(attenuate(m_backdrop.getFillColor()));
}
