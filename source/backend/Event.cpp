#include "Event.h"
Event::Event(){
	//This should never be called. This is here to applease the compiler.
}
Event::Event(std::string input_name, std::string input_date, User input_creator, int input_id_number){
	date = boost::gregorian::from_string(input_date);
	
	//We cannot schedule on these days
	if(date.month() == 12 && date.day() == 25){
		//Christmas
		throw std::logic_error("cannot assign event to holiday");
	}else if(date.month() == 1 && date.day() == 1){
		//New Years
		throw std::logic_error("cannot assign event to holiday");
	}else if(date.month() == 7 && date.day() == 4){
		//July 4
		throw std::logic_error("cannot assign event to holiday");
	}
	
	name = input_name;
	creator_real_name = input_creator.getRealName();
	creator_user_name = input_creator.getUserName();
	id_number = input_id_number;
}
Event::~Event(){

}
std::string Event::get_date(){
	return boost::gregorian::to_simple_string(date);
}
std::string Event::get_name(){
	return name;
}
std::string Event::get_creator_user_name(){
	return creator_user_name;
}
std::string Event::get_creator_real_name(){
	return creator_real_name;
}
int Event::get_id_number(){
	return id_number;
}
bool Event::operator>=(Event rhs){
	return date >= rhs.date;
}
bool Event::operator<=(Event rhs){
	return date <= rhs.date;
}
bool Event::operator>(Event rhs){
	return date > rhs.date;
}
bool Event::operator<(Event rhs){
	return date < rhs.date;
}
