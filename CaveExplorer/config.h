#pragma once
#include <windows.h> //do typu COORD
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "math.h"

#include <iostream>
#include <fstream>



#include "console.h"
#include "gameEngine.h"
#include "gameSave.h" 
#include "mapObjects.h"




// Wymiary planszy
#define MapMaxX 200
#define MapMaxY 200

// Wymiary viewporta
#define  ViewportW  80
#define  ViewportH	30 

//bloki
#define block_static 0xB2
#define block_normal 0xB1
#define block_normal_damaged 0xB0
#define block_empty ' '
#define block_player 0xF5
#define block_enemy 0xFE
#define block_item 0xCF
#define block_portal 0xDB



//tworzenie jaskiñ
#define CaveSize 49 //prawdopodobienstwo w % generacji sasiedniego segmentu jaskini (im wieksze, tym wieksze sa jaskinie)
#define MinCaveSize 10 //minimalna ilosc segmentow jednej jaskini 
#define CavesPerLevel 14 //ilosc jaskin na kazdy poziom - dostosowac do rozmiaru planszy!
#define DTETR 2 //min. dystans do krawedzi potrzebny do od˜wiezenia widoku - RACZEJ NIE ZMIENIAC

//generacja przeciwników
#define EnemyAmount 22 //ilosc przeciwnikow na lvl 0
#define EnemyMultiplier 1.5 //mnoznik zwiekszania si³ˆy oraz ilo˜ci przeciwnikow na kolejnym lvl
#define EnemyStartHp 20
#define EnemyStartDamage 4
#define MaxEnemyNum 100		//maksymalna przewidziana ilosc przeciwnikow (ustawiona na sztywno bo tak.)

//gracz, levele gracza i jego parametry
#define PlayerStartHp 50
#define PlayerStartDamage 7
#define ExpToNextLevel 10 //iloœæ EXP potrzebna do zdobycia nast. poziomu postaci
#define PlayerDamageMultiplier 1.3 //mnoznik zwiekszenia obrazen gracza na kazdy level
#define HPregenRate 8 //uzdrawia gracza o 1hp co X ruchów -> im mniejsza wartosc, tym szybciej ro˜œnie HP

//globalne ustawienia
#define MinDamageMultiplier 0.6 //mno¿lik minimalnych obra¿en wzglêdem pe³nych obra¿eñ
#define SeeDistance 6 //zasiêg wzroku przeciwników
#define Visibility 10 //zasiêg wzroku gracza | obecnie nieu¿ywany

//kolory
#define color_player 0x03
#define color_block_normal 0x08
#define color_block_static 0x0F
#define color_block_enemy 0x04
#define color_background 0x00 
#define color_portal 0x09

#define color_menu_active 0x0D
#define color_menu 0x05
#define color_logo 0x05

//scie¿ki do plików
#define language_path "Language\\"
#define language_extension ".cml"




extern mapObject viewport;
extern mapObject portal;
extern enemy enemies[MaxEnemyNum];
extern playerClass player;
extern gameEngine TheGameEngine;


extern unsigned int tmp;
extern unsigned int Turns;
extern int CaveSegments;
