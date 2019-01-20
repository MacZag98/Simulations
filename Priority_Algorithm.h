#ifndef PRIORITY_ALGORITHM_H
#define PRIORITY_ALGORITHM_H

std::vector<Process> Priority_Algorithm (std::vector<Process> table_of_processes) {
	std::sort (table_of_processes.begin(), table_of_processes.end(), sort_by_AT);
	
	
	return table_of_processes;
}

#endif // PRIORITY_ALGORITHM_H