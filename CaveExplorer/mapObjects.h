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
};

class playerClass : public character
{
public:
	int level;
	int exp;

	int TryMove(char direction);
	void Move();
	void RegenerateLife();
	void Death();
	void Atack();
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


