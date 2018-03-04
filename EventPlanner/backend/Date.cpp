#include "../stdafx.h"
#include "Date.h"

Date::Date() {

}

Date::Date(std::string inputDate, std::string startTime, int numTimeslots, std::shared_ptr<User> creator) {

	//code for determining time and creating timeslots here.
	
	std::shared_ptr<TimeSlot> temp = std::make_shared<TimeSlot>(startTime);
	temp->m_attendees.push_back(creator);
	int endMin = stoi(startTime.substr(3, 2));
	endMin += 20;
	m_timeSlots.push_back(temp);
	std::string startHr = startTime.substr(0, 2);
	for (int i = 0; i < numTimeslots; i++)
	{		
		std::string slot = "";
		//etime.substr(3, 2) this returns the endmin string
		if (endMin >= 60) {
			endMin = 0;
			int hourInt = std::stoi(startHr);
			hourInt++;
			startHr = std::to_string(hourInt);
			slot = startHr + ":" + "00";
			endMin += 20;
		}
		else {
			slot = startHr + ":" + std::to_string(endMin);
			endMin += 20;
		}
		std::shared_ptr<TimeSlot> temp = std::make_shared<TimeSlot>(startHr + ":" + std::to_string(endMin));
		temp->m_attendees.push_back(creator);//adds creator as attendee of each timeslot.
		m_timeSlots.push_back(temp);
	}
	m_date = inputDate;
}
Date::~Date() {

}
//std::list<std::string>* Date::getTimeSlots() {
	//return(timeSlots);
//}
//std::string Date::getDate(bool ifIO) {
	/*std::string s = boost::gregorian::to_iso_extended_string(date);*/
	/*for (int x = s.length() - 1; x >= 0; x--) {
		if (s.at(x) == '-') {
			s.at(x) = '/';
		}
	}
	if (ifIO) return(s);
	return dateFormatFixer(s);*/
	//return("hi");
//}
std::string Date::dateFormatFixer(std::string date) {
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