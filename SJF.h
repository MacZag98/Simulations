#ifndef SJF_H
#define SJF_H

void SJF (std::vector<Process> table_of_processes) {
	table_of_processes[0].CT=table_of_processes[0].return_BT()+table_of_processes[0].return_AT(); //calculating the algorithm for the first process
	table_of_processes[0].TAT=table_of_processes[0].return_BT();
	table_of_processes[0].WT=0;
	for (int i=1; i<table_of_processes.size(); ++i) { //calculating the algorithm for the rest of the processes
		int number=i; //assisting variable
		for (int j=i; j<table_of_processes.size(); ++j)
			if (table_of_processes[j].return_BT()<=table_of_processes[i-1].CT) //if BT of current process is smaller than or equal to CT of previous process
				++number; //increment variable
		std::sort (table_of_processes.begin()+i, table_of_processes.begin()+number, sort_by_BT); //sorting by Burst time processes that already arrived
		table_of_processes[i].CT=table_of_processes[i-1].CT+table_of_processes[i].return_BT(); //CT = CT of the previously ended process + BT of the current process
		table_of_processes[i].TAT=table_of_processes[i].CT-table_of_processes[i].return_AT(); //TAT = CT - AT
		table_of_processes[i].WT=table_of_processes[i].TAT-table_of_processes[i].return_BT(); //WT = TAT - BT
	}
	float	average_TAT=0, //Average total amount of time that process spent in the system
			average_WT=0; //Average waiting time
	for (int i=0; i<table_of_processes.size(); ++i) {
		average_TAT=average_TAT+table_of_processes[i].TAT; //addition of TAT
		average_WT=average_WT+table_of_processes[i].WT; //addition of WT
	}
	average_TAT=average_TAT/table_of_processes.size(); //dividing by number of processes
	average_WT=average_WT/table_of_processes.size(); //dividing by number of processes
	std::sort (table_of_processes.begin(), table_of_processes.end(), sort_by_PID); //sorting by PID
	std::cout<<"\nSJF Algorithm\nPID	AT	BT	CT	TAT	WT\n"; //showing output
	for (int i=0; i<table_of_processes.size(); ++i)
        std::cout << table_of_processes[i] << '\n';
    std::cout<<"Average total amount of time that process spent in the system: "<<average_TAT<<"\nAverage waiting time: "<<average_WT;
}

#endif // SJF_H