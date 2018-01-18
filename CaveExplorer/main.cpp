//CAVE EXPLORER 
#include "config.h"


playerClass player;
mapObject viewport;
mapObject portal;
enemy enemies[MaxEnemyNum] ;
gameEngine TheGameEngine;

int main()
{

	if (!config::loadMainConfig()) {
		std::cout << "Pliki gry zostaly uszkodzone! Gra nie moze zostac wczytana..." << std::endl;
		system("Pause");
		return 0;
	}

	console::initScreen();



	loadGameSaveVariable(1);



	menu::ShowMenu();


	system("PAUSE");
	return 0;
}