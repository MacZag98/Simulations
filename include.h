#ifndef INCLUDE_H
#define INCLUDE_H
#include <iostream>

bool sort_by_AT (Process i, Process j) { return (i.return_AT()<j.return_AT()); }
bool sort_by_BT (Process i, Process j) { return (i.return_BT()<j.return_BT()); }
bool sort_by_PID (Process i, Process j) { return (i.return_PID()<j.return_PID()); }

#endif // INCLUDE_H