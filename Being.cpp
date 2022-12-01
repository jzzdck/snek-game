#include "Being.h"

Being::Being() {
	
}

bool Being::CollidesWith (const Being & another) {
	return m_gridpos == another.m_gridpos; 
}

