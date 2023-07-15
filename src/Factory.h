#pragma once
#include <string>
#include <cassert>
#include "Singleton.h"

template <class T>
class Factory: public Uncopyable{
public:
	Factory(){}
	friend Singleton<Factory>;
public:
	typedef T* (*FactoryFunc)();//typedef for the pointer to a function with the name FactoryFunc

	int add(const std::string& type, FactoryFunc ff){
		m_map[type] = ff;
		static int i = 0;
		i++;
		return i;
	}

	T* create(const std::string& type){
		auto it = m_map.find(type);
		if (it == m_map.end()) return nullptr;//key is not in the map
		FactoryFunc ff = it->second;
		assert(ff);
		T* go = ff();
		assert(go);
		return go;
	}

private:
	typedef std::map<std::string, FactoryFunc> FactoryMap;
	FactoryMap m_map;
};
