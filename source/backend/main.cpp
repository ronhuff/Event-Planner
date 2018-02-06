#include "Executive.h"
#include <iostream>

int main(int argc, char* argv[]){
	Executive e;
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
		default:
			std::cout << "Welcoming to testing. Extend the main file as needed.\n";
			std::cout << "If the first argument is 'a', give an event name and a date as the 2nd and 3rd argument to add an event. A '1' indicates sucess.\n"
			std::cout << "If the first argument is 'd', display all events in file.\n"
			std::cout << "If the first argument is 'r', give an integer to delete the event with the id number. A '1' indicates sucess.\n"
			
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
	





