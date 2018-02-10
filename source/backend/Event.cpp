#include "Event.h"
Event::Event(){
	//This should never be called. This is here to applease the compiler.
}
Event::Event(std::string inputName, std::string inputDate, User inputCreator, int inputIDNum){
	date = boost::gregorian::from_string(inputDate);
	
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
	
	name = inputDate;
	creatorRealName = inputCreator.getRealName();
	creatorUserName = inputCreator.getUserName();
	idNum = inputIDNum;
}
Event::~Event(){

}
std::string Event::getDate(){
	//Get the date as a string.
	std::string s = boost::gregorian::to_iso_extended_string(date);
	for(int x = s.length()-1; x >= 0; x--){
		s.at(x) = '/';
	}
	return ;
}
std::string Event::getName(){
	return name;
}
std::string Event::getCreatorUserName(){
	return creatorUserName;
}
std::string Event::getCreatorRealName(){
	return creatorRealName;
}
int Event::getIDNumber(){
	return idNum;
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
