#pragma once

class Uncopyable{
protected:
	Uncopyable(){}
private:
	Uncopyable(const Uncopyable&);
	Uncopyable& operator=(const Uncopyable&);
};

template <class T>
class Singleton{
public:
	static T* Instance(){
		static T t;
		return &t;
	}
};