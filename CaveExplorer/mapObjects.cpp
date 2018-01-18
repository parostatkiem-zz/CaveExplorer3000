#include "config.h"



void enemy::MoveEnemies()
{
	int i;
	int xDist = 0;
	int yDist = 0;
	for (i = 0; i < MaxEnemyNum; i++) //petla po wszystkich przeciwnikach
	{
		if (enemies[i].position.X == 0 && enemies[i].position.Y == 0)
			continue; //koniec petli jesli przeciwnik nie istnieje

		int tmp = mathem::CalculateDistance(enemies[i].position, player.position);
		if (mathem::CalculateDistance(enemies[i].position, player.position) <= SeeDistance) //jesli przeciwnik widzi gracza
		{
			console::setColor(kolor_blok_przeciwnik);
			if (mathem::CalculateDistance(enemies[i].position, player.position) <= 1) //przeciwnik stoi kolo gracza
			{
				//przeciwnik atakuje
				int obrazenia = mathem::RandomInt(MinDamageMultiplier*enemies[i].damage, enemies[i].damage);
				if (player.hp - obrazenia > 0)
				{
					player.hp -= obrazenia; //gracz otrzymuje cios
					gameEngine::Log("Otrzyma�e� obra�enia", -obrazenia);
				}
				else
					player.Death();   //gracz umiera

			}
			else //przeciwnik idzie w kierunku gracza
			{
				xDist = enemies[i].position.X - player.position.X;
				yDist = enemies[i].position.Y - player.position.Y;
				if (abs(xDist) > abs(yDist)) //przeciwnik porusza si� w osi poziomej
				{
					if (xDist > 0) //w lewo
					{
						if (TheGameEngine.area[enemies[i].position.Y][enemies[i].position.X - 1] == blok_pusty || TheGameEngine.area[enemies[i].position.Y][enemies[i].position.X - 1] == blok_gracz)
						{
							//moze sie normalnie poruszyc w wyznaczonym kierunku
							enemies[i].position.X--;
							console::putCharXY(map::GetOnScreenPos(enemies[i].position).X, map::GetOnScreenPos(enemies[i].position).Y, blok_przeciwnik);
							console::putCharXY(map::GetOnScreenPos(enemies[i].position).X + 1, map::GetOnScreenPos(enemies[i].position).Y, blok_pusty);
							TheGameEngine.area[enemies[i].position.Y][enemies[i].position.X + 1] = blok_pusty;
						}
						else
						{
							if (yDist > 0) //w gore
							{
								if (TheGameEngine.area[enemies[i].position.Y - 1][enemies[i].position.X] == blok_pusty || TheGameEngine.area[enemies[i].position.Y - 1][enemies[i].position.X] == blok_gracz)
								{
									//nie moze sie normalnie poruszyc, wiec rusza wedlug innej osi
									enemies[i].position.Y--;
									console::putCharXY(map::GetOnScreenPos(enemies[i].position).X, map::GetOnScreenPos(enemies[i].position).Y, blok_przeciwnik);
									console::putCharXY(map::GetOnScreenPos(enemies[i].position).X, map::GetOnScreenPos(enemies[i].position).Y + 1, blok_pusty);
									TheGameEngine.area[enemies[i].position.Y + 1][enemies[i].position.X] = blok_pusty;
								}
							}
							else //w dol
							{
								if (TheGameEngine.area[enemies[i].position.Y + 1][enemies[i].position.X] == blok_pusty || TheGameEngine.area[enemies[i].position.Y + 1][enemies[i].position.X] == blok_pusty)
								{
									//nie moze sie normalnie poruszyc, wiec rusza wedlug innej osi
									enemies[i].position.Y++;
									console::putCharXY(map::GetOnScreenPos(enemies[i].position).X, map::GetOnScreenPos(enemies[i].position).Y, blok_przeciwnik);
									console::putCharXY(map::GetOnScreenPos(enemies[i].position).X, map::GetOnScreenPos(enemies[i].position).Y - 1, blok_pusty);
									TheGameEngine.area[enemies[i].position.Y - 1][enemies[i].position.X] = blok_pusty;
								}
							}
						}
					}
					else //w prawo
					{
						if (TheGameEngine.area[enemies[i].position.Y][enemies[i].position.X + 1] == blok_pusty || TheGameEngine.area[enemies[i].position.Y][enemies[i].position.X + 1] == blok_gracz)
						{
							//moze sie normalnie poruszyc w wyznaczonym kierunku
							enemies[i].position.X++;
							console::putCharXY(map::GetOnScreenPos(enemies[i].position).X, map::GetOnScreenPos(enemies[i].position).Y, blok_przeciwnik);
							console::putCharXY(map::GetOnScreenPos(enemies[i].position).X - 1, map::GetOnScreenPos(enemies[i].position).Y, blok_pusty);
							TheGameEngine.area[enemies[i].position.Y][enemies[i].position.X - 1] = blok_pusty;
						}
						else
						{
							if (yDist > 0) //w gore
							{
								if (TheGameEngine.area[enemies[i].position.Y - 1][enemies[i].position.X] == blok_pusty || TheGameEngine.area[enemies[i].position.Y - 1][enemies[i].position.X] == blok_gracz)
								{
									//nie moze sie normalnie poruszyc, wiec rusza wedlug innej osi
									enemies[i].position.Y--;
									console::putCharXY(map::GetOnScreenPos(enemies[i].position).X, map::GetOnScreenPos(enemies[i].position).Y, blok_przeciwnik);
									console::putCharXY(map::GetOnScreenPos(enemies[i].position).X, map::GetOnScreenPos(enemies[i].position).Y + 1, blok_pusty);
									TheGameEngine.area[enemies[i].position.Y + 1][enemies[i].position.X] = blok_pusty;
								}
							}
							else //w dol
							{
								if (TheGameEngine.area[enemies[i].position.Y + 1][enemies[i].position.X] == blok_pusty || TheGameEngine.area[enemies[i].position.Y + 1][enemies[i].position.X] == blok_pusty)
								{
									//nie moze sie normalnie poruszyc, wiec rusza wedlug innej osi
									enemies[i].position.Y++;
									console::putCharXY(map::GetOnScreenPos(enemies[i].position).X, map::GetOnScreenPos(enemies[i].position).Y, blok_przeciwnik);
									console::putCharXY(map::GetOnScreenPos(enemies[i].position).X, map::GetOnScreenPos(enemies[i].position).Y - 1, blok_pusty);
									TheGameEngine.area[enemies[i].position.Y - 1][enemies[i].position.X] = blok_pusty;
								}
							}
						}
					}
				}
				else //przeciwnik porusza sie w osi pionowej
				{
					if (yDist > 0) //w gore
					{
						if (TheGameEngine.area[enemies[i].position.Y - 1][enemies[i].position.X] == blok_pusty || TheGameEngine.area[enemies[i].position.Y - 1][enemies[i].position.X] == blok_gracz)
						{
							//moze sie normalnie poruszyc w wyznaczonym kierunku
							enemies[i].position.Y--;
							console::putCharXY(map::GetOnScreenPos(enemies[i].position).X, map::GetOnScreenPos(enemies[i].position).Y, blok_przeciwnik);
							console::putCharXY(map::GetOnScreenPos(enemies[i].position).X, map::GetOnScreenPos(enemies[i].position).Y + 1, blok_pusty);
							TheGameEngine.area[enemies[i].position.Y + 1][enemies[i].position.X] = blok_pusty;
						}
						else
						{
							if (xDist > 0) //w lewo
							{
								if (TheGameEngine.area[enemies[i].position.Y][enemies[i].position.X - 1] == blok_pusty || TheGameEngine.area[enemies[i].position.Y][enemies[i].position.X - 1] == blok_gracz)
								{
									//nie moze sie normalnie poruszyc, wiec rusza wedlug innej osi
									enemies[i].position.X--;
									console::putCharXY(map::GetOnScreenPos(enemies[i].position).X, map::GetOnScreenPos(enemies[i].position).Y, blok_przeciwnik);
									console::putCharXY(map::GetOnScreenPos(enemies[i].position).X + 1, map::GetOnScreenPos(enemies[i].position).Y, blok_pusty);
									TheGameEngine.area[enemies[i].position.Y][enemies[i].position.X + 1] = blok_pusty;
								}

							}
							else //w prawo
							{
								if (TheGameEngine.area[enemies[i].position.Y][enemies[i].position.X + 1] == blok_pusty || TheGameEngine.area[enemies[i].position.Y][enemies[i].position.X + 1] == blok_gracz)
								{
									//nie moze sie normalnie poruszyc, wiec rusza wedlug innej osi
									enemies[i].position.X++;
									console::putCharXY(map::GetOnScreenPos(enemies[i].position).X, map::GetOnScreenPos(enemies[i].position).Y, blok_przeciwnik);
									console::putCharXY(map::GetOnScreenPos(enemies[i].position).X - 1, map::GetOnScreenPos(enemies[i].position).Y, blok_pusty);
									TheGameEngine.area[enemies[i].position.Y][enemies[i].position.X - 1] = blok_pusty;
								}

							}
						}
					}
					else //w dol
					{
						if (TheGameEngine.area[enemies[i].position.Y + 1][enemies[i].position.X] == blok_pusty || TheGameEngine.area[enemies[i].position.Y + 1][enemies[i].position.X] == blok_pusty)
						{
							//moze sie normalnie poruszyc w wyznaczonym kierunku
							enemies[i].position.Y++;
							console::putCharXY(map::GetOnScreenPos(enemies[i].position).X, map::GetOnScreenPos(enemies[i].position).Y, blok_przeciwnik);
							console::putCharXY(map::GetOnScreenPos(enemies[i].position).X, map::GetOnScreenPos(enemies[i].position).Y - 1, blok_pusty);
							TheGameEngine.area[enemies[i].position.Y - 1][enemies[i].position.X] = blok_pusty;
						}
						else
						{
							if (xDist > 0) //w lewo
							{
								if (TheGameEngine.area[enemies[i].position.Y][enemies[i].position.X - 1] == blok_pusty || TheGameEngine.area[enemies[i].position.Y][enemies[i].position.X - 1] == blok_gracz)
								{
									//nie moze sie normalnie poruszyc, wiec rusza wedlug innej osi
									enemies[i].position.X--;
									console::putCharXY(map::GetOnScreenPos(enemies[i].position).X, map::GetOnScreenPos(enemies[i].position).Y, blok_przeciwnik);
									console::putCharXY(map::GetOnScreenPos(enemies[i].position).X + 1, map::GetOnScreenPos(enemies[i].position).Y, blok_pusty);
									TheGameEngine.area[enemies[i].position.Y][enemies[i].position.X + 1] = blok_pusty;
								}

							}
							else //w prawo
							{
								if (TheGameEngine.area[enemies[i].position.Y][enemies[i].position.X + 1] == blok_pusty || TheGameEngine.area[enemies[i].position.Y][enemies[i].position.X + 1] == blok_gracz)
								{
									//nie moze sie normalnie poruszyc, wiec rusza wedlug innej osi
									enemies[i].position.X++;
									console::putCharXY(map::GetOnScreenPos(enemies[i].position).X, map::GetOnScreenPos(enemies[i].position).Y, blok_przeciwnik);
									console::putCharXY(map::GetOnScreenPos(enemies[i].position).X - 1, map::GetOnScreenPos(enemies[i].position).Y, blok_pusty);
									TheGameEngine.area[enemies[i].position.Y][enemies[i].position.X - 1] = blok_pusty;
								}

							}
						}
					}
				}
			}
			//koniec ruchu
			TheGameEngine.area[enemies[i].position.Y][enemies[i].position.X] = blok_przeciwnik;

			console::setColor(0x0F);

		}
	}
}

//DO GRACZA
int playerClass::TryMove(char direction)
{
	COORD tmp = player.position;
	console::setColor(kolor_gracz);
	switch (direction)
	{
	case 72: //gora
		if (TheGameEngine.area[player.position.Y - 1][player.position.X] == blok_pusty || TheGameEngine.area[player.position.Y - 1][player.position.X] == blok_zwykly || TheGameEngine.area[player.position.Y - 1][player.position.X] == blok_zwykly_ukruszony)
		{
			TheGameEngine.TotalTurns++;
			Turns++;
			if (TheGameEngine.area[player.position.Y - 1][player.position.X] == blok_zwykly)
			{
				//nalezy ukruszyc blok
				console::setColor(kolor_blok_zwykly);
				console::putCharXY(player.position.X - viewport.position.X, player.position.Y - viewport.position.Y - 1, blok_zwykly_ukruszony);
				TheGameEngine.area[player.position.Y - 1][player.position.X] = blok_zwykly_ukruszony;
			}
			else
			{
				//blok juz jest ukruszony, mozna go zniszczyc i sie tam przemiescic LUB pole jest puste
				player.position.Y--;
				console::putCharXY(player.position.X - viewport.position.X, player.position.Y - viewport.position.Y, blok_gracz);
				console::putCharXY(player.position.X - viewport.position.X, player.position.Y - viewport.position.Y + 1, blok_pusty);
			}
		}
		break;
	case 80:  //dol
		if (TheGameEngine.area[player.position.Y + 1][player.position.X] == blok_pusty || TheGameEngine.area[player.position.Y + 1][player.position.X] == blok_zwykly || TheGameEngine.area[player.position.Y + 1][player.position.X] == blok_zwykly_ukruszony)
		{
			TheGameEngine.TotalTurns++;
			Turns++;
			if (TheGameEngine.area[player.position.Y + 1][player.position.X] == blok_zwykly)
			{
				//nalezy ukruszyc blok
				console::setColor(kolor_blok_zwykly);
				console::putCharXY(player.position.X - viewport.position.X, player.position.Y - viewport.position.Y + 1, blok_zwykly_ukruszony);
				TheGameEngine.area[player.position.Y + 1][player.position.X] = blok_zwykly_ukruszony;
			}
			else
			{
				player.position.Y++;
				console::putCharXY(player.position.X - viewport.position.X, player.position.Y - viewport.position.Y, blok_gracz);
				console::putCharXY(player.position.X - viewport.position.X, player.position.Y - viewport.position.Y - 1, blok_pusty);
			}
		}
		break;
	case 77: //prawo
		if (TheGameEngine.area[player.position.Y][player.position.X + 1] == blok_pusty || TheGameEngine.area[player.position.Y][player.position.X + 1] == blok_zwykly || TheGameEngine.area[player.position.Y][player.position.X + 1] == blok_zwykly_ukruszony)
		{
			TheGameEngine.TotalTurns++;
			Turns++;
			if (TheGameEngine.area[player.position.Y][player.position.X + 1] == blok_zwykly)
			{
				//nalezy ukruszyc blok
				console::setColor(kolor_blok_zwykly);
				console::putCharXY(player.position.X - viewport.position.X + 1, player.position.Y - viewport.position.Y, blok_zwykly_ukruszony);
				TheGameEngine.area[player.position.Y][player.position.X + 1] = blok_zwykly_ukruszony;
			}
			else
			{
				player.position.X++;
				console::putCharXY(player.position.X - viewport.position.X, player.position.Y - viewport.position.Y, blok_gracz);
				console::putCharXY(player.position.X - viewport.position.X - 1, player.position.Y - viewport.position.Y, blok_pusty);
			}
		}
		break;
	case 75: //lewo
		if (TheGameEngine.area[player.position.Y][player.position.X - 1] == blok_pusty || TheGameEngine.area[player.position.Y][player.position.X - 1] == blok_zwykly || TheGameEngine.area[player.position.Y][player.position.X - 1] == blok_zwykly_ukruszony)
		{
			TheGameEngine.TotalTurns++;
			Turns++;
			if (TheGameEngine.area[player.position.Y][player.position.X - 1] == blok_zwykly)
			{
				//nalezy ukruszyc blok
				console::setColor(kolor_blok_zwykly);
				console::putCharXY(player.position.X - viewport.position.X - 1, player.position.Y - viewport.position.Y, blok_zwykly_ukruszony);
				TheGameEngine.area[player.position.Y][player.position.X - 1] = blok_zwykly_ukruszony;
			}
			else
			{
				player.position.X--;
				console::putCharXY(player.position.X - viewport.position.X, player.position.Y - viewport.position.Y, blok_gracz);
				console::putCharXY(player.position.X - viewport.position.X + 1, player.position.Y - viewport.position.Y, blok_pusty);
			}

		}
		break;
	}

	TheGameEngine.area[player.position.Y][player.position.X] = blok_pusty;

	console::setColor(0x0F);

	return 1;
}

//NAZWA TROCH� Z�A, DA�BYM COS W STYLU WAITFORKEY I DO KLASY GRACZA
void playerClass::getKey()
{

	unsigned char inputChar;
	do
	{
		inputChar = console::getKey();
		if (inputChar == 0 || inputChar == 0xE0)
			inputChar = console::getKey();  //'czyszczenie' znaku ze �mieci je�li jest enterem albo czym� takim

		if (inputChar == 72 || inputChar == 80 || inputChar == 77 || inputChar == 75)
		{
			if (TheGameEngine.GameState == 1)
			{
				gameEngine::ClearLog();
				RegenerateLife();
				player.TryMove(inputChar);
				map::CheckPortal();
				enemy::MoveEnemies();
				map::CheckRefresh();
				gameEngine::RefreshGui();
			}

		}
		if (inputChar == 27) //escape pressed
		{
			menu::ShowMenu();
		}

		if (inputChar == 32) //space pressed
		{
			if (TheGameEngine.GameState == 1)
			{
				gameEngine::ClearLog();
				RegenerateLife();
				Atack();
			}
		}




	} while (1);


}

//MAPa
void map::CheckRefresh()
{
	if (player.position.X - viewport.position.X <= DTETR
		|| player.position.X - viewport.position.X >= ViewportW - DTETR
		|| player.position.Y - viewport.position.Y <= DTETR
		|| player.position.Y - viewport.position.Y >= ViewportH - DTETR)
	{

		gameEngine::RefreshMap();

	}
}

//MAPA
void map::InitializeLevel(int level)
{
	system("CLS");
	srand(time(NULL));
	int x = 0;
	int y = 0;




	for (x = 0; x < MapMaxX; x++)
	{
		for (y = 0; y < MapMaxY; y++)
		{
			if (x == 0 || x == MapMaxX - 1 || y == 0 || y == MapMaxY - 1)
				TheGameEngine.area[y][x] = blok_staly; //otaczanie mapy nierozbijalnymi blokami
			else
				TheGameEngine.area[y][x] = blok_zwykly; // wypelnianie mapy blokami do rozwalenia
		}
	}

	//generowanie jaskin
	int i = 0;
	for (i = 0; i <= CavesPerLevel; i++)
	{
		CaveSegments = 0;
		COORD tmp;
		tmp.X = mathem:: RandomInt(1, MapMaxX - 1);
		tmp.Y = mathem::RandomInt(1, MapMaxX - 1);
		//map[tmp.X][tmp.Y] = blok_pusty;
		AddCaveSegment(tmp);

	}

	//generowanie przeciwnikow===================
	struct enemy e;
	e.position.X = 0;
	e.position.Y = 0;
	for (i = 0; i < MaxEnemyNum; i++) //czyszczenie tablicy przeciwnikow
	{
		enemies[i] = e; //resetowanie pozycji kazdego przeciwnika na (0,0) - oznacza to,ze on nie  istnieje
	}


	e.damage = EnemyStartDamage + (EnemyMultiplier*level);
	e.hp = EnemyStartHp + (EnemyMultiplier*level);
	for (i = 0; i < EnemyAmount + (EnemyMultiplier*level) - 2; i++)
	{
		int a = EnemyAmount + (EnemyMultiplier*level);
		COORD tmp;
		tmp.X = mathem::RandomInt(1, MapMaxX - 1);
		tmp.Y = mathem::RandomInt(1, MapMaxX - 1);

		if (TheGameEngine.area[tmp.Y][tmp.X] == blok_pusty)
		{
			COORD tmp2;
			tmp2.X = tmp.Y;
			tmp2.Y = tmp.X;
			e.position = tmp;
			//wylosowana pozycja jest pusta. Stawianie przeciwnika
			enemies[i] = e;
			TheGameEngine.area[tmp.Y][tmp.X] = blok_przeciwnik;
		}
		else
			i--;

	}


	//ustawianie gracza
	PlacePlayer();

	PlacePortal();

	gameEngine::RefreshMap();
	gameEngine::InitGui();
	gameEngine::RefreshGui();



}

// DO MAPU
void map::AddCaveSegment(COORD point)
{
	int a = mathem::RandomInt(0, 100);
	unsigned char b = TheGameEngine.area[point.Y][point.X];
	unsigned char c = blok_zwykly;


	if (b == blok_zwykly && a<CaveSize || CaveSegments<MinCaveSize && b == blok_zwykly)
	{
		CaveSegments++;
		TheGameEngine.area[point.Y][point.X] = blok_pusty;


		//generowanie segmentow dla sasiednich 4 pol
		COORD tmp;
		tmp.X = point.X + 1;
		tmp.Y = point.Y;
		AddCaveSegment(tmp);

		tmp.X = point.X;
		tmp.Y = point.Y + 1;
		AddCaveSegment(tmp);

		tmp.X = point.X - 1;
		tmp.Y = point.Y;
		AddCaveSegment(tmp);

		tmp.X = point.X;
		tmp.Y = point.Y - 1;
		AddCaveSegment(tmp);
	}
}

//DO MAPU
void map::PlacePlayer()
{
	mapObject tmp;
	tmp.position.X = mathem::RandomInt(1, MapMaxX - 1);
	tmp.position.Y = mathem::RandomInt(1, MapMaxY - 1);

	unsigned char b = TheGameEngine.area[tmp.position.Y][tmp.position.X];
	unsigned char c = blok_pusty;

	if (b == c)
	{
		//map[tmp.X][tmp.Y] = blok_gracz;
		player.position = tmp.position;

		return;
	}
	else
	{
		PlacePlayer();
	}

}

//DO MAPU
COORD map::GetOnScreenPos(COORD p)
{
	COORD out;
	out.X = p.X - viewport.position.X;
	out.Y = p.Y - viewport.position.Y;
	return out;
}

//DO MAPY
void map::PlacePortal()
{
	mapObject tmp;
	tmp.position.X = mathem::RandomInt(2, MapMaxX - 1);
	tmp.position.Y = mathem::RandomInt(2, MapMaxY - 1);

	unsigned char b = TheGameEngine.area[tmp.position.Y][tmp.position.X];
	unsigned char c = blok_pusty;

	if (b == c)
	{
		//map[tmp.X][tmp.Y] = blok_gracz;
		portal.position = tmp.position;

		return;
	}
	else
	{
		PlacePortal();
	}

}

//GRACZ
void playerClass::Atack()
{
	int i = 0;
	for (int i = 0; i<MaxEnemyNum; i++)  //petla po wszystkich przeciwnikach
	{
		if (enemies[i].position.X == 0 && enemies[i].position.Y == 0)
			continue;    //pominiecie przeciwnika jesli nie istnieje

		int tmp = mathem::CalculateDistance(enemies[i].position, player.position);
		int s = mathem::CalculateDistance(enemies[i].position, player.position);
		if (mathem::CalculateDistance(enemies[i].position, player.position) <= 1) //jestli gracz jest obok przeciwnika
		{
			TheGameEngine.TotalTurns++;
			Turns++;
			int obrazenia = mathem::RandomInt(MinDamageMultiplier*player.damage, player.damage);


			gameEngine::Log("Zadane obra�enia", obrazenia);
			if (enemies[i].hp <= obrazenia)//cios zabija przeciwnika
			{
				TheGameEngine.EnemiesKilled++;
				COORD tmp = map::GetOnScreenPos(enemies[i].position);

				console::putCharXY(tmp.X, tmp.Y, blok_pusty); //usuniecie przeciwnika z widoku

															  //usuniecie przeciwnika z mapy
				TheGameEngine.area[enemies[i].position.Y][enemies[i].position.X] = blok_pusty;
				enemies[i].position.X = 0;
				enemies[i].position.Y = 0;//ustawienie przeciwnika jako niezywego


				gameEngine::Log("Zabi�e� przeciwnika!", 0);


				if (player.exp >= ExpToNextLevel)
				{
					//gracz awansuje na nowy level
					player.level++;

					player.exp = -1;

					player.damage *= PlayerDamageMultiplier;

					gameEngine::Log("Awansowa�e� na wy�szy poziom!!", 0);


				}

				player.exp++;
				gameEngine::RefreshGui();
			}
			else //cios tylko uszkadza przeciwnika
			{
				enemies[i].hp -= obrazenia;

			}


			enemy::MoveEnemies();
			gameEngine::RefreshGui();
		}
	}

}

//DO GRACZA
void playerClass::Death()
{
	TheGameEngine.GameState = 0;

	gameEngine::ShowDeathScreen();

}

//GRACZ
void playerClass::RegenerateLife()
{
	if (Turns >= HPregenRate)
	{
		Turns = 0;
		if (player.hp<PlayerStartHp)
			player.hp++;
	}
	else
		Turns++;
}

//DO Mapu
void map::CheckPortal() //sprawdza, czy gracz nie  wszedl w portal
{
	if (player.position.X == portal.position.X && player.position.Y == portal.position.Y)
	{
		map::InitializeLevel(++TheGameEngine.CurrentLevel);
	}
}