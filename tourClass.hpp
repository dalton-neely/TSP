#ifndef TOURCLASS_HPP
#define TOURCLASS_HPP

#include <vector>
#include <cstdlib>
#include <chrono>

using namespace std;

class tourClass{
	private:
		vector<cityClass> tour;
		double fitness;
		int distance;
		tourManager *tourMan;
	public:
		tourClass(tourManager *);
		tourClass(vector<cityClass>, tourManager *);
		void generateIndividual();
		void generateInit();
		void shuffle(vector<cityClass> &);
		cityClass getCity(int);
		void setCity(int, cityClass);
		double getFitness();
		int getDistance();
		int tourSize();
		bool containsCity(cityClass);
		void print();
		int findIndexByName(int);
		bool equals(tourClass);
};

bool tourClass::equals(tourClass _tour){
	bool returnValue = true;
	for(int i = 0; i < tourSize(); i++){
		if(tour[i].getName() != _tour.getCity(i).getName() || tour[i].getX() != _tour.getCity(i).getX() || tour[i].getY() != _tour.getCity(i).getY())
			returnValue = false;
	}
	return returnValue;
}

int tourClass::findIndexByName(int _name){
	int foundIndex = -1;
	for(int i = 0; i < tourSize(); i++){
		if(tour[i].getName() == _name)
			foundIndex = i;
	}
	return foundIndex;
}

tourClass::tourClass(tourManager * _tourMan){
	tourMan = _tourMan;
	fitness = 0;
	distance = 0;
}

tourClass::tourClass(vector<cityClass> _tour, tourManager * _tourMan){
	tourMan = _tourMan;
	fitness = 0;
	distance = 0;
	tour = _tour;
}

void tourClass::generateIndividual(){
	for(int i = 0; i < tourMan->count(); i++)
		tour.push_back(tourMan->get(i));
	shuffle(tour);
}

void tourClass::generateInit(){
	cityClass temp(0,0,0);
	for(int i = 0; i < tourMan->count(); i++)
		tour.push_back(temp);
}

void tourClass::shuffle(vector<cityClass> & _tour){
	srand(chrono::system_clock::now().time_since_epoch().count());
	for(int i = 0; i < rand() % 100 + 75; i++){
		int swap1 = rand() % tourMan->count();
		int swap2 = rand() % tourMan->count();
		cityClass temp(_tour[swap1].getX(), _tour[swap1].getY(), _tour[swap1].getName());
		_tour[swap1].copy(_tour[swap2]);
		_tour[swap2].copy(temp);
	}
}

cityClass tourClass::getCity(int _position){
	return tour[_position];
}

void tourClass::setCity(int _position, cityClass _city){
	tour[_position].copy(_city);
	fitness = 0;
	distance = 0;
}

double tourClass::getFitness(){
	if(fitness == 0){
		fitness = 1/(double)getDistance();
	}
	return fitness;
}

int tourClass::getDistance(){
	if(distance == 0){
		int tourDistance = 0;
		for(int i = 0; i < tourMan->count(); i++){
			cityClass fromCity = getCity(i);
			cityClass destinationCity(0,0,0);
			if(i+1 < tourMan->count()){
				destinationCity = getCity(i+1);
			}else{
				destinationCity = getCity(0);
			}
			tourDistance += fromCity.distance(destinationCity);
		}
		distance = tourDistance;
	}
	return distance;
}

int tourClass::tourSize() {
	return tour.size();
}

bool tourClass::containsCity(cityClass _city){
	bool retVal = false;
	for(int i = 0; i < tourMan->count(); i++){
		if(tour[i].equals(_city)){
			//~ cout << "comparison" << endl;
			//~ tour[i].print();
			//~ _city.print();
			retVal = true;
		}
	}
	return retVal;
}

void tourClass::print(){
	for(int i = 0; i < tourSize(); i++){
		tour[i].print();
		cout << endl;
	}
	cout << endl;
}


#endif
