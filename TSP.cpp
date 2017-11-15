#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <iomanip>

using namespace std;

const int POPSIZE = 50;
const string FILENAME = "cities.txt";
const int MRATE = 50;
const int TSIZE = 5;
const int GENERATIONS = 50;

class City{
	public:
		int x, y, name;
		City(){
			this->x = 0;
			this->y = 0;
			this->name = 0;
		}
		City(int x, int y, int name){
			this->x = x;
			this->y = y; 
			this->name = name;
		}
		void print(){
			cout << "####CITY####" << endl;
			if(this->x > 9)
				cout << "#----" << this->x << "----#" << endl;
			else
				cout << "#----0" << this->x << "----#" << endl;
			if(this->y > 9)
				cout << "#----" << this->y << "----#" << endl;
			else
				cout << "#----0" << this->y << "----#" << endl;
			if(this->name > 9)
				cout << "#----" << this->name << "----#" << endl;
			else
				cout << "#----0" << this->name << "----#" << endl;
			cout << "####CITY####" << endl;
		}
		void copy(City city){
			this->x = city.x;
			this->y = city.y;
			this->name = city.name;
		}
		bool equal(City city){
			return (this->x == city.x && this->y == city.y && this->name == city.name);
		}
		double distance(City city){
			return sqrt(pow((double)this->x - (double)city.x, 2.00) + pow((double)this->y - (double)city.y, 2.00));
		}
};

class Resources{
	public:
		vector<City> cities;
		int size;
		Resources(){
			ifstream in(FILENAME);
			size = 0;
			
			City city;
			while(in >> city.name >> city.x >> city.y){
				this->size++;
				this->insert(city);
			}
		}
		void insert(City city){
			this->cities.push_back(city);
		}
		void print(){
			cout << "@@@@@@@@@@RESOURCES@@@@@@@@@@" << endl;
			for(int i = 0; i < this->size; i++){
				cout << "@---------" << i << endl;
				this->cities[i].print();
				cout << "@ENDENDEND--" << i << endl;
			}
			cout << "@@@@@@@@@@RESOURCES@@@@@@@@@@" << endl;
		}
}RESOURCES;

class Individual{
	public:
		vector<City> chromosome;
		double fitness;
		double distance;
		
		Individual(){
			this->fitness = -1.0;
			this->distance = -1.0;
			City temp;
			for(int i = 0; i < RESOURCES.size; i++)
				this->chromosome.push_back(temp);
		}
		void update(){
			this->getDistance();
			this->getFitness();
		}
		void shuffle(){
			srand(chrono::system_clock::now().time_since_epoch().count());
			City temp;
			for(int i = 0; i < rand() % 100 + 75; i++){
				int swap1 = rand() % RESOURCES.size;
				int swap2 = rand() % RESOURCES.size;
				temp.copy(this->chromosome[swap1]);
				this->chromosome[swap1].copy(this->chromosome[swap2]);
				this->chromosome[swap2].copy(temp);
			}
			this->getDistance();
			this->getFitness();
		}
		void generateIndividual(){
			for(int i = 0; i < RESOURCES.size; i++)
				this->chromosome[i].copy(RESOURCES.cities[i]);
			this->shuffle();
			this->getDistance();
			this->getFitness();
		}
		bool check(){
			int checkValue = 1;
			for(int i = 0; i < RESOURCES.size; i++){
				for(int j = 0; j < RESOURCES.size; j++){
					if(checkValue == this->chromosome[j].name){
						checkValue++;
					}
				}
			}
			if(checkValue == RESOURCES.size + 1){
				return true;
			}else{
				return false;
			}
		}
		void getDistance(){
			this->distance = 0;
			for(int i = 0; i < RESOURCES.size; i++){
				if(i != RESOURCES.size - 1){
					this->distance += this->chromosome[i].distance(chromosome[i + 1]);
				}else{
					this->distance += this->chromosome[i].distance(chromosome[0]);
				}
			}
		}
		void getFitness(){
			this->fitness = 1/this->distance;
		}
		void copy(Individual individual){
			for(int i = 0; i < RESOURCES.size; i++)
				this->chromosome[i].copy(individual.chromosome[i]);
			this->getDistance();
			this->getFitness();
		}
		bool equal(Individual individual){
			bool returnValue = true;
			for(int i = 0; i < RESOURCES.size; i++)
				if(!this->chromosome[i].equal(individual.chromosome[i]))
					returnValue = false;
			return returnValue;
		}
		int find(int name){
			int foundIndex = -1;
			for(int i = 0; i < RESOURCES.size; i++){
				if(this->chromosome[i].name == name)
					foundIndex = i;
			}
			return foundIndex;
		}
		bool contains(City city){
			bool returnValue = false;
			for(int i = 0; i < RESOURCES.size; i++)
				if(this->chromosome[i].equal(city))
					returnValue = true;
			return returnValue;
		}
		int mutate(){
			int num = 0;
			srand(chrono::system_clock::now().time_since_epoch().count());
			for(int i = 0; i < RESOURCES.size; i++){
				if(rand() % 1000000 <= MRATE){
					num++;
					int pos2 = rand() % RESOURCES.size;
					City temp;
					temp.copy(this->chromosome[i]);
					this->chromosome[i].copy(this->chromosome[pos2]);
					this->chromosome[pos2].copy(temp);
				}
			}
			this->getDistance();
			this->getFitness();
			return num;
		}
		void print(){
			cout.setf(ios::fixed);
			cout.precision(2);
			cout << "++++++++++INDIVIDUAL++++++++++" << endl;
			cout << "++++++++++Distance:" << this->distance << endl;
			cout.precision(5);
			cout << "++++++++++Fitness: " << this->fitness << endl;
			for(int i = 0; i < RESOURCES.size; i++){
				cout << "+---------" << i << endl;
				this->chromosome[i].print();
				cout << "+ENDENDEND--" << i << endl;
			}
			cout << "++++++++++INDIVIDUAL++++++++++" << endl;
		}
		void printLine(){
			cout << "~~~~~~~~INDIVIDUAL LINE~~~~~~~~~~~~" << endl;
			cout << "Distance: " << this->distance << endl;
			cout << "Fitness: " << this->fitness << endl;
			cout << "Cities: ";
			for(int i = 0; i < RESOURCES.size; i++){
				cout << " |" << this->chromosome[i].name << "|";
			}
			cout << endl;
			cout << "~~~~~~~~INDIVIDUAL LINE~~~~~~~~~~~~" << endl;
		}
		
};

class Population{
	public:
		vector<Individual> individuals;
		int size;
		Population(){
			this->size = POPSIZE;
			Individual individual;
			for(int i = 0; i < POPSIZE; i++)
				this->individuals.push_back(individual);
		}
		Population(int size){
			this->size = size;
			Individual individual;
			for(int i = 0; i < this->size; i++)
				this->individuals.push_back(individual);
		}
		void copy(Population pop){
			for(int i = 0; i < this->size; i++){
				this->individuals[i].copy(pop.individuals[i]);
			}
		}
		void save(int index, Individual individual){
			this->individuals[index].copy(individual);
		}
		void generate(){
			Individual individual;
			individual.generateIndividual();
			for(int i = 0; i < this->size; i++){
				individual.shuffle();
				this->save(i, individual);
			}
		}
		Individual getFittest(){
			int fittestIndex = 0;
			double fit = 0.000000000;
			for(int i = 0; i < this->size; i++){
				if(this->individuals[i].fitness > fit){
					fittestIndex = i;
					fit = this->individuals[i].fitness;
				}
			}
			return this->individuals[fittestIndex];
		}
		void print(){
			cout << "%%%%%%%%%%%%%%%%%%%%%%POPULATION%%%%%%%%%%%%%%%%%%%%" << endl;
			for(int i = 0; i < this->size; i++){
				cout << "----->" << i << endl;
				cout << "Distance: " << this->individuals[i].distance << endl;
				cout << "Fitness: " << this->individuals[i].fitness << endl;
				cout << "Citys: ";
				for(int j = 0; j < RESOURCES.size; j++){
					cout << " |" << this->individuals[i].chromosome[j].name << "|";
				}
				cout << endl;
			}
			cout << "%%%%%%%%%%%%%%%%%%%%%%POPULATION%%%%%%%%%%%%%%%%%%%%" << endl;
		}
};

class Lab{
	public:
		int mutations;
		int crossovers;
		Lab(){
			this->mutations = 0;
			this->crossovers = 0;
		}
		Individual tournamentSelection(Population pop){
			Population temp(TSIZE);
			int index = 0;
			srand(chrono::system_clock::now().time_since_epoch().count());
			for(int i = 0; i < TSIZE; i++){
				index = rand() % POPSIZE;
				if(index >= POPSIZE)
					index--;
				temp.save(i, pop.individuals[index]);
			}
			Individual fittest;
			fittest = temp.getFittest();
			return fittest;
		}
		Individual crossover(Individual parent1, Individual parent2){
			this->crossovers++;
			Individual child;
			
			int start = rand() % RESOURCES.size;
			int end = rand() % RESOURCES.size;
			
			if(end <= start){
				int temp = start;
				start = end;
				end = temp;
			}
			
			for(int i = start; i < end; i++){
				child.chromosome[i].copy(parent1.chromosome[i]);
			}

			for(int i = 0; i < RESOURCES.size; i++){
				if(!child.contains(parent2.chromosome[i])){
					for(int j = 0; j < RESOURCES.size; j++){
						if(child.chromosome[j].name == 0){
							child.chromosome[j].copy(parent2.chromosome[i]);
							break;
						}
					}
				}
			}
			child.update();
			return child;
		}
		Population evolve(Population pop){
			Population temp; 
			
			temp.save(0, pop.getFittest());
			
			
			for(int i = 1; i < pop.size; i++){
				Individual parent1, parent2;
				parent1.copy(this->tournamentSelection(pop));
				parent2.copy(this->tournamentSelection(pop));
				while(parent1.equal(parent2)){
					parent2.copy(this->tournamentSelection(pop));
				}
				
				Individual child;
				child.copy(this->crossover(parent1, parent2));
				temp.save(i, child);
			}
			
			for(int i = 1; i < pop.size; i++)
				this->mutations += temp.individuals[i].mutate();
			
			return temp;
		}
};

int main(){
	Population population;
	population.generate();
	Lab lab;
	cout << "Generations: " << GENERATIONS << endl;
	cout << "initial distance: " << population.getFittest().distance << endl;
	population.copy(lab.evolve(population));
	for(int i = 0; i < GENERATIONS; i++){
		if(i % 5 == 0)
			cout << ".";
		population.copy(lab.evolve(population));
	}
	cout << "Fittest distance: " << population.getFittest().distance << endl;
	population.getFittest().printLine();
	cout << "Is the final inividual visiting every city? " << population.getFittest().check() << endl;
	cout << "Number of Mutations: " << lab.mutations << endl;
	cout << "Number of Crossovers: " << lab.crossovers << endl;
	return 0;
}
