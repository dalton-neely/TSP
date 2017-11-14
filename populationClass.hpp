#ifndef POPULATIONCLASS_HPP
#define POPULATIONCLASS_HPP

using namespace std;

class populationClass{
	public:
		vector<tourClass> population;
		
		populationClass(int, bool, tourManager *);
		void saveIndividual(int, tourClass);
		tourClass getIndividual(int);
		tourClass getFittest();
		int populationSize();
		void print();
};

void populationClass::print(){
	cout << "Population Print:" << endl;
	cout << "########################" << endl;
	for(int i = 0; i < populationSize(); i++){
		cout << "^^^^^^^^^^^^^^^^^^^^^^" << endl;
		population[i].print();
		cout << "^^^^^^^^^^^^^^^^^^^^^^" << endl;
	}
	cout << "########################" << endl;
}

populationClass::populationClass(int _popSize, bool init, tourManager * tourMan){
	for(int i = 0; i < _popSize; i++){
		tourClass temp(tourMan);
		population.push_back(temp);
	}
	
	if(init){
		for(int i = 0; i < _popSize; i++){
			tourClass temp(tourMan);
			temp.generateIndividual();
			saveIndividual(i, temp);
		}
	}else{
		for(int i = 0; i < _popSize; i++){
			tourClass temp(tourMan);
			temp.generateInit();
			saveIndividual(i, temp);
		}
	}
}

void populationClass::saveIndividual(int _index, tourClass _tour){
	population[_index] = _tour;
}

tourClass populationClass::getIndividual(int _index){
	return population[_index];
}

tourClass populationClass::getFittest(){
	tourClass fittest = population[0];
	for(int i = 1; i < populationSize(); i++){
		if(fittest.getFitness() <= getIndividual(i).getFitness()){
			fittest = getIndividual(i);
			//~ cout << i << " is the fittest" << endl;
		}
	}
	//~ print();
	return fittest;
}

int populationClass::populationSize(){
	return population.size();
}

#endif
