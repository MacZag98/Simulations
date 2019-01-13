#ifndef FCFS_H
#define FCFS_H
#include <vector>

std::vector<Process> FCFS (std::vector<Process> table_of_processes) {
	table_of_processes[0].CT=table_of_processes[0].return_BT()+table_of_processes[0].return_AT(); //calculating the algorithm for the first process
	table_of_processes[0].TAT=table_of_processes[0].return_BT();
	table_of_processes[0].WT=0;
	for (int i=1; i<table_of_processes.size(); ++i) { //calculating the algorithm for the rest of the processes
		table_of_processes[i].CT=table_of_processes[i-1].CT+table_of_processes[i].return_BT(); //CT = CT of the previously ended process + BT of the current process
		table_of_processes[i].TAT=table_of_processes[i].CT-table_of_processes[i].return_AT(); //TAT = CT - AT
		table_of_processes[i].WT=table_of_processes[i].TAT-table_of_processes[i].return_BT(); //WT = TAT - BT
	}
	return table_of_processes;
}

#endif // FCFS_H