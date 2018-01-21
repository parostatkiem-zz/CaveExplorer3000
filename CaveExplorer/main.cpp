//CAVE EXPLORER 
#include "config.h"
#include "confStaff.h"


playerClass player;
mapObject viewport;
mapObject portal;
shop theShop;
enemy enemies[MaxEnemyNum] ;
gameEngine TheGameEngine;



using namespace std;

int main()
{
	//gameEngine::FillShopItemsPrototype();
	console::initScreen();



	loadGameSaveVariable(1);



	menu::ShowMenu();


	system("PAUSE");
	return 0;
}