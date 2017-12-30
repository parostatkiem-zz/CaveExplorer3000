#pragma once
#include "config.h"
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
	//reset mapy podczas rozgrywki
	static void RefreshMap();

	//reset gui w trakcie gry
	static void RefreshGui();

	//wstawia gui w trakcie gry
	static void InitGui();

	static void Log(char* text, int num);

	static void ClearLog();

	static void ShowDeathScreen();

	static void ShowOptions(int initialGameState);

	static void DrawLogo();
};
