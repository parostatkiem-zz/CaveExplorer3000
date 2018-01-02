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

template <class type>
class cml
{
	std::fstream file;
public:
	container <type> data;

	//constructors
	cml(std::string path);
	type findKey(std::string request);
	void loadSection(std::string request);
	void loadKey(std::string request);

	//public methods
	bool good() const;
};

void wypisz(container<int>& con) {
	for (int i = 0; i < con.lenght; i++)
		std::cout << i << ": " << con.key[i] << " - " << con.value[i] << std::endl;
}

void test() {
	container<int> con1;
	con1.add("pierwszy", 1);
	con1.add("drugi", 2);
	wypisz(con1);
	con1.clearContainer();
	con1.add("pierwszy", 1);

	container<int> con2("pierwszy", 1);
	con2.add("drugi", 2);
	wypisz(con2);
	std::cout << con2.find("zwracaZeroczyli type()") << std::endl;

	system("pause");
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


//cml public construktor
template<class type>
inline cml<type>::cml(std::string path) {
	file.open(path, ios::in | ios::binary);
}

template<class type>
inline bool cml<type>::good() const {
	return file.good();
}
