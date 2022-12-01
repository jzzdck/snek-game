#include <SFML/Graphics.hpp>
#include "Game.h"
#include <cstdlib>

int main(int argc, char *argv[]){
	std::srand(time(nullptr));
	Game g;
	g.Run();
	
	return 0;
}

