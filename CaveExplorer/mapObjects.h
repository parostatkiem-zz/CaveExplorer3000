#pragma once
#include<iostream>
#include "config.h"
using namespace std;

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
	static void CheckShop();
	static void PlaceShop();

};

//class ShopItemType
//{
//public:
//	int value = 0;//0=weapon, 1= armor
//	string bonusUnit = "DMG"; 
//	string availableNames[3];
//	//mo¿na dodaæ wiêcej w przysz³oœci
//
//	ShopItemType(int _value, string _bonusUnit, string _names[3])
//	{
//		value = _value;
//		bonusUnit = _bonusUnit;
//		
//	}
//	ShopItemType()
//	{}
//};

class shopItem
{
public:
	string name = "";
	string bonusUnit = "";
	int type;

	int price = 0;
	int bonus = 0;
	
	shopItem(int _type, string _name, string _bonusUnit)
	{
		type = _type;
		name = _name;
		bonusUnit = _bonusUnit;
	}
	shopItem() {}
};

class shop : public mapObject
{
public:
	
	vector<int> alreadyBoughtTypes;
	vector<shopItem> items;

	void flushItems();

	shop();
	
	void fillShop();
	void buyItem(int index);
	
};

