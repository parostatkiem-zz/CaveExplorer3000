#pragma once
#include "config.h"

class mapObject
{
public:
	COORD position;
};

class character : public mapObject
{
public:
	int hp;
	int maxhp;
	int damage;
	int type=0;
};

class playerClass : public character
{
public:
	int level;
	int exp;
	int gold;

	int TryMove(char direction);
	void getKey();
	void RegenerateLife();
	void Death();
	void Atack();
	void PickGold();
};

class enemy : public character
{
public:
	//PODZIELIC RUCH NA ENEMY A PETLE RUCHU NA MAPE
	static void MoveEnemies();
};

class map
{
public:
	static void CheckRefresh();
	static void InitializeLevel(int level);
	static void AddCaveSegment(COORD punkt);
	static void PlacePlayer();
	static COORD GetOnScreenPos(COORD p);
	static void PlacePortal();
	static void CheckPortal();
};


