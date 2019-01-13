// DODAJ ZGRANIE DO PLIKU I ZASTANOW SIE DLACZEGO ROUND ROBIN NIE DZIALA PRZY PONOWNYM WYWOLANIU FUNKCJI

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "process.h"
#include "include.h"
#include "FCFS.h"
#include "SJF.h"
#include "Round_Robin.h"

#define TABLE_OF_PROCESSES "./table_of_processes3.txt"

std::vector<Process> add_processes (std::vector<Process> table_of_processes);

int main() {
	std::fstream file;
	file.open(TABLE_OF_PROCESSES, std::ios::in); //opening file in read-only mode
	if( file.good() == true ) {
		std::cout << "Access granted!" << std::endl;
		int first_column,
			second_column,
			third_column;
		std::vector<Process> table_of_processes;
		while (!file.eof()) {
			file>>first_column>>second_column>>third_column;
			table_of_processes.push_back(Process(first_column,second_column,third_column));
		}
    	char menu;
		std::cout<<"Do you want to add more processes to the list? [y/n]";
		std::cin>>menu;
		if (menu=='y') table_of_processes=add_processes(table_of_processes);
    	FCFS(table_of_processes);
		SJF(table_of_processes);
		Round_Robin(table_of_processes);
		std::cout<<"\n\nPID - Process ID\nAT - Acess time\nBT - Burst time\nCT - time at which process has ended\nTAT - Total amount of time that process spent in the system\nWT - Waiting time";
	}
	else {
		std::cout << "Access denied!" << std::endl;
		return 1;
	}
	int n;
	std::cin>>n;
	return 0;
}

std::vector<Process> add_processes (std::vector<Process> table_of_processes) {
	int number,
		first,
		second,
		third;
	std::cout<<"How many?\n";
	std::cin>>number;
	std::cout<<"AT - time of arrival\nBT - Burst time\nAT BT (separate with space)\n";
	first=table_of_processes.back().return_PID()+1; //starting with PID of the last process on the list + 1
	for (int i=0; i<number; ++i) {  
		std::cin>>second>>third;
		table_of_processes.push_back(Process(first+i,second,third)); //create process of PID at the end of the list and given AT and BT
	}
	std::sort (table_of_processes.begin(), table_of_processes.end(), sort_by_AT); //sort processes by AT
	return table_of_processes;
}