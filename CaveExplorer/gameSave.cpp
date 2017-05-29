#include "config.h"



using namespace std;

ofstream file;

FILE *plik;
char* nazwa=new char[256];
char* docdir = getenv("USERPROFILE");

unsigned int x = 0, y = 0;

int saveGame()
{


	if (!docdir)
		return 0; //nie udalo sie odczytac katalogu dokumenty
	string path(docdir);
	path += "\\Documents\\CaveExplorer";

	


	string filename = "\\savegame.txt";

	file.open(path + filename);
	if (!file.is_open())
	{
		string tmp = "mkdir "+path;
		system(tmp.c_str()); //tworzenie katalogu, bo nie istnieje

		tmp = "del " + path+filename;
		system(tmp.c_str()); //usuwanie starego pliku, bo inaczej ofstream sobie nie radzi³
		file.open(path + filename);
	}

	if (!file.is_open())
	{
		return 0; //nie udalo sie otworzyc pliku nawet po utworzeniu katalogu - coœ posz³o nie tak
	}

	

	if (!GameSaveLoad) //trzeba sapisac do pliku informacje, ze obsluga zapisu/odczytu jest wylaczona
	{
		file<<"gameSaveLoad=0\n";
		file.close();
		return 1;
	}




	

	//=========FAKTYCZNY ZAPIS DO PLIKU==============


	file<<"gameSaveLoad=1\n";

	string tmp;
	for (int x = 0; x <= MapMaxY; x++)
				{
					
				for (int y = 0; y < MapMaxX; y++)
					tmp += map[x][y];
				}
	file << "map=" << tmp.c_str();
	file<< "\n";
	file<<"totalTurns="<< TotalTurns<<"\n";
	file<<"currentLevel="<< CurrentLevel<<"\n";
	file<<"enemiesKilled="<< EnemiesKilled<<"\n";
	file<<"player="<< player.position.X<<","<< player.position.Y << "," << player.damage << "," << player.exp << "," << player.hp << "," << player.level << "," << player.maxhp << ",\n";
	file<<"enemies=";
	for (int x = 0; x < 100; x++)
	{
		if (enemies[x].position.X == 0 && enemies[x].position.Y == 0)
			continue; //koniec petli jesli  przeciwnik nie istnieje

		file<<enemies[x].position.X<<","<< enemies[x].position.Y << "," << enemies[x].damage << "," << enemies[x].hp<<"|";
	}
	file<<"\n";
	file<<"portal="<<portal.X<<","<< portal.Y;
	file.close();
	return 1;
}

int loadGame()
{
	if (!isSaved)
		return 0; //nie da sie odczytac  pliku zapisu


	if (!docdir)
		return 0; //nie udalo sie odczytac katalogu dokumenty
	char *path=docdir;



	sprintf(nazwa, "%s\\%s", docdir, "Documents\\CaveExplorer");

	sprintf(nazwa,  "%s\\%s", nazwa, "savegame.txt");

	plik = fopen(nazwa, "r");
	if (plik == NULL)
		return 0;
	const size_t line_size = 41000;
	const size_t zmienna_size = 50;
	char* line=new char[line_size];

	char tmp[50] = { 0 };
	int i = 0;
	int n = 0;
	int k = 0;
	char* zmienna= new char[zmienna_size];
	struct Enemy e; //tymczasowa zmienna przeciwnika
	e.position.X = 0;
	e.position.Y = 0;

	while (fgets(line, line_size, plik) != NULL)
	{

		if (line[0] == '=')
			break;
		i = 0;
		do
		{
			zmienna[i] = line[0];
			i++;
			*line++;
		} while (line[0] != '=');
		zmienna[i] = '\0';

		*line++; //wywalanie znaku = z wartosci



		i = 0;
		do
		{
			i++;
		} while (line[i] != '\n');
		line[i] = '\0';//usuniecie znaku nowej linii z konca zmiennej



		if (strcmp(zmienna, "gameSaveLoad") == 0)
		{
			GameSaveLoad = (unsigned int)line;
			if (!GameSaveLoad)
				return 0; //wczytywanie jest wylaczone
		}




		if (strcmp(zmienna, "map") == 0)
		{
			for (int x = 0; x <= MapMaxY; x++)
			{
			memcpy(map[x], (unsigned char*)line, MapMaxX); // OK
				for (int y = 0; y<MapMaxX; y++)
					*line++;
			}
		}




		if (strcmp(zmienna, "currentLevel") == 0)
		{
			CurrentLevel = atoi(line);

		}

		if (strcmp(zmienna, "totalTurns") == 0)
		{
			TotalTurns = atoi(line);

		}

		if (strcmp(zmienna, "enemiesKilled") == 0)
		{
			EnemiesKilled = atoi(line);

		}

		if (strcmp(zmienna, "player") == 0)
		{
			for (x = 0; x < 50; x++)
				tmp[x] = 0;
			n = 0;
			i = 0;
			while (line[0] != '\0')
			{
				if (line[0] == ',')
				{
					i = 0;
					*line++;

					switch (n)
					{
					case 0: //pierwsza liczba w ciagu
						player.position.X = atoi(tmp);
						break;
					case 1:
						player.position.Y = atoi(tmp);
						break;
					case 2:
						player.damage = atoi(tmp);
						break;
					case 3:
						player.exp = atoi(tmp);
						break;
					case 4:
						player.hp = atoi(tmp);
						break;
					case 5:
						player.level = atoi(tmp);
						break;
					case 6:
						player.maxhp = atoi(tmp);
						break;

					}


					for (x = 0; x < 50; x++)
						tmp[x] = 0;
					n++;
				}
				tmp[i] = line[0];
				*line++;
				i++;
			}

		}

		if (strcmp(zmienna, "portal") == 0)
		{
			for (x = 0; x < 50; x++)
				tmp[x] = 0;
			n = 0;
			i = 0;
			while (line[0] != '\0')
			{
				if (line[0] == ',')
				{
					i = 0;
					*line++;

					switch (n)
					{
					case 0: //pierwsza liczba w ciagu
						portal.X = atoi(tmp);
						break;
					case 1:
						portal.Y = atoi(tmp);
						continue;
						break;


					}


					for (x = 0; x < 50; x++)
						tmp[x] = 0;
					n++;
				}
				tmp[i] = line[0];
				*line++;
				i++;
			}

		}

		if (strcmp(zmienna, "enemies") == 0)
		{

			for (i = 0; i < MaxEnemyNum; i++) //czyszczenie tablicy przeciwnikow
			{
				enemies[i] = e; //resetowanie pozycji kazdego przeciwnika na (0,0) - oznacza to,ze nie on istnieje
			}


			for (x = 0; x < 50; x++)
				tmp[x] = 0;
			n = 0;
			i = 0;
			while (line[0] != '\0')
			{
				if (line[0] == '|')
				{
					*line++;
					e.hp = atoi(tmp);
					enemies[k] = e;
					k++;
					i = 0;
					n = 0;
					continue;
				}

				if (line[0] == ',')
				{
					i = 0;
					*line++;

					switch (n)
					{
					case 0: //pierwsza liczba w ciagu 
						e.position.X = atoi(tmp);
						break;
					case 1:
						e.position.Y = atoi(tmp);
						break;
					case 2:
						e.damage = atoi(tmp);
						break;
					case 3:

						break;

					}


					for (x = 0; x < 50; x++)
						tmp[x] = 0;
					n++;
				}
				tmp[i] = line[0];
				*line++;
				i++;
			}

		}

	}
	

	fclose(plik);

	return 1;
}

int loadGameSaveVariable(unsigned int checkForGameSaveVariable)
{


	if (!docdir)
		return 0; //nie udalo sie odczytac katalogu dokumenty
	char *path = docdir;
	//path += "\\Documents\\CaveExplorer";


	sprintf(nazwa, "%s\\%s", docdir, "Documents\\CaveExplorer");

	sprintf(nazwa, "%s\\%s", nazwa, "savegame.txt");

	plik = fopen(nazwa, "r");
	if (plik == NULL)
	{
		if (checkForGameSaveVariable)		
			GameSaveLoad = 1; //ustawianie zmiennej na domyœl¹ wartoœæ
		return 0;
	}
	const size_t line_size = 41000;
	const size_t zmienna_size = 50;
	char* line = new char[line_size];


	unsigned char tmp[50] = { 0 };
	int i = 0;

	fgets(line, line_size, plik);


	if (checkForGameSaveVariable)
	{
		if (line[13] == '1')
			GameSaveLoad = 1;
		else
			GameSaveLoad = 0;
	}



	return 1;



}

int isSaved()
{

	if (loadGameSaveVariable(0) == 0)
		return 0;
	else
		return 1;

}

