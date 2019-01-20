#ifndef FCFS_H
#define FCFS_H

std::vector<Process> FCFS (std::vector<Process> table_of_processes) {
	std::sort (table_of_processes.begin(), table_of_processes.end(), sort_by_AT);
	int time=0; //increasing every step
	std::vector<Process> queue = {table_of_processes[0]};

	while(!queue.empty()) { //while queue is not empty
		time=time+queue[0].return_BT(); //incrementing time

		if (queue[queue.size()].return_BT()==0) { // if BT in queue equal 0

			queue[queue.size()].CT=time-queue[0].return_BT();	// CT = time from previous round of the loop
			queue[queue.size()].TAT=queue[queue.size()].CT-queue[queue.size()].return_AT(); //TAT = CT - AT

			for (int i=0; i<table_of_processes.size(); ++i) { //serching for right PID in table_of_processes
				if (queue[queue.size()].return_PID()==table_of_processes[i].return_PID()) {
					table_of_processes[i].CT=queue[queue.size()].CT; //assigning CT and TAT to the right PID in table_of_processes
					table_of_processes[i].TAT=queue[queue.size()].TAT;
					queue.erase(queue.end()); //erasing bursted process from queue
					break;
				}
			}
		}
		
		for (int i=0; i<table_of_processes.size(); ++i) //arrival of the new processes
			if (time-queue[0].return_BT()<table_of_processes[i].return_AT() && table_of_processes[i].return_AT()<=time)
				queue.push_back(table_of_processes[i]);
			
		queue.push_back(Process(queue[0].return_PID(),queue[0].return_AT(),0)); //moving process to the end of the queue
		queue.erase(queue.begin()); //erasing moved process
    }
	for (int i=0; i<table_of_processes.size(); ++i)
		table_of_processes[i].WT=table_of_processes[i].TAT-table_of_processes[i].return_BT(); //calculating waiting time

	return table_of_processes;
}

#endif // FCFS_H