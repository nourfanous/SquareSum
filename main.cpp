#include <iostream>
#include <fstream>
#include <ctime>
#include "graph.h"
int main() {
	int start;
        int last;
        std::cin >> start >> last;	
	std::ofstream fout ("ans2.out");
	for (int i = start; i < last; ++i)
	{
		graph mygraph(i);
		const long int beforeTime = time(0);
		bool anser = mygraph.hasCycle();
		const long int theTime = (time(0) - beforeTime);
		std::cout << i;
		fout << i;
		if (anser){
			std::cout << " Good ";
			fout <<" Good ";
		}else {
			std::cout << " Bad  ";
			fout <<" Bad  ";
		}
		std::cout << theTime << std::endl;
		fout << theTime << std::endl;
	}
}
