#pragma once
#include "config.h"

#include <fstream>
#include <string>

template <class type = std::string>
class container
{
public:
	std::string* key;
	type* value;
	unsigned int lenght;

	container();
	container(std::string ke, type va);
	~container();

	void add(std::string ke, type va);
	void clearContainer();
	type find(std::string requestValue);

private:
	template<class typeToDel>
	void deleteIf(typeToDel* variable);

	template<class typeToCp>
	void coppy(typeToCp* from, typeToCp* to, unsigned int howMany);
};

template <class type = std::string>
class cml
{
	std::fstream file;

	//private methods
	void clearContainer();

	template<typename t>
	t convertToType(std::string request);

	

public:
	container <type> data;

	//constructors
	cml(std::string path);

	//public methods
	bool good() const;
	type findKey(std::string request);
	void loadSection(std::string request);
	type readKey(std::string requestKey, std::string requestSection = NULL);
	void changeFile(std::string path);
};


//-------------------------------------Container-------------------------------------
template<class type>
inline container<type>::container(){
	key = nullptr; value = nullptr; lenght = 0;
}

template<class type>
inline container<type>::container(std::string ke, type va){
	value = new type[1];
	key = new std::string[1];
	value[0] = va;
	key[0] = ke;
	lenght=1;
}

template<class type>
inline container<type>::~container(){
	if (lenght) {
		deleteIf(value);
		deleteIf(key);
		lenght = 0;
	}
}

template<class type>
inline void container<type>::add(std::string ke, type va){
	type* newValue = new type[lenght + 1];
	std::string* newKey = new std::string[lenght + 1];

	coppy<type>(value, newValue, lenght);
	coppy<std::string>(key, newKey, lenght);

	if (lenght) {
		deleteIf<std::string>(key);
		deleteIf<type>(value);
	}
	
	value = newValue; value[lenght] = va;
	key = newKey; key[lenght] = ke;
	lenght++;
}

template<class type>
inline void container<type>::clearContainer(){
	deleteIf<type>(value);
	deleteIf<std::string>(key);
	lenght = NULL;
}

template<class type>
inline type container<type>::find(std::string requestValue){
	for (int i = 0; i < lenght; i++) 
		if (requestValue == key[i]) return value[i];
	return type();
}

template<class type>
template<class typeToDel>
inline void container<type>::deleteIf(typeToDel * variable){
	if (variable)
		delete[] variable;

}

template<class type>
template<class typeToCp>
inline void container<type>::coppy(typeToCp * from, typeToCp * to, unsigned int howMany){
	for (int i = 0; i < howMany; i++)
		to[i] = from[i];
}



//-------------------------------------cml------------------------------------- 
template<class type>
inline cml<type>::cml(std::string path) {
	file.open(path, std::ios::in | std::ios::binary);
}

template<class type>
inline bool cml<type>::good() const {
	return file.good();
}

template<class type>
inline void cml<type>::loadSection(std::string request){
	file.seekg(0);
	std::string line;
	std::string reqSec = "[" + request + "]";
	int i = 0;

	do {
		std::getline(file, line);
	} while (line.find(reqSec));

	do {
		

		std::getline(file, line);
		if (line[0] == '[') break;
		if (line[0] == '/' && line[1] == '/') continue;

		std::string keyBuf = "";
		std::string valBuf = ""; 
		int flag = 0;
		for (i = 0; i < line.length(); i++) {

			if (line[i] == '<') flag = 1;
			else if (line[i] == '>')flag = 0;
			else if (flag == 1) keyBuf += line[i];
			
			if (line[i] == '\"' && flag == 2) flag = 0;
			else if (line[i] == '\"') flag = 2;
			else if (flag == 2) valBuf += line[i];
		}
		data.add(keyBuf, convertToType<type>(valBuf));
	} while (!(
		line[0] == '[' &&
		line[1] == 'e' &&
		line[2] == 'n' &&
		line[3] == 'd' &&
		line[4] == '['
		));
}

template<class type>
inline type cml<type>::readKey(std::string requestKey, std::string requestSection)
{
	return type();
}

template<>
template<>
inline int cml<int>::convertToType(std::string request)
{
	int turnType = 0;
	int multiplier = 1;
	for (int i = request.length() - 1; i >= 0; i--) {
		if (request[i] == '-') {
			turnType *= -1;
			continue;
		}
		turnType += (request[i] - 48) * multiplier;
		multiplier *= 10;
	}

	return turnType;
}

template<>
template<>
inline std::string cml<std::string>::convertToType(std::string request)
{
	return request;
}


