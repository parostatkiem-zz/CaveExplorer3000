#pragma once

#include "time.h"

class mathem
{
public:
	//losowanie int z zakresu od do
	static int RandomInt(int min, int max);

	//zwraca dystans miêdzy dwoma punktami
	static int CalculateDistance(COORD a, COORD b);
};

class menu
{
public:
	//pokazuje menu - g³ówna pêtla gry
	static void ShowMenu();
};

class gameEngine
{
public:
	//sekcja zmiennych
	 unsigned char area[200][200];
	 unsigned int GameState;
	 unsigned int LogLevel;
	 unsigned int TotalTurns;
	 unsigned int CurrentLevel;
	 unsigned int EnemiesKilled;
	 unsigned int GameSaveLoad;

	 unsigned int Turns;
	 unsigned int CaveSegments;


	//reset mapy podczas rozgrywki
	static void RefreshMap();

	//reset gui w trakcie gry
	static void RefreshGui();

	//wstawia gui w trakcie gry
	static void InitGui();

	static void Log(const char* text, int num);

	static void ClearLog();

	static void ShowDeathScreen();

	static void ShowOptions(int initialGameState);

	static void DrawLogo();

	
	//static void ShowShopMenu(shop* theShop);
	gameEngine()
	{
		GameState = 0;
		LogLevel = 0;
		TotalTurns = 0;
		CurrentLevel = 0;
		EnemiesKilled = 0;
		GameSaveLoad = 0;
	}
	


};


