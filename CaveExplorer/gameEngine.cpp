#include "config.h"



unsigned int tmp;
unsigned int Turns;
int CaveSegments;



//DO MAPU??
int mathem::CalculateDistance(COORD a, COORD b)
{
	return sqrt(pow((a.X - b.X), 2) + pow((a.Y - b.Y), 2));
}

//STATYCZNE ALE RACZEJ DO KLASY MAPY
int mathem::RandomInt(int min, int max)
{
	int r;
	const unsigned int range = 1 + max - min;
	const unsigned int buckets = RAND_MAX / range;
	const unsigned int limit = buckets * range;


	do
	{
		r = rand();
	} while (r >= limit);

	return min + (r / buckets);
}



//DO MENU
void menu::ShowMenu()
{

	system("CLS");
	unsigned char menuIndex = 0;
	short colors[5] = { 0 };
	int i = 0;
	unsigned char c;
	DrawLogo();

	do
	{
		if (GameState != 0 && GameState != 1)
			return;
		for (i = 0; i < 5; i++)
		{
			if (menuIndex == i)
			{
				colors[i] = kolor_menu_aktywny;
			}
			else
			{
				colors[i] = kolor_menu;
			}


		}
		if (GameState != 1 && !GameSaveLoad || !isSaved())
		{
			colors[1] = 0x08;
		}



		console::drawMenuItem(17, 7, colors[0], "Rozpocznij NOW¤ gr©");
		if (isSaved() && GameSaveLoad  &&  GameState == 0)
		{


			console::drawMenuItem(16, 12, colors[1], "Kontynuuj zapisan¥ gr©");
		}
		else
		{


			console::drawMenuItem(22, 12, colors[1], "Kontynuuj");
		}



		console::drawMenuItem(24, 17, colors[2], "Opcje");

		console::drawMenuItem(21, 22, colors[3], "Zakoäcz gr©");



		c = console::getKey();


		if (c == 72) //gora
		{
			if (menuIndex >0)
			{
				menuIndex--;
			}
		}

		if (c == 80)//dol
		{
			if (menuIndex < (4 - 1))
			{
				menuIndex++;
			}
		}




		if (c == 13)//enter
		{
			switch (menuIndex)
			{
			case 0: //nowa gra

				system("CLS");

				GameState = 1;
				CurrentLevel = 0;
				Turns = 0;
				player.hp = PlayerStartHp; // 3 dla testow
				player.damage = PlayerStartDamage;
				player.maxhp = PlayerStartHp;
				player.exp = 0; //start exp
				player.level = 1;
				EnemiesKilled = 0;
				map::InitializeLevel(CurrentLevel);
				


				player.Move();

				return;
				break;
			case 1: //kontynuuj

				if (GameState == 1)
				{
					//gra sie toczy, zamknij menu
					system("CLS");
					RefreshMap();
					RefreshGui();
					return;
				}
				else
				{
					//wczytaj gre
					if (isSaved())
					{
						if (!loadGame())
						{
							system("CLS");
							console::drawMenuItem(25, 13, kolor_blok_przeciwnik, "Uuups, cos poszlo nie tak :( Nie udalo sie zaladowac gry"); //error
							system("pause");
							system("CLS");
							break;
						}
						GameState = 1;
						system("CLS");
						RefreshMap();
						RefreshGui();
						player.Move();
					}

				}




				break;

			case 2: //opcje
				tmp = GameState; //zapis obecnego GameState do tymczasowej zmiennej
				GameState = 2;
				ShowOptions(tmp);
				DrawLogo();  //ponowne wyœwietlenie grafiki logo
				break;

			case 3: //wyjdz

				if (area[0][0] == blok_staly && GameSaveLoad || !GameSaveLoad)
					saveGame(); //zapisanie gry na wyjsciu jesli wczytana jest jakas mapa lub zmieniono opcje
				exit(0);  //ostateczne wyjscie z programu
				break;
			}
		}

		if (c == 27) //escape pressed
		{
			if (GameState == 1)
			{
				RefreshMap(); //kontunuuj gre
				return;
			}
		}

	} while (1);
}


