#ifndef TOURMANAGER_CPP
#define TOURMANAGER_CPP

#include <vector>

using namespace std;

class tourManager{
	private:
		vector<cityClass> cityList;
	public:
		tourManager();
		void add(cityClass);
		cityClass get(int);
		int count();
};

tourManager::tourManager(){
	
}

void tourManager::add(cityClass _city){
	cityList.push_back(_city);
}

cityClass tourManager::get(int _index){
	return cityList[_index];
}

int tourManager::count(){
	return cityList.size();
}

#endif
