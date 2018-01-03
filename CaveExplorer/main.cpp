//CAVE EXPLORER 
#include "config.h"
#include "confStaff.h"

unsigned char area[200][200];
unsigned int GameState = 0;
unsigned int LogLevel = 0;
unsigned int TotalTurns = 0;
unsigned int CurrentLevel = 0;
unsigned int EnemiesKilled = 0;

unsigned int GameSaveLoad = 1;

playerClass player;
mapObject viewport;
mapObject portal;
enemy enemies[MaxEnemyNum] ;

template<class type>
void wypisz(container<type>& con) {
	for (int i = 0; i < con.lenght; i++)
		std::cout << i << ": " << con.key[i] << " - " << con.value[i] << std::endl;
}

void test() {
	//==========container
	container<int> con1;
	con1.add("pierwszy", 1);
	con1.add("drugi", 2);
	wypisz(con1);
	con1.clearContainer();
	con1.add("pierwszy", 1);
	

	container<int> con2("pierwszy", 1);
	con2.add("drugi", 2);
	wypisz(con2);
	std::cout << con2.find("drugi") << std::endl;
	std::cout << con2.find("zwracaZeroczyli type()") << std::endl;

	container<std::string> con3("pierwszy", "jeden");
	wypisz(con3);

	//===========cml
	cml<std::string> cml1("C:\\Users\\filip\\Documents\\CaveExplorer\\Language\\pl.txt");
	cml1.loadSection("pierwszyDzial");
	wypisz(cml1.data);

	cml<int> cml2("C:\\Users\\filip\\Documents\\CaveExplorer\\Language\\pl.txt");
	cml2.loadSection("drugiDzial");
	wypisz(cml2.data);

	std::cout << cml2.find("wiersz3") << std::endl;

	system("pause");
}


int main()
{

	test();

	
	console::initScreen();



	loadGameSaveVariable(1);



	menu::ShowMenu();


	system("PAUSE");
	return 0;
}