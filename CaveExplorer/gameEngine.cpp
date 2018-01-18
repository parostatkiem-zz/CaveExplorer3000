#include "config.h"



unsigned int tmp;
unsigned int Turns;
int CaveSegments;


int mathem::CalculateDistance(COORD a, COORD b)
{
	return sqrt(pow((a.X - b.X), 2) + pow((a.Y - b.Y), 2));
}

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


void menu::ShowMenu()
{

	system("CLS");
	unsigned char menuIndex = 0;
	short colors[5] = { 0 };
	int i = 0;
	unsigned char c;
	gameEngine::DrawLogo();

	do
	{
		if (TheGameEngine.GameState != 0 && TheGameEngine.GameState != 1)
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
		if (TheGameEngine.GameState != 1 && !TheGameEngine.GameSaveLoad || !isSaved())
		{
			colors[1] = 0x08;
		}



		console::drawMenuItem(17, 7, colors[0], "Rozpocznij NOW¤ gr©");
		if (isSaved() && TheGameEngine.GameSaveLoad  &&  TheGameEngine.GameState == 0)
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

				TheGameEngine.GameState = 1;
				TheGameEngine.CurrentLevel = 0;
				Turns = 0;
				player.hp = PlayerStartHp; // 3 dla testow
				player.damage = PlayerStartDamage;
				player.maxhp = PlayerStartHp;
				player.exp = 0; //start exp
				player.level = 1;
				TheGameEngine.EnemiesKilled = 0;
				map::InitializeLevel(TheGameEngine.CurrentLevel);
				


				player.Move();

				return;
				break;
			case 1: //kontynuuj

				if (TheGameEngine.GameState == 1)
				{
					//gra sie toczy, zamknij menu
					system("CLS");
					gameEngine::RefreshMap();
					gameEngine::RefreshGui();
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
						TheGameEngine.GameState = 1;
						system("CLS");
						gameEngine::RefreshMap();
						gameEngine::RefreshGui();
						player.Move();
					}

				}




				break;

			case 2: //opcje
				tmp = TheGameEngine.GameState; //zapis obecnego TheGameEngine.GameState do tymczasowej zmiennej
				TheGameEngine.GameState = 2;
				gameEngine::ShowOptions(tmp);
				gameEngine::DrawLogo();  //ponowne wyœwietlenie grafiki logo
				break;

			case 3: //wyjdz

				if (TheGameEngine.area[0][0] == blok_staly && TheGameEngine.GameSaveLoad || !TheGameEngine.GameSaveLoad)
					saveGame(); //zapisanie gry na wyjsciu jesli wczytana jest jakas mapa lub zmieniono opcje
				exit(0);  //ostateczne wyjscie z programu
				break;
			}
		}

		if (c == 27) //escape pressed
		{
			if (TheGameEngine.GameState == 1)
			{
				gameEngine::RefreshMap(); //kontunuuj gre
				return;
			}
		}

	} while (1);
}


int lastI = 0;
char buf[256];

void gameEngine::RefreshMap()
{
	//system("CLS");
	//InitGui();
	//RefreshGui();
	ClearLog();

	if (TheGameEngine.GameState != 1)
		return;

	int x = 0;
	int y = 0;


	viewport.position.X = player.position.X - ViewportW / 2;
	viewport.position.Y = player.position.Y - ViewportH / 2;

	//InitGui();
	/*system("CLS");
	InitGui();
	RefreshGui();*/

	char c;
	mapObject tmp;
	for (y = viewport.position.Y; y < viewport.position.Y + ViewportH; y++)
	{
		for (x = viewport.position.X; x < viewport.position.X + ViewportW; x++)
		{
			tmp.position.X = x - ViewportH / 2;
			tmp.position.Y = y;



			c = TheGameEngine.area[y][x];
			if (x < 0 || x >= MapMaxX || y < 0 || y >= MapMaxY)
			{
				console::setColor(kolor_tlo);
				printf(" ");
				console::setColor(0x0F);
				continue;
			}



			switch (c)
			{
			case (char)blok_gracz:
				console::setColor(kolor_gracz);
				break;

			case (char)(blok_zwykly) :
				console::setColor(kolor_blok_zwykly);
				break;
			case (char)(blok_zwykly_ukruszony) :
				console::setColor(kolor_blok_zwykly);
				break;

			case (char)blok_przeciwnik:
				console::setColor(kolor_blok_przeciwnik);
				break;

			case (char)blok_staly:
				console::setColor(kolor_blok_staly);
				break;
			}
			//if (CalculateDistance(player,tmp)<=Visibility)
			printf("%c", c);

			console::setColor(0x0F);

		}
		printf("\n");
	}
	console::setColor(kolor_gracz);
	console::putCharXY(player.position.X - viewport.position.X, player.position.Y - viewport.position.Y, blok_gracz);


	//czy portal jest w zasiegu mapy
	tmp.position = map::GetOnScreenPos(portal.position);
	if (tmp.position.X >= 0 && tmp.position.X <= ViewportW && tmp.position.Y >= 0 && tmp.position.Y <= ViewportH)
	{
		console::setColor(kolor_portal);
		console::putCharXY(portal.position.X - viewport.position.X, portal.position.Y - viewport.position.Y, blok_portal);
	}
	console::setColor(0x0F);
}

void gameEngine::RefreshGui()
{

	if (TheGameEngine.GameState != 1)
		return;
	int hpPercent = player.hp * 15 / player.maxhp;
	int i;





	///==========HP=========

	console::setColor(0x0c);
	char c = 178;
	for (int i = 1; i <= 15; i++)
	{

		if (i > hpPercent)
		{
			console::setColor(0x08);
			c = 176;
		}

		console::putCharXY(ViewportW + 6 + i, 1, c);
	}

	console::setColor(0x0c);

	snprintf(buf, sizeof buf, "%d ", player.hp);
	console::putStrXY(ViewportW + 6 + 15 + 2, 1, buf);  //current level number

														///==========LVL=========
	int lvlPercent = player.exp * 15 / ExpToNextLevel;


	console::setColor(0x0A);
	c = 178;
	for (int i = 1; i <= 15; i++)
	{

		if (i > lvlPercent)
		{
			console::setColor(0x08);
			c = 176;
		}

		console::putCharXY(ViewportW + 6 + i, 3, c);
	}
	console::setColor(0x0A);

	snprintf(buf, sizeof buf, "%d", player.level);
	console::putStrXY(ViewportW + 7, 4, buf);  //current level number
	console::setColor(0x08);


	snprintf(buf, sizeof buf, "%d", player.level + 1);
	console::putStrXY(ViewportW + 7 + 15 - 1, 4, buf); //next level number



	console::setColor(0xD0);
	snprintf(buf, sizeof buf, "%d - %d", (int)(player.damage * MinDamageMultiplier), player.damage);
	console::putStrXY(ViewportW + 7, 6, buf); //player min and max damage number

	snprintf(buf, sizeof buf, "%d", TheGameEngine.CurrentLevel + 1);
	console::putStrXY(ViewportW + 21, 6, buf); //cave deep


											   ///==========Portal=========


	float maxDist = sqrt(pow(MapMaxX, 2) + pow(MapMaxY, 2))*0.75;
	float dist = mathem::CalculateDistance(player.position, portal.position);
	float tmp = (float)(dist / maxDist);
	float val = tmp * 12;

	console::setColor(0x08);
	c = 176;
	for (int i = 1; i <= 12; i++)
	{

		if (i > val)
		{
			console::setColor(kolor_portal);

			c = 178;
		}

		console::putCharXY(ViewportW + 10 + 12 - i, 8, c);
	}










}

void gameEngine::InitGui()
{
	console::setColor(0x04);
	console::putStrXY(ViewportW + 2, 1, "HP:");

	console::setColor(0x02);
	console::putStrXY(ViewportW + 2, 3, "LVL:");

	console::setColor(0x05);
	console::putStrXY(ViewportW + 2, 6, "DMG:"); console::putStrXY(ViewportW + 15, 6, "CAVE:");

	console::setColor(0x09);
	console::putStrXY(ViewportW + 2, 8, "Portal:");
}

void gameEngine::Log(char* text, int num)
{



	//	putStrXY(ViewportW + 7, 4, buf);  //current level number


	if (num <0)
	{
		//gracz przyjal obrazenia
		console::setColor(0x04);
		snprintf(buf, sizeof buf, "%s: %d", text, -num);
	}
	else if (num > 0)
	{
		//gracz zadal obrazenia
		console::setColor(0x0A);
		snprintf(buf, sizeof buf, "%s: %d", text, num);

	}
	else
	{
		//inna wiadomosc
		console::setColor(0x08);
		snprintf(buf, sizeof buf, "%s", text);
	}
	console::putStrXY(ViewportW + 1, ViewportH - 1 - TheGameEngine.LogLevel, buf);
	TheGameEngine.LogLevel++;
}

void gameEngine::ClearLog()
{
	TheGameEngine.LogLevel = 0;
	int i = 0;
	for (i = 9; i < ViewportH; i++)
	{
		console::putStrXY(ViewportW + 1, i, "                                      ");
	}
}

void gameEngine::ShowDeathScreen()
{
	system("cls");
	console::setColor(kolor_logo);
	printf("                                     ____\n");
	printf("                              __,---'     `--.__\n");
	printf("                           ,-'                ; `.\n");
	printf("                          ,'                  `--.`--.\n");
	printf("                         ,'                       `._ `-.\n");
	printf("                         ;                     ;     `-- ;\n");
	printf("                       ,-'-_       _,-~~-.      ,--      `.\n");
	printf("                       ;;   `-,;    ,'~`.__    ,;;;    ;  ;\n");
	printf("                       ;;    ;,'  ,;;      `,  ;;;     `. ;\n");
	printf("                       `:   ,'    `:;     __/  `.;      ; ;\n");
	printf("                        ;~~^.   `.   `---'~~    ;;      ; ;\n");
	printf("                        `,' `.   `.            .;;;     ;'\n");
	printf("                        ,',^. `.  `._    __    `:;     ,'\n");
	printf("                        `-' `--'    ~`--'~~`--.  ~    ,'\n");
	printf("                       /;`-;_ ; ;. /. /   ; ~~`-.     ;\n");
	printf("-._                   ; ;  ; `,;`-;__;---;      `----'\n");
	printf("   `--.__             ``-`-;__;:  ;  ;__;\n");
	printf(" ...     `--.__                `-- `-'\n");
	printf("`--.:::...     `--.__                ____\n");
	printf("    `--:::::--.      `--.__    __,--'    `.\n");
	printf("        `--:::`;....       `--'       ___  `.\n");
	printf("            `--`-:::...     __           )  ;\n");
	printf("                  ~`-:::...   `---.      ( ,'\n");
	printf("                      ~`-:::::::::`--.   `-.\n");
	printf("                          ~`-::::::::`.    ;\n");
	printf("                              ~`--:::,'   ,'\n");
	printf("                                   ~~`--'~\n");


	//przezyles xxx itd.

	console::setColor(kolor_menu_aktywny);
	snprintf(buf, sizeof buf, "Doszedˆe˜ do jaskini: ", TheGameEngine.CurrentLevel + 1);
	console::putStrXY(62, 3, buf);
	console::setColor(0xD0);
	snprintf(buf, sizeof buf, "%d", TheGameEngine.CurrentLevel + 1);
	console::putStrXY(62 + 23, 3, buf);

	console::setColor(kolor_menu_aktywny);

	snprintf(buf, sizeof buf, "Osi¥gn¥ˆe˜ poziom: %d", player.level);
	console::putStrXY(62, 5, buf);

	snprintf(buf, sizeof buf, "Zabiˆe˜ %d przeciwnik¢w", TheGameEngine.EnemiesKilled);
	console::putStrXY(62, 7, buf);

	snprintf(buf, sizeof buf, "Poruszˆe˜ si© %d razy", TheGameEngine.TotalTurns);
	console::putStrXY(62, 9, buf);

}

void gameEngine::ShowOptions(int initialGameState)
{
	system("cls");
	unsigned char menuIndex = 0;
	unsigned char c;


	if (TheGameEngine.GameSaveLoad)
		menuIndex = 1;
	else
		menuIndex = 0;


	do
	{


		console::drawMenuItem(16, 12, kolor_menu, "Obsˆuga zapisu i wczytywania gry");
		if (menuIndex == 1)
			console::drawMenuItem(16 + 37, 12, 0x0A, "TAK"); //lewo
		else
			console::drawMenuItem(16 + 37, 12, 0x0A, "NIE"); //prawo



		c = console::getKey();


		if (c == 75) //lewo
		{
			if (menuIndex < (2 - 1))
			{
				TheGameEngine.GameSaveLoad = 1;
				menuIndex++;
			}

		}

		if (c == 77)//prawo
		{
			if (menuIndex >0)
			{
				TheGameEngine.GameSaveLoad = 0;
				menuIndex--;

			}
		}

		if (c == 27) //escape pressed
		{
			TheGameEngine.GameState = initialGameState;
			system("CLS");

			return;
		}


	} while (1);
}

void gameEngine::DrawLogo()
{
	console::setColor(kolor_logo);


	console::putStrXY(1, 0, "_________                    ___________             .__              ");
	console::putStrXY(1, 1, "\\_   ___ \\_____ ___  __ ____ \\_   _____/__  ________ |  |   ___________  ___________ ");
	console::putStrXY(1, 2, "/    \\  \\/\\__  \\\\  \\/ // __ \\ |    __)_\\  \\/  |____ \\|  |  /  _ \\_  __ \\/ __ \\_  __ \\");
	console::putStrXY(1, 3, "\\     \\____/ __ \\\\   /\\  ___/ |        \\>    <|  |_> >  |_(  <_> )  | \\|  ___/|  | \\/");
	console::putStrXY(1, 4, " \\______  (____  /\\_/  \\___  >_______  /__/\\_ \\   __/|____/\\____/|__|   \\___  >__|   ");
	console::putStrXY(1, 5, "        \\/     \\/          \\/        \\/      \\/__|                          \\/       ");


	console::setColor(0x08);
	console::putStrXY(60, 20, "by  Jan Sudczak & Filip Strozik");
	console::setColor(0x0F);
}

