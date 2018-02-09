#include "Executive.h"
#include <iostream>

int main(int argc, char* argv[]){
    Executive e;

    e.searchUserFile("dnewman") ? std::cout << "Found \"dnewman\"\n" : std::cout << "Method failed\n";
    e.searchUserFile("schoi") ? std::cout << "Found \"schoi\"\n" : std::cout << "Method failed\n";
    e.searchUserFile("wgraham") ? std::cout << "Found \"wgraham\"\n" : std::cout << "Method failed\n";
    e.searchUserFile("dnewman") ? std::cout << "Found \"dnewman\"\n" : std::cout << "Method failed\n";
    return (0);
}

/*

FILES
EventList.txt
	0 0
	1 1
	1 3
	etc...
info_#.txt
	<name>
	<creator username>
record_#.txt
	<TimeBlock> : <userId> list
	<TimeBlock> : ...
user_<username>.txt
	<propername> <event_id> ...
	
*/
	





