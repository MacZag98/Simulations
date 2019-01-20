#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "process.h"
#include "include.h"
#include "FCFS.h"
#include "SJF.h"
#include "Round_Robin.h"

#define TABLE_OF_PROCESSES "./table_of_processes.txt"
#define RESULT_FILE "./results.txt"

enum process_algorithm {
	FCFS_algorithm=0,
	SJF_algorithm,
	Round_Robin_algorithm
};

std::vector<Process> read_data_from_file (std::fstream &file);
std::vector<Process> add_processes (std::vector<Process> table_of_processes);
void simulate_algorithm (process_algorithm algorithm_name);
void save_result (std::vector<Process> &result, process_algorithm algorithm_name, int &TQ);
void show_result (std::vector<Process> &result, process_algorithm algorithm_name, int &TQ);

int main() {
	std::fstream file;
	file.open(RESULT_FILE, std::ios::out);
	file.close();

	simulate_algorithm (FCFS_algorithm);
	simulate_algorithm (SJF_algorithm);
	simulate_algorithm (Round_Robin_algorithm);

	//std::cout << "PID - Process ID\nAT - Acess time\nBT - Burst time\nCT - time at which process has ended\nTAT - Total amount of time that process spent in the system\nWT - Waiting time";
	int n;
	std::cin >> n;
	return 0;
}

std::vector<Process> read_data_from_file (std::fstream &file) {
	int tab[4];
	std::vector<Process> table_of_processes;

	while (!file.eof()) {
		file >> tab[0] >> tab[1] >> tab[2] >> tab [3];
		table_of_processes.push_back(Process(tab));
	}

	return table_of_processes;
}

std::vector<Process> add_processes (std::vector<Process> table_of_processes) {
	int number,
		first,
		second,
		third;
	std::cout << "How many?\n";
	std::cin >> number;
	std::cout << "AT - time of arrival\nBT - Burst time\nAT BT (separate with space)\n";

	first=table_of_processes.back().return_PID()+1; //starting with PID of the last process on the list + 1

	for (int i=0; i<number; ++i) {  
		std::cin >> second >> third;
		table_of_processes.push_back(Process(first+i,second,third)); //create process of PID at the end of the list and given AT and BT
	}

	std::sort (table_of_processes.begin(), table_of_processes.end(), sort_by_AT); //sort processes by AT

	return table_of_processes;
}

void simulate_algorithm (process_algorithm algorithm_name) {
	std::fstream file;
	file.open(TABLE_OF_PROCESSES, std::ios::in); //opening file in read-only mode

	if( file.good() == true ) {
		std::cout << "Access granted!" << std::endl;

		std::vector<Process> table_of_processes,
							 result;

		table_of_processes=read_data_from_file(file);

    	char menu;
		std::cout << "Do you want to add more processes to the list? [y/n]";
		std::cin >> menu;
		if (menu=='y') 
			table_of_processes=add_processes(table_of_processes);

		int TQ=0; //Time Quantum
		switch (algorithm_name) {

    		case FCFS_algorithm : 
    			result=FCFS(table_of_processes);
    			break;

			case SJF_algorithm : 
				result=SJF(table_of_processes);
				break;

			case Round_Robin_algorithm : 
				std::cout << "On what value would you like to set the TQ (Time quantum)?\n";
				std::cin >> TQ;
				result=Round_Robin(table_of_processes, TQ);
				break;
		}
		save_result(result, algorithm_name, TQ);
		file.close();
	}
	else
		std::cout << "Access denied!" << std::endl;
}

void save_result (std::vector<Process> &result, process_algorithm algorithm_name, int &TQ) {
	std::fstream file;
	file.open(RESULT_FILE, std::ios::out | std::ios::app); //opening file in save-only mode

	if( file.good() == true ) {
		std::cout << "Access granted!" << std::endl;

		float	average_TAT=0, //Average total amount of time that process spent in the system
				average_WT=0; //Average waiting time

		for (int i=0; i<result.size(); ++i) {
			average_TAT=average_TAT+result[i].TAT; //addition of TAT
			average_WT=average_WT+result[i].WT; //addition of WT
		}

		average_TAT=average_TAT/result.size(); //dividing by number of processes
		average_WT=average_WT/result.size(); //dividing by number of processes

		std::sort (result.begin(), result.end(), sort_by_PID); //sorting by PID

		switch (algorithm_name) {

    		case FCFS_algorithm : 
    			file << "FCFS Algorithm\n";
    			break;

			case SJF_algorithm : 
				file << "SJF Algorithm\n";
				break;

			case Round_Robin_algorithm : 
				file << "Round-Robin Algorithm\nTime Quantum: " << TQ << std::endl;
				break;
		}

		file << "PID	AT	BT	CT	TAT	WT	Priority\n" << result << "Average total amount of time that process spent in the system: " << average_TAT << "\nAverage waiting time: " << average_WT << std::endl;
		file.close();
	}
	else
		std::cout << "Access denied!" << std::endl;
}

void show_result (std::vector<Process> &result, process_algorithm algorithm_name, int &TQ) {
	float	average_TAT=0, //Average total amount of time that process spent in the system
			average_WT=0; //Average waiting time

	for (int i=0; i<result.size(); ++i) {
		average_TAT=average_TAT+result[i].TAT; //addition of TAT
		average_WT=average_WT+result[i].WT; //addition of WT
	}

	average_TAT=average_TAT/result.size(); //dividing by number of processes
	average_WT=average_WT/result.size(); //dividing by number of processes

	std::sort (result.begin(), result.end(), sort_by_PID); //sorting by PID

	switch (algorithm_name) {	

		case FCFS_algorithm :
			std::cout << "FCFS Algorithm\n";
			break;

		case SJF_algorithm :
			std::cout << "SJF Algorithm\n";
			break;

		case Round_Robin_algorithm :
			std::cout << "Round-Robin Algorithm\nTime Quantum: " << TQ << std::endl;
			break;
	}

	std::cout << "\nPID	AT	BT	CT	TAT	WT	Priority\n"; //showing output
	for (int i=0; i<result.size(); ++i)
		std::cout << result[i] << '\n';
	std::cout << "Average total amount of time that process spent in the system: " << average_TAT << "\nAverage waiting time: " << average_WT << std::endl;
}