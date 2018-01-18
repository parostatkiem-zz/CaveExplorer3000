#include "config.h"



container<std::string> gameConfig;
cml<std::string> menuLang;
cml<std::string> gameLang;
cml<std::string> languages;


void config::loadLanguage(){
	//Wype³nianie kontenera, z tekstami w grze
	std::string langPath = gameConfig.find("Language_Path") + gameConfig.find("Language") + gameConfig.find("Language_Expansion");
	

	menuLang.clearCml();
	menuLang.changeFile(langPath);
	menuLang.loadSection("Menu");


	gameLang.clearCml();
	gameLang.changeFile(langPath);
	gameLang.loadSection("Game");
}

bool config::loadMainConfig()
{
	gameConfig.clearContainer();

	std::string language_path = "Language\\";
	std::string config_extension = ".cml";

	//wczytywanie pliku config
	std::string path = "config" + config_extension;
	std::cout << "config path: " << path << std::endl;
	cml<std::string> confFile(path);
	confFile.loadSection("Default");

	languages.clearCml();
	languages.changeFile(path);
	languages.loadSection("Languages");
	std::cout << std::endl << "Sciezka do pliku: " << languages.givePath() << std::endl;
	languages.data.showContainer();

	//kopiowanie configów co kontenera globalnego
	gameConfig.coppyContainer(confFile.data);
	gameConfig.showContainer();

	config::loadLanguage();

	std::cout << "Sciezka do pliku: " << menuLang.givePath() << std::endl;
	menuLang.data.showContainer();

	std::cout << std::endl << "Sciezka do pliku: " << gameLang.givePath() << std::endl;
	gameLang.data.showContainer();

	return true;
}
