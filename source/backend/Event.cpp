#include "Event.h"
Event::Event(){
	//This should never be called. This is here to applease the compiler.
}
Event::Event(std::string input_name, std::string input_date, std::string input_creator, int input_id_number){
	name = input_name;
	date = boost::gregorian::from_string(input_date);
	creator = input_creator;
	id_number = input_id_number;
}
Event::~Event(){
}
boost::gregorian::date Event::get_date(){
	return date;
}
std::string Event::get_name(){
	return name;
}
std::string Event::get_creator(){
	return creator;
}
int Event::get_id_number(){
	return id_number;
}
