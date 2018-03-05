#include "Event.h"
Event::Event() {
	//This should never be called. This is here to applease the compiler.
}
Event::Event(std::string inputName, std::string inputDate, std::string inputCreatorUsername, std::string inputCreatorRealName, int inputIDNum) {
	listOfDates.push_back(inputDate);
	name = inputName;
	creatorRealName = inputCreatorRealName;
	creatorUserName = inputCreatorUsername;
	idNum = inputIDNum;
}
Event::~Event() {

}
std::string Event::getDate(std::string date) {
	for (int i = 0; i < listOfDates.size(); i++) {
		if (listOfDates.at(i) == date) {
			return(listOfDates.at(i));
		}
	}
}

std::string Event::getName() {
	return name;
}
std::string Event::getCreatorUserName() {
	return creatorUserName;
}
std::string Event::getCreatorRealName() {
	return creatorRealName;
}
int Event::getIDNumber() {
	return idNum;
}
/*bool Event::operator>=(Event rhs){
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
}*/

bool Event::addTaskList() {
	if (tasks == nullptr) {
		tasks = new TaskList();
		return(true);
	}
	else {
		//this should never execute due to it not being shown in event view if task doesn't exist.
		return(false);
	}
	return false;
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
void Event::addTimeSlot(std::list<std::string>* list) {
	listOfTimeSlots.push_back(list);
}