#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Shape.hpp>
using Grid = std::vector<std::vector<sf::Vector2f>>;

class World {
public:
	World(const sf::Vector2u &size, int rows, int cols);
	bool CheckBoundaries(const sf::Vector2u & gridpos) const; 
	const sf::Vector2f & GetPosition(int row, int col) const;
	const sf::Vector2f & GetPosition(const sf::Vector2u & gridpos) const;
	sf::Vector2u GetRandomPosition(int offset) const;
	const sf::Vector2f & GetBlockSize() const;
private:
	Grid m_grid;
	sf::Vector2f m_blocksize;
};

#endif

