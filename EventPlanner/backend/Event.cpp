#include "Event.h"
Event::Event(){
	//This should never be called. This is here to applease the compiler.
}
Event::Event(std::string inputName, std::string inputDate, std::string inputCreatorUsername, std::string inputCreatorRealName, int inputIDNum){
	date = boost::gregorian::from_string(inputDate);
	
	name = inputName;
	creatorRealName = inputCreatorRealName;
	creatorUserName = inputCreatorUsername;
	idNum = inputIDNum;
}
Event::~Event(){

}
std::string Event::getDate(bool ifIO){
	//Get the date as a string.
	std::string s = boost::gregorian::to_iso_extended_string(date);
	for(int x = s.length()-1; x >= 0; x--){
		if(s.at(x) == '-'){
			s.at(x) = '/';
		}
	}
	std::cout << s + "* DBG Event.cpp:24\n";
	if (ifIO) return(s);
	return dateFormatFixer(s);
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

std::string Event::dateFormatFixer(std::string date)
{
	if (date.length() == 10 && date[4] == '/' && date[7] == '/')
	{
		std::string year = date.substr(0, 4);
		std::string month = date.substr(5, 2);
		std::string day = date.substr(8, 2);
		return (month + "/" + day + "/" + year);
	}
	else//if problems, it will just display the original format.
	{
		return(date);
	}
}