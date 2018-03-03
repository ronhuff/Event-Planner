#include "Date.h"

Date::Date(){

}

Date::Date(std::string inputDate, std::list<std::string> slots){
  date = boost::gregorian::from_string(inputDate);
  timeSlots = slots;
}
Date::~Date(){

}
std::list<std::string> Date::getTimeSlots(){
  return(timeSlots);
}
std::string Date::getDate(bool ifIO){
  std::string s = boost::gregorian::to_iso_extended_string(date);
	for(int x = s.length()-1; x >= 0; x--){
		if(s.at(x) == '-'){
			s.at(x) = '/';
		}
	}
	if (ifIO) return(s);
	return dateFormatFixer(s);
}
std::string Date::dateFormatFixer(std::string date){
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
