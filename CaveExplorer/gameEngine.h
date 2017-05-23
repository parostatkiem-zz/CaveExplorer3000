#pragma once
#include "config.h"
#include "time.h"



int RandomInt(int min, int max);
COORD GetOnScreenPos(COORD p);
int CalculateDistance(COORD a, COORD b);
void PlacePlayer();
void MoveEnemies();
void AddCaveSegment(COORD punkt);
void InitializeLevel(int level);
void Move();
int TryMove(char direction);
void ShowMenu();
void Atack();
void Death();
void RegenerateLife();
void PlacePortal();
void CheckPortal();