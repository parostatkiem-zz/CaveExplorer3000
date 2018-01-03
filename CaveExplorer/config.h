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
#define blok_staly 0xB2
#define blok_zwykly 0xB1
#define blok_zwykly_ukruszony 0xB0
#define blok_pusty ' '
#define blok_gracz 0xF5
#define blok_przeciwnik 0xFE
#define blok_item 0xCF
#define blok_portal 0xDB



//tworzenie jaski�
#define CaveSize 49 //prawdopodobienstwo w % generacji sasiedniego segmentu jaskini (im wieksze, tym wieksze sa jaskinie)
#define MinCaveSize 10 //minimalna ilosc segmentow jednej jaskini 
#define CavesPerLevel 14 //ilosc jaskin na kazdy poziom - dostosowac do rozmiaru planszy!
#define DTETR 2 //min. dystans do krawedzi potrzebny do od�wiezenia widoku - RACZEJ NIE ZMIENIAC

//generacja przeciwnik�w
#define EnemyAmount 22 //ilosc przeciwnikow na lvl 0
#define EnemyMultiplier 1.5 //mnoznik zwiekszania si��y oraz ilo�ci przeciwnikow na kolejnym lvl
#define EnemyStartHp 20
#define EnemyStartDamage 4
#define MaxEnemyNum 100		//maksymalna przewidziana ilosc przeciwnikow (ustawiona na sztywno bo tak.)

//gracz, levele gracza i jego parametry
#define PlayerStartHp 50
#define PlayerStartDamage 7
#define ExpToNextLevel 10 //ilo�� EXP potrzebna do zdobycia nast. poziomu postaci
#define PlayerDamageMultiplier 1.3 //mnoznik zwiekszenia obrazen gracza na kazdy level
#define HPregenRate 8 //uzdrawia gracza o 1hp co X ruch�w -> im mniejsza wartosc, tym szybciej ro��nie HP

//globalne ustawienia
#define MinDamageMultiplier 0.6 //mno�lik minimalnych obra�en wzgl�dem pe�nych obra�e�
#define SeeDistance 6 //zasi�g wzroku przeciwnik�w
#define Visibility 10 //zasi�g wzroku gracza | obecnie nieu�ywany

//kolory
#define kolor_gracz 0x03
#define kolor_blok_zwykly 0x08
#define kolor_blok_staly 0x0F
#define kolor_blok_przeciwnik 0x04
#define kolor_tlo 0x00 
#define kolor_portal 0x09

#define kolor_menu_aktywny 0x0D
#define kolor_menu 0x05
#define kolor_logo 0x05

//scie�ki do plik�w
#define language_path "Language\\"


//globalna definicja zmiennych
extern unsigned char area[200][200];
extern unsigned int GameState;
extern unsigned int LogLevel;
extern unsigned int TotalTurns;
extern unsigned int CurrentLevel;
extern unsigned int EnemiesKilled;

extern unsigned int GameSaveLoad;

extern mapObject viewport;
extern mapObject portal;
extern enemy enemies[MaxEnemyNum];
extern playerClass player;


extern unsigned int tmp;
extern unsigned int Turns;
extern int CaveSegments;
