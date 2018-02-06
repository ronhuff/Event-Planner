#include "Executive.h"
#include <iostream>

int main(int argc, char* argv[]){
	Executive e;
	if(argc >= 2){
		switch(argv[1][0]){
			case 'a':
				if(argc == 4){
					std::cout << e.generate_event(argv[2],argv[3]) << '\n';
				}
			break;
			case 'r':
				if(argc == 3){
					std::cout << e.delete_event(std::stoi(argv[2])) << '\n';
				}
			break;
			case 'd':
				std::vector<Event> l = e.get_event_list();
				for(auto&& x = l.begin(); x != l.end(); x++){
					//Iterate over every element in the vector.
					std::cout << x->get_id_number() << '\n';
				}
			break;
		}
	}
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
	





