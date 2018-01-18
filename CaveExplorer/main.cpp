//CAVE EXPLORER 
#include "config.h"
#include "confStaff.h"


playerClass player;
mapObject viewport;
mapObject portal;
shop theShop;
enemy enemies[MaxEnemyNum] ;
gameEngine TheGameEngine;

int main()
{

	console::initScreen();



	loadGameSaveVariable(1);



	menu::ShowMenu();


	system("PAUSE");
	return 0;
}