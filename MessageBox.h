#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H
#include <SFML/System/Vector2.hpp>
#include <string>
#include <vector>
#include "Window.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>

sf::Color attenuate(const sf::Color &c);

class MessageBox {
public:
	MessageBox();
	MessageBox(int visible_lines,int charsize,float width,sf::Vector2f position); 
	
	void Add(std::string message);
	void Clear();
	void Draw(Window & window);
	void Update();
private:
	std::vector<std::string> m_messages;
	int m_visible_lines;
	
	sf::RectangleShape m_backdrop;
	sf::Font m_font;
	sf::Text m_content;
};

#endif

