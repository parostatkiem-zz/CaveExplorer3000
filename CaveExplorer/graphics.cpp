#include "config.h"


int lastI = 0;
char buf[256];

void RefreshMap()
{
	//system("CLS");
	//InitGui();
	//RefreshGui();
	ClearLog();

	if (GameState != 1)
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



			c = map[y][x];
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
	tmp.position = GetOnScreenPos(portal.position);
	if (tmp.position.X >= 0 && tmp.position.X <= ViewportW && tmp.position.Y >= 0 && tmp.position.Y <= ViewportH)
	{
		console::setColor(kolor_portal);
		console::putCharXY(portal.position.X - viewport.position.X, portal.position.Y - viewport.position.Y, blok_portal);
	}
	console::setColor(0x0F);
}

void RefreshGui()
{

	if (GameState != 1)
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

	snprintf(buf, sizeof buf, "%d", CurrentLevel + 1);
	console::putStrXY(ViewportW + 21, 6, buf); //cave deep


									  ///==========Portal=========


	float maxDist = sqrt(pow(MapMaxX, 2) + pow(MapMaxY, 2))*0.75;
	float dist = CalculateDistance(player.position, portal.position);
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

void InitGui()
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

void Log(char* text, int num)
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
	console::putStrXY(ViewportW + 1, ViewportH - 1 - LogLevel, buf);
	LogLevel++;
}

void ClearLog()
{
	LogLevel = 0;
	int i = 0;
	for (i = 9; i < ViewportH; i++)
	{
		console::putStrXY(ViewportW + 1, i, "                                      ");
	}
}

void ShowDeathScreen()
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
	snprintf(buf, sizeof buf, "Doszedˆe˜ do jaskini: ", CurrentLevel + 1);
	console::putStrXY(62, 3, buf);
	console::setColor(0xD0);
	snprintf(buf, sizeof buf, "%d", CurrentLevel + 1);
	console::putStrXY(62 + 23, 3, buf);

	console::setColor(kolor_menu_aktywny);

	snprintf(buf, sizeof buf, "Osi¥gn¥ˆe˜ poziom: %d", player.level);
	console::putStrXY(62, 5, buf);

	snprintf(buf, sizeof buf, "Zabiˆe˜ %d przeciwnik¢w", EnemiesKilled);
	console::putStrXY(62, 7, buf);

	snprintf(buf, sizeof buf, "Poruszˆe˜ si© %d razy", TotalTurns);
	console::putStrXY(62, 9, buf);

}

void ShowOptions(int initialGameState)
{
	system("cls");
	unsigned char menuIndex = 0;
	unsigned char c;


	if (GameSaveLoad)
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
				GameSaveLoad = 1;
				menuIndex++;
			}

		}

		if (c == 77)//prawo
		{
			if (menuIndex >0)
			{
				GameSaveLoad = 0;
				menuIndex--;

			}
		}

		if (c == 27) //escape pressed
		{
			GameState = initialGameState;
			system("CLS");

			return;
		}


	} while (1);
}

void DrawLogo()
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