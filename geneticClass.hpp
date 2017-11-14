#ifndef GENETIC_CLASS_HPP
#define GENETIC_CLASS_HPP

using namespace std;

class geneticClass{
	public:
		int mutationRate;
		int turnamentSize;
		bool elitetism;
		geneticClass(tourManager *);
		populationClass evolve(populationClass);
		tourManager * tour;
		tourClass crossover(tourClass, tourClass);
		void mutate(tourClass &);
		tourClass turnamentSelection(populationClass);
};

geneticClass::geneticClass(tourManager * tourMan){
	mutationRate = 5;
	turnamentSize = 5;
	elitetism = true;
	tour = tourMan;
}

populationClass geneticClass::evolve(populationClass _population){
	int elitetismOffset = 0;
	populationClass temp(_population.populationSize(), true, tour); 
	
	if(elitetism){
		temp.saveIndividual(0, _population.getFittest());
		elitetismOffset = 1;
	}
	
	for(int i = elitetismOffset; i < _population.populationSize(); i++){
		tourClass parent1 = turnamentSelection(_population);
		//~ parent1.print();
		tourClass parent2 = turnamentSelection(_population);
		while(parent1.equals(parent2)){
			parent2 = turnamentSelection(_population);
		}
		//~ cout << "they differ" << endl;
		//~ cout << "%%%%%%%" << endl;
		//~ parent2.print();
		
		//~ cout << "before crossover" << endl;
		tourClass child(tour);
		child.generateInit();
		child = crossover(parent1, parent2);
		//~ cout << "passed crossover" << endl;
		//~ child.print();
		temp.saveIndividual(i, child);
	}
	
	
	for(int i = elitetismOffset; i < _population.populationSize(); i++){
		tourClass tempTour = temp.getIndividual(i);
		mutate(tempTour);
	}
	
	//~ cout << "passed mutation" << endl;
	
	return temp;
}

tourClass geneticClass::crossover(tourClass _a, tourClass _b){
	tourClass child(tour);
	child.generateInit();
	
	int start = rand() % _a.tourSize();
	//~ cout << "tourSize: " << _a.tourSize() << endl;
	
	int end = rand() % _a.tourSize();
	if(end <= start){
		int temp = start;
		start = end;
		end = temp;
	}
	//~ cout << "start: " << start << endl;
	//~ cout << "end: " << end << endl;
	for(int i = start; i < end; i++){
		child.setCity(i, _a.getCity(i));
	}
	//~ _a.print();
	//~ cout << "#########" << endl;
	//~ _b.print();
	//~ cout << "#########" << endl;
	//~ child.print();
	
	for(int i = 0; i < _a.tourSize(); i++){
		//~ cout << "round " << i << endl;
		if(i < start || i >= end){
			if(child.containsCity(_b.getCity(i))){
				//~ cout << " child contains ";
				//~ _b.getCity(i).print();
				//~ cout << endl;
				int index = _a.findIndexByName(_b.getCity(i).getName());
				//~ cout << i << "swaped with index of b swap: " << index << endl;
				child.setCity(i, _b.getCity(index));
			}else{
				child.setCity(i, _b.getCity(i));
			}
		}
	}
	//~ cout << "end loop" << endl;
	
	//~ cout << "end result +++++++++++++++++++++++++++++++++++++++" << endl;
	//~ child.print();
	return child;
}

void geneticClass::mutate(tourClass &_tour){
	for(int i = 0; i < _tour.tourSize(); i++){
		if(rand() % 1000000 <= mutationRate){
			int pos2 = rand() % _tour.tourSize();
			cityClass temp(0,0,0);
			temp.copy(_tour.getCity(i));
			_tour.setCity(i, _tour.getCity(pos2));
			_tour.setCity(pos2, temp);
		}
	}
}

tourClass geneticClass::turnamentSelection(populationClass _population){
	populationClass temp(turnamentSize, false, tour);
	//~ temp.print();
	srand(chrono::system_clock::now().time_since_epoch().count());
	for(int i = 0; i < turnamentSize; i++){
		int index = rand() % _population.populationSize();
		//~ cout << "population index: " << index << endl;
		temp.saveIndividual(i, _population.getIndividual(index));
	}
	
	tourClass fittest = temp.getFittest();
	//~ cout << "fittest";
	//~ fittest.print();
	return fittest;
}

#endif
