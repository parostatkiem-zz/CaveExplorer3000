//CAVE EXPLORER 
#include "config.h"
#include "confStaff.h"


playerClass player;
mapObject viewport;
mapObject portal;
shop theShop;
enemy enemies[MaxEnemyNum] ;
gameEngine TheGameEngine;

static ShopItemType shopItemTypes[ShopItemTypesAmount];

int main()
{
	shopItemTypes[0] = { 0, "DMG" }; //weapon
	shopItemTypes[1] = { 1, "HP" }; //armor
	
	console::initScreen();



	loadGameSaveVariable(1);



	menu::ShowMenu();


	system("PAUSE");
	return 0;
}