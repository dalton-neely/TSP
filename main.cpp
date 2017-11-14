#include <iostream>
#include <string>
#include <fstream>

#include "cityClass.hpp"
#include "tourManager.hpp"
#include "tourClass.hpp"
#include "populationClass.hpp"
#include "geneticClass.hpp"

using namespace std;

void loadData(string _name, tourManager & _tour){
	ifstream in;
	in.open(_name, ifstream::in);
	int name, x, y, count;
	in >> count;
	for(int i = 0; i < count; i++){
		in >> name >> x >> y;
		cityClass temp(x, y, name);
		_tour.add(temp);
	}
}

int main(int argc, char **argv){
	tourManager tour;
	loadData("input.txt", tour);
	populationClass population(50, true, &tour);
	cout << "initial distance: " << population.getFittest().getDistance() << endl;
	geneticClass gentics(&tour);
	for(int i = 0; i < 250; i++){
		cout << "round: " << i + 1 << endl;
		population = gentics.evolve(population);
	}
	cout << "Fittest distance: " << population.getFittest().getDistance() << endl;
	population.getFittest().print();
	return 0;
}
