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
	unsigned int length;

	container();
	container(std::string ke, type va);
	~container();

	void add(std::string ke, type va);
	void clearContainer();
	type find(std::string requestValue);
	bool good() const;

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
	template<class t>
	t convertToType(std::string request);

public:
	container <type> data;

	//constructors
	cml(std::string path);
	~cml();

	//public methods
	void clearCml();
	bool good() const;
	bool goodFile() const;
	bool goodData() const;
	type findKey(std::string request);
	void loadSection(std::string request);
	void loadKey(std::string requestKey, std::string requestSection = "");
	void loadFile();
	static type readKey(std::string path, std::string requestKey, std::string requestSection = "");
	std::string givePath();
	void changeFile(std::string path);
};


//-------------------------------------Container-------------------------------------
//constructors
template<class type>
inline container<type>::container(){
	key = nullptr; value = nullptr; length = 0;
}

template<class type>
inline container<type>::container(std::string ke, type va){
	value = new type[1];
	key = new std::string[1];
	value[0] = va;
	key[0] = ke;
	length=1;
}

template<class type>
inline container<type>::~container(){
	if (length) {
		deleteIf(value);
		deleteIf(key);
		length = 0;
	}
}

//methods
template<class type>
inline void container<type>::add(std::string ke, type va){
	type* newValue = new type[length + 1];
	std::string* newKey = new std::string[length + 1];

	coppy<type>(value, newValue, length);
	coppy<std::string>(key, newKey, length);

	if (length) {
		deleteIf<std::string>(key);
		deleteIf<type>(value);
	}
	
	value = newValue; value[length] = va;
	key = newKey; key[length] = ke;
	length++;
}

template<class type>
inline void container<type>::clearContainer(){
	if (length) {
		deleteIf<type>(value);
		deleteIf<std::string>(key);
		length = NULL;
	}
}

template<class type>
inline type container<type>::find(std::string requestValue){
	for (int i = 0; i < length; i++) 
		if (requestValue == key[i]) return value[i];
	return type();
}

template<class type>
inline bool container<type>::good() const
{
	return (bool)length;
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
//constructors
template<class type>
inline cml<type>::cml(std::string path) {
	file.open(path, std::ios::in | std::ios::binary);
}

template<class type>
inline cml<type>::~cml(){
	clearCml();
}


//methods
template<class type>
inline type cml<type>::findKey(std::string request){
	return data.find(request);
}

template<class type>
inline void cml<type>::clearCml(){
	data.clearContainer();
	file.close();
}

template<class type>
inline bool cml<type>::good() const {
	return file.good();
}

template<class type>
inline bool cml<type>::goodFile() const
{
	return file.good();
}

template<class type>
inline bool cml<type>::goodData() const
{
	return data.good();
}

template<class type>
inline void cml<type>::loadSection(std::string request){
	if (!goodFile()) return;
	file.seekg(0);

	std::string line;
	std::string reqSec = "[" + request + "]";

	do {
		std::getline(file, line);
		if (file.eof()) return;
	} while (line.find(reqSec));

	do {
		

		std::getline(file, line);
		if (line[0] == '[') break;
		if (line[0] == '/' && line[1] == '/') continue;

		std::string keyBuf = "";
		std::string valBuf = ""; 
		int flag = 0;
		for (int i = 0; i < line.length(); i++) {

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
		line[4] == ']'
		));
	file.seekg(0);
}

template<class type>
inline void cml<type>::loadKey(std::string requestKey, std::string requestSection){
	if (!goodFile()) return;
	file.seekg(0);

	std::string line;
	std::string reqSec = "[" + requestSection + "]";

	if(reqSec != "[]")
		do {
			std::getline(file, line);
			if (file.eof()) return;
		} while (line.find(reqSec));
		
		do{
			std::getline(file, line);
			if (line[0] == '/' && line[1] == '/') continue;

			std::string keyBuf = "";
			std::string valBuf = "";
			int flag = 0;

			for (int i = 0; i < line.length(); i++) {
				if (line[i] == '<') flag = 1;
				else if (line[i] == '>')flag = 0;
				else if (flag == 1) keyBuf += line[i];

				if (line[i] == '\"' && flag == 2) flag = 0;
				else if (line[i] == '\"') flag = 2;
				else if (flag == 2) valBuf += line[i];
			}
			if (keyBuf == requestKey) {
				data.add(keyBuf, convertToType<type>(valBuf));
				break;
			}
		} while (!(
			line[0] == '[' &&
			line[1] == 'e' &&
			line[2] == 'n' &&
			line[3] == 'd' &&
			line[4] == ']'
			));

	file.seekg(0);
}

template<class type>
inline void cml<type>::loadFile(){
	if (!goodFile()) return;
	file.seekg(0);

	std::string line;

	do {
		std::getline(file, line);
		if (line[0] == '/' && line[1] == '/') continue;

		std::string keyBuf = "";
		std::string valBuf = "";
		int flag = 0;

		for (int i = 0; i < line.length(); i++) {
			if (line[i] == '<') flag = 1;
			else if (line[i] == '>')flag = 0;
			else if (flag == 1) keyBuf += line[i];

			if (line[i] == '\"' && flag == 2) flag = 0;
			else if (line[i] == '\"') flag = 2;
			else if (flag == 2) valBuf += line[i];
		}
		if (valBuf != "" || keyBuf != "")
			data.add(keyBuf, convertToType<type>(valBuf));
	} while (!(
		line[0] == '[' &&
		line[1] == 'e' &&
		line[2] == 'n' &&
		line[3] == 'd' &&
		line[4] == ']'
		));
	file.seekg(0);
}

template<class type>
inline type cml<type>::readKey(std::string path, std::string requestKey, std::string requestSection){
	cml <type>tmp(path);
	tmp.loadKey(requestKey, requestSection);
	return tmp.findKey(requestKey);
}

template<class type>
inline std::string cml<type>::givePath(){
	return path;
}

template<class type>
inline void cml<type>::changeFile(std::string path){
	file.close();
	file.open(path, path, std::ios::in | std::ios::binary)
}

template<class type>
template<class t>
inline t cml<type>::convertToType(std::string request){
	t turnType = 0.0;
	float multiplier = 1.0;
	int decimalFlag = 0;
	int negativeFlag = 0;
	bool dotFlag = false;

	for (int i = 0; i < request.length(); i++) {
		if (dotFlag) {
			decimalFlag++;
			multiplier /= 10.0;
		}
		else if (request[i] == '.') dotFlag = true;
		if (request[i] == '-')	negativeFlag++;
	}
	for (int i = request.length() - 1; i >= 0; i--) {
		if (request[i] == '.') decimalFlag--;
		else if (request[i] == '-') {
			negativeFlag--;
			turnType *= -1;
		}	
		else{
			turnType += (request[i] - 48) * multiplier;
			multiplier *= 10;
		}
	}
	return turnType;
}

template<>
template<>
inline char cml<char>::convertToType(std::string request){
	char turnType = 0;
	for (int i = request.length() - 1; i >= 0; i--)
		turnType += request[i];
	return turnType;
}

template<>
template<>
inline std::string cml<std::string>::convertToType(std::string request){
	return request;
}


