#pragma once
#include "config.h"

#include <fstream>
#include <string>

template <class type>
class container
{
public:
	std::string* key;
	type* value;
	unsigned int lenght;

	container();
	container(std::string ke, type va);

	void add(std::string ke, type va);

private:
	void deleteIf(type* toDel);
	void deleteIf(std::string* toDel);
	void coppy(type * from, type * to, unsigned int howMany);
	void coppy(std::string * from, std::string * to, unsigned int howMany);
};

template <class type>
class cml
{
	std::fstream file;
public:
	container <type> data;

	//constructors
	cml(std::string path);

	//public methods
	bool good() const;
};

void wypisz(container<int> con) {
	for (int i = 0; i < con.lenght; i++)
		std::cout << i << ": " << con.key[i] << " - " << con.value[i] << std::endl;
}

void test() {
	container<int> con1;
	con1.add("pierwszy", 1);
	con1.add("drugi", 2);
	wypisz(con1);

	container<int> con2("pierwszy", 1);
	con2.add("drugi", 2);
	wypisz(con2);

	system("pause");
}





//cml public construktor
template<class type>
inline cml<type>::cml(std::string path){
	file.open(path, ios::in);
}

template<class type>
inline bool cml<type>::good() const{
	return file.good();
}


//Container's public constructors
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
inline void container<type>::add(std::string ke, type va){
	type* newValue = new type[lenght + 1];
	std::string* newKey = new std::string[lenght + 1];

	coppy(value, newValue, lenght);
	coppy(key, newKey, lenght);

	deleteIf(value);
	deleteIf(key);

	value = newValue; value[lenght] = va;
	key = newKey; key[lenght] = ke;
	lenght++;
}

template<class type>
inline void container<type>::deleteIf(type * toDel){
	if (toDel) delete[]toDel;
}
template<class type>
inline void container<type>::deleteIf(std::string * toDel) {
	if (toDel) delete[]toDel;
}

template<class type>
inline void container<type>::coppy(type * from, type * to, unsigned int howMany){
	for (int i = 0; i < howMany; i++) 
		to[i] = from[i];
}
template<class type>
inline void container<type>::coppy(std::string * from, std::string * to, unsigned int howMany) {
	for (int i = 0; i < howMany; i++)
		to[i] = from[i];
}



