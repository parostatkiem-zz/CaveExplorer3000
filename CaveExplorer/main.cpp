//CAVE EXPLORER 
#include "config.h"
#include "confStaff.h"

unsigned char area[200][200];
unsigned int GameState = 0;
unsigned int LogLevel = 0;
unsigned int TotalTurns = 0;
unsigned int CurrentLevel = 0;
unsigned int EnemiesKilled = 0;

unsigned int GameSaveLoad = 1;

playerClass player;
mapObject viewport;
mapObject portal;
enemy enemies[MaxEnemyNum] ;

int main()
{
	console::initScreen();



	loadGameSaveVariable(1);



	menu::ShowMenu();


	system("PAUSE");
	return 0;
}