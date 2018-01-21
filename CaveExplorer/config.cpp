#include "config.h"

cml<std::string> gameConfig;
cml<std::string> menuLang;
cml<std::string> gameLang;
cml<std::string> languages;

//TUTAJ DODAJEMY WYPELNIANIE KONTENEROW I KLASS CML ZWIAZANYCH Z JEZYKIEM!
void config::loadLanguage(){
	//Wype³nianie kontenera, z tekstami w grze
	std::string langPath = gameConfig.findKey("Language_Path") + gameConfig.findKey("Language") + gameConfig.findKey("Language_Expansion");
	

	menuLang.clearCml();
	menuLang.changeFile(langPath);
	menuLang.loadSection("Menu");


	gameLang.clearCml();
	gameLang.changeFile(langPath);
	gameLang.loadSection("Game");
}

//TUTAJ DODAJEMY WYPELNIANIE KONTENEROW I KLASS CML ZWIAZANYCH Z CONFIGAMI!
bool config::loadMainConfig()
{
	

	std::string language_path = "Language\\";
	std::string config_extension = ".cml";

	//wczytywanie pliku config
	std::string path = "config" + config_extension;
	gameConfig.clearCml();
	gameConfig.changeFile(path);
	gameConfig.loadSection("Default");
	

	languages.clearCml();
	languages.changeFile(path);
	languages.loadSection("Languages");

	config::loadLanguage();
	
	//sprawdzanie poprawnosci
	
	if (!gameConfig.goodFile() ||
		!menuLang.goodFile() ||
		!gameLang.goodFile() ||
		!languages.goodFile() ) return false;
	
	//


	return true;
}

bool config::loadMainConfigWithLog()
{

	bool flag = loadMainConfig();// <- tutaj wywo³anie funkcji bez logów

	std::cout << std::endl << "Sciezka do pliku: " << gameConfig.getPath() << std::endl;
	gameConfig.data.showContainer();

	std::cout << std::endl << "Sciezka do pliku: " << languages.getPath() << std::endl;
	languages.data.showContainer();

	std::cout << std::endl << "Sciezka do pliku: " << menuLang.getPath() << std::endl;
	menuLang.data.showContainer();

	std::cout << std::endl << "Sciezka do pliku: " << gameLang.getPath() << std::endl;
	gameLang.data.showContainer();

	//system("pause");

	return flag;
}
