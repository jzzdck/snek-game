#ifndef WINDOW_H
#define WINDOW_H
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class Window {
public:
	Window();
	Window(const std::string & title, const sf::Vector2u & size, bool fullscreen);
	void BeginDraw();
	void Update();
	void EndDraw();
	~Window();
	
	bool IsDone() const;
	void Close();
	bool IsFullScreen() const;
	sf::Vector2u GetSize() const;
	std::string GetTitle() const;
	
	void ToggleFullScreen();
	
	void Draw(sf::Drawable & to_draw);
private:
	void create();
	void destroy();
	
	sf::Vector2u m_size;
	sf::RenderWindow m_window;
	std::string m_title;
	bool m_done;
	bool m_fullscreen;
};

#endif

