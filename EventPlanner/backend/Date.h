#pragma once

#include <string>
#include <list>
#include <memory>
#include <vector>
#include "TimeSlot.h"
#include "User.h"

//#include "date_time.hpp"
//#include "gregorian.hpp"
class User;
class TimeSlot;

class Date {
public:
	Date();
	Date(std::string inputDate, std::string startTime, int numTimeslots, std::shared_ptr<User> creator);
	~Date();
	

	

	std::string m_startTime;
	std::string m_endTime;

	std::string m_date;
	std::vector<std::shared_ptr<TimeSlot>> m_timeSlots;
	/*boost::gregorian::date date;*/
	std::string dateFormatFixer(std::string date);



private:
};
