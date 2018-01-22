//CAVE EXPLORER 
#include "config.h"


playerClass player;
mapObject viewport;
mapObject portal;
shop theShop;
enemy enemies[MaxEnemyNum] ;
gameEngine TheGameEngine;



using namespace std;

int main()
{



	if (!config::loadMainConfigWithLog()) {
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