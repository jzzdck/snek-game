#include "World.h"
#include <stdexcept>
#include <algorithm>


World::World (const sf::Vector2u & size, int rows, int cols) 
	: m_blocksize(sf::Vector2f(1.f * size.x/rows, 1.f * size.y/cols))
{
	if (rows<=1 || cols<=1) {
		throw std::invalid_argument("cant have <=1 rows or cols in World");
	}
	
	m_grid.resize(cols);
	for(size_t i=0;i<m_grid.size();i++) { 
		m_grid[i].resize(rows);
		for(size_t j=0;j<m_grid[i].size();j++) { 
			sf::Vector2f position(j * m_blocksize.x, i * m_blocksize.y);
			m_grid[i][j] = position;
		}
	}
}

const sf::Vector2f & World::GetPosition (int row, int col) const {
	if (row<0 || row >= m_grid.size()) {
		throw std::range_error("row not in range");
	}
	
	if (col<0 || col >= m_grid[0].size()) {
		throw std::range_error("col not in range");
	}
	
	return m_grid[row][col];
}

const sf::Vector2f & World::GetBlockSize ( ) const {
	return m_blocksize;
}

sf::Vector2u World::GetRandomPosition (int offset) const {
	int rowsize = m_grid.size();
	int colsize = m_grid[0].size();
	int random_row = std::rand()%(rowsize-2*offset)+offset;
	int random_col = std::rand()%(colsize-2*offset)+offset;
	
	return sf::Vector2u(random_row, random_col);
}

const sf::Vector2f & World::GetPosition (const sf::Vector2u & gridpos) const {
	return this->GetPosition(gridpos.x, gridpos.y);
}

bool World::CheckBoundaries (const sf::Vector2u & gridpos) const {
	return gridpos.x >= 0 && gridpos.x < m_grid.size()
		&& gridpos.y >= 0 && gridpos.y < m_grid[0].size();
		
}

