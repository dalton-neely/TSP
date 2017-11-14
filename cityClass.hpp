#ifndef CITYCLASS_HPP
#define CITYCLASS_HPP

#include <cmath>
#include <iostream>
#include <string>

using namespace std;

class cityClass{
	private:
		int x,y,name;
	public:
		cityClass(int, int, int);
		void copy(cityClass);
		bool equals(cityClass);
		int getX();
		int getY();
		int getName();
		double distance(cityClass);
		void print();
};

cityClass::cityClass(int _x, int _y, int _name){
	x = _x;
	y = _y;
	name = _name;
}

void cityClass::copy(cityClass _city){
	x = _city.x;
	y = _city.y;
	name = _city.name;
}

bool cityClass::equals(cityClass _city){
	if(_city.getX() == x && _city.getY() == y && _city.getName() == name)
		return true;
	else
		return false;
}

int cityClass::getX(){
	return x;
}

int cityClass::getY(){
	return y;
}

int cityClass::getName(){
	return name;
}

double cityClass::distance(cityClass _city){
	return sqrt(pow((double)x - (double)_city.x, 2.00) + pow((double)y - (double)_city.y, 2.00));
}

void cityClass::print(){
	cout << name << ": [ " << x << " , " << y << " ]";
}

#endif

