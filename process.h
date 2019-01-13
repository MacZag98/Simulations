#ifndef PROCESS_H
#define PROCESS_H
#include <iostream>

class Process
{
    int PID; //Process identification number
    int AT; //Arrival time
    int BT; //Burst time - time required to finish the process
    public:
        Process() {}
        Process(int first, int second, int third) {
        	PID=first;
        	AT=second;
        	BT=third;
        }
        int return_PID() {return PID;}
        int return_AT() {return AT;}
        int return_BT() {return BT;}
        int CT=0; //time at which process was finished
        int TAT=0; //Total amount of time that process spent in the system
        int WT=0; //Waiting time
};

std::ostream &operator<<(std::ostream& str, Process &p) {
    str<<p.return_PID()<<"	"<<p.return_AT()<<"	"<<p.return_BT()<<"	"<<p.CT<<"	"<<p.TAT<<"	"<<p.WT;
    return str;
}

std::ostream &operator<<(std::ostream& str, std::vector<Process> &p) {
    for (int i=0; i<p.size(); ++i)
        str<<p[i].return_PID()<<"	"<<p[i].return_AT()<<"	"<<p[i].return_BT()<<"	"<<p[i].CT<<"	"<<p[i].TAT<<"	"<<p[i].WT<<"\n";
    return str;
}

#endif // PROCESS_H