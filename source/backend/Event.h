#ifndef EVENT_H
#define EVENT_H

#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>
#include "Record.h"

class Event{
	public:
		Event();
		Event(std::string input_name, std::string input_date, std::string input_creator, int input_id_number);
		~Event();
		boost::gregorian::date get_date();
		std::string get_name();
		std::string get_creator();
		int get_id_number();
		
		//std::string get_description(); //Optional
	private:
		boost::gregorian::date date;
		std::string name;
		std::string creator;
		int id_number;
		//List of records
		
		//std::string description; //Optional
		//bool completed; //Optional
};

#endif
