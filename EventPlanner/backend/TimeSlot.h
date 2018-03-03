#pragma once

#include <string>
#include <memory>
#include <vector>

#include "User.h"

class User;

class TimeSlot
{
public:
	TimeSlot();
	TimeSlot(std::string);
	~TimeSlot();


	std::string m_startTime; //expected format HH:MM(e.g. 08:00, 17:00) if necessary, reformat output in interface (e.g. 8:00 AM)
	
	//vector of attendees for this TimeSlot
	std::vector<std::shared_ptr<User>> m_attendees;
};

