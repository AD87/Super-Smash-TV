#pragma once

template <class T>
struct Vec2{
	Vec2(){
		x = 0;
		y = 0;
	}
	Vec2(T _x, T _y){
		x = _x;
		y = _y;
	}

	Vec2& operator+=(Vec2 b)
	{
		*this = *this + b;
		return *this;
	}

	Vec2 operator-()const{
		return Vec2(-x,-y);
	}

	Vec2& operator-=(Vec2 b)
	{
		*this = *this - b;
		return *this;
	}

	template <class Scalar>
	Vec2& operator*=(Scalar s)
	{
		*this = *this *s;
		return *this;
	}

	T x;
	T y;
};

template <class T>
Vec2<T> operator+(const Vec2<T>& a, const Vec2<T>& b){
	return Vec2<T>(a.x + b.x, a.y + b.y);
}

template <class T>
Vec2<T> operator-(const Vec2<T>& a, const Vec2<T>& b){
	return Vec2<T>(a.x - b.x, a.y - b.y);
}

template <class T>
Vec2<T> operator*(const Vec2<T>& a, const Vec2<T>& b){
	return Vec2<T>(a.x * b.x, a.y * b.y);
}

template <class T, class scalar>
Vec2<T> operator*(const Vec2<T>& a, scalar s){
	return Vec2<T>(a.x * s, a.y * s);
}

template <class T, class scalar>
Vec2<T> operator*(scalar s, const Vec2<T>& a){
	return a*s;
}


typedef Vec2<int> Vec2i;
typedef Vec2<float> Vec2f;