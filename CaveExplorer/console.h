#pragma once
#include <Windows.h>
// clasa obs³ugi konsoli
static class console {
public:

	// Ustawianie zadanego rozmiaru okna
	static void SetConsoleWindowSize(int x, int y);

	// Ustawienie odpowiednich parametrów konsoli
	static void initScreen(void);

	// Drukowanie znaku z na pozycji (x,y)
	static void putCharXY(int x, int y, unsigned char z);

	// Drukowanie ³añcucha s od pozycji (x,y)
	static void putStrXY(int x, int y, const char *s);

	// Zmiana kolorów w konsoli
	static void setColor(unsigned short id);

	// Pobieranie znaku z konsoli
	static char getKey(void);

	//Wypisanie tekstu w ramce
	static void drawMenuItem(int x, int y, unsigned short c, const char *s);

	static class shopGUI
	{
	public:
		static void showItemsMenu();
		//static void buyItem(int index);
		static void hideItemsMenu();
	};
};
