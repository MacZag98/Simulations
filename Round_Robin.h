#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H

std::vector<Process> Round_Robin (std::vector<Process> table_of_processes, int &TQ) {
	int time=0; //increasing every step
	std::vector<Process> queue = {table_of_processes[0]};
	while(!queue.empty()) { //while queue is not empty
		if (queue[0].return_BT()>TQ) { //if Burst time is greater than Time quantum
			time=time+TQ; //incrementing time
			for (int i=0; i<table_of_processes.size(); ++i) //arrival of the new processes
				if (time-TQ<table_of_processes[i].return_AT() && table_of_processes[i].return_AT()<=time)
					queue.push_back(table_of_processes[i]);
			if (queue[queue.size()].return_BT()==0) { // if BT in queue equal 0
				queue[queue.size()].CT=time-TQ;	// CT = time from previous round of the loop
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
			queue.push_back(Process(queue[0].return_PID(),queue[0].return_AT(),(queue[0].return_BT()-TQ))); //moving process to the end of the queue
			queue.erase(queue.begin()); //erasing moved process
		}
		else { //if Burst time is smallero than or equal Time quantum
			time=time+queue[0].return_BT(); //incrementing time
			for (int i=0; i<table_of_processes.size(); ++i) //arrival of the new processes
				if (time-queue[0].return_BT()<table_of_processes[i].return_AT() && table_of_processes[i].return_AT()<=time)
					queue.push_back(table_of_processes[i]);
			if (queue[queue.size()].return_BT()==0) { // if BT in queue equal 0
				queue[queue.size()].CT=time-queue[0].return_BT(); // CT = time from previous round of the loop
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
		    queue.push_back(Process(queue[0].return_PID(),queue[0].return_AT(),0)); //moving process to the end of the queue
			queue.erase(queue.begin()); //erasing moved process
		}
    }
	for (int i=0; i<table_of_processes.size(); ++i)
		table_of_processes[i].WT=table_of_processes[i].TAT-table_of_processes[i].return_BT(); //calculating waiting time
	return table_of_processes;
}

#endif // ROUND_ROBIN_H