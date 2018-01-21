#include "config.h"



void console::SetConsoleWindowSize(int x, int y) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	GetConsoleScreenBufferInfo(h, &bufferInfo);


	SMALL_RECT winInfo = bufferInfo.srWindow;
	COORD windowSize = { winInfo.Right - winInfo.Left + 1, winInfo.Bottom - winInfo.Top + 1 };

	if (windowSize.X > x || windowSize.Y > y)
	{
		// window size needs to be adjusted before the buffer size can be reduced.
		SMALL_RECT info =
		{
			0,
			0,
			x < windowSize.X ? x - 1 : windowSize.X - 1,
			y < windowSize.Y ? y - 1 : windowSize.Y - 1
		};

		SetConsoleWindowInfo(h, TRUE, &info);

	}

	COORD size = { x, y };
	SetConsoleScreenBufferSize(h, size);



	SMALL_RECT info = { 0, 0, x - 1, y - 1 };
	SetConsoleWindowInfo(h, TRUE, &info);

}

void console::initScreen(void) {



		HANDLE wh2 = GetStdHandle(STD_OUTPUT_HANDLE);





		system("Title CaveExplorer by Jan Sudczak/Filip Strózik"); //ustawianie tytu³u okna

																   //wy³¹czenie migania kursora
		CONSOLE_CURSOR_INFO cciInfo;
		cciInfo.dwSize = 1;
		cciInfo.bVisible = 0;
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cciInfo);

		//Ustawianie czcionki na Terminal 8x12
		CONSOLE_FONT_INFOEX info = { 0 };
		info.cbSize = sizeof(info);
		info.dwFontSize.X = 8;
		info.dwFontSize.Y = 12;
		info.FontWeight = FW_NORMAL;
		wcscpy_s(info.FaceName, L"Terminal");
		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);


		////ustawianie rozmiaru bufora okna
		COORD bufferSize = { 120, 31 };
		SetConsoleScreenBufferSize(wh2, bufferSize);

		//SMALL_RECT windowSize = { 0, 0, 120, 29 };
		//SetConsoleWindowInfo(wh2, 1, &windowSize);

		//ShowWindow(GetConsoleWindow(), SW_NORMAL);
		console::SetConsoleWindowSize(120, 31); //ustawianie rozmiaru ekranu


		system("chcp 852"); //na koniec kodowanie. Jest to raczej niepotrzebne, ale dam ¿eby by³o na wszelki wypadek :D
		system("cls");
	}

void console::putCharXY(int x, int y, unsigned char z){
	COORD a;
	a.X = x;
	a.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), a);
	printf("%c", z);
	a.X = 0;
	a.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), a);
}

void console::putStrXY(int x, int y, const char * s)
{
	while (*s)
		putCharXY(x++, y, *s++);
}

void console::setColor(unsigned short id)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), id);
}

char console::getKey(void)
{
	return _getch();
}

void console::drawMenuItem(int x, int y, unsigned short c, const char *s)
{

	setColor(c);
	const char *t = s;

	unsigned int num = 0;
	unsigned int i = 0;
	putCharXY(x, y, 0xC9);
	while (*t)
	{
		num++;
		*t++;
	}


	for (i = 1; i <= num + 3; i++)
	{
		putCharXY(x + i, y, 0xCD);

	}

	putCharXY(x + num + 3, y, 0xBB);

	putCharXY(x, y + 1, 0xBA);

	putCharXY(x + num + 3, y + 1, 0xBA);
	t = s;
	for (i = 2; i <= num + 1; i++)
	{
		putStrXY(x + i, y + 1, t);
		*t++;

	}
	setColor(c);
	for (i = 0; i <= num + 5; i++)
	{
		putCharXY(x + i - 1, y + 2, 0xCD);

	}



	setColor(0x0F);

}


void console::shopGUI::showItemsMenu()
{
	system("CLS");
	unsigned char menuIndex = 0;
	short colors[6] = { 0 };
	
	char buf2[256];
	unsigned char c;
	console::drawMenuItem(13, 1, color_block_gold, gameLang.findKey("Shop_Title").c_str()); 
	console::drawMenuItem(13+30, 1, color_block_static , gameLang.findKey("Shop_Stat").c_str()); 
	console::drawMenuItem(13 + 50, 1, color_block_static, gameLang.findKey("Shop_Price").c_str()); 
	do
	{
		for (int i = 0; i < theShop.items.capacity(); i++)
		{
			if (menuIndex == i)
			{
				colors[i] = color_menu_active;
			}
			else
			{
				colors[i] = color_menu;
			}


		}


		
		for (int i = 0; i < theShop.items.capacity(); i++)
		{
			console::drawMenuItem(17, 5+4*i, colors[i],theShop.items[i].name.c_str());
			snprintf(buf2, sizeof buf2, "%d %s", theShop.items[i].bonus, theShop.items[i].bonusUnit.c_str()); //nazwa
			console::drawMenuItem(17 + 25, 5 + 4 * i , colors[i],buf2); //staty
			snprintf(buf2, sizeof buf2, "%d", theShop.items[i].price);
			console::drawMenuItem(17 + 47, 5 + 4 * i, colors[i], buf2); //cena
		}

	



		//console::drawMenuItem(24, 17, colors[2], "Test2");



		c = console::getKey();


		if (c == 72) //gora
		{
			if (menuIndex > 0)
			{
				menuIndex--;
			}
		}

		if (c == 80)//dol
		{
			if (menuIndex < theShop.items.capacity()-1)
			{
				menuIndex++;
			}
		}
		if (c == 13)//enter
		{
			try //just in case
			{
				theShop.buyItem(menuIndex);
			}
			catch(exception ex) {};
			theShop.flushItems();
			break;

		}
		if (c == 27) //escape pressed
		{
			break;
		}




	} while (1);
	hideItemsMenu();
	return;
}

void console::shopGUI::hideItemsMenu()
{

//	system("CLS");
	
	gameEngine::InitGui();
	gameEngine::RefreshGui();

	gameEngine::RefreshMap();
}