//CAVE EXPLORER 
#include "config.h"

unsigned char map[200][200];
unsigned int GameState = 0;
unsigned int LogLevel = 0;
unsigned int TotalTurns = 0;
unsigned int CurrentLevel = 0;
unsigned int EnemiesKilled = 0;

unsigned int GameSaveLoad = 1;

playerClass player;
COORD viewport;
COORD portal;
Enemy enemies[MaxEnemyNum] ;

int main()
{
	console::initScreen();



	loadGameSaveVariable(1);



	ShowMenu();


	system("PAUSE");
	return 0;
}