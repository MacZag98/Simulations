#ifndef SJF_H
#define SJF_H

std::vector<Process> SJF (std::vector<Process> table_of_processes) {
	std::sort (table_of_processes.begin(), table_of_processes.end(), sort_by_AT); //sort by Arrival Time
	int time=0; //increasing every step
	std::vector<Process> queue = {table_of_processes[0]}; // create a queue

	while(!queue.empty()) { //while queue is not empty
		std::sort (queue.begin(), queue.end(), sort_by_BT); //sort queue by Burst Time
		
		if (queue[0].return_BT()==0) { // if BT in queue equal 0

			queue[0].CT=time;	// CT = current time
			queue[0].TAT=queue[0].CT-queue[0].return_AT(); //TAT = CT - AT

			for (int i=0; i<table_of_processes.size(); ++i) { //serching for right PID in table_of_processes
				if (queue[0].return_PID()==table_of_processes[i].return_PID()) {
					table_of_processes[i].CT=queue[0].CT; //assigning CT and TAT to the right PID in table_of_processes
					table_of_processes[i].TAT=queue[0].TAT;
					queue.erase(queue.begin()); //erasing bursted process from queue
					break;
				}
			}
		}
		time=time+queue[0].return_BT(); //incrementing time

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

#endif // SJF_H