#ifndef EVENT_H
#define EVENT_H

#include <boost/date.hpp>
#include <string>
#include "Record.hpp"

class Event{
	public:
		Event();
		Event(std::string name, std::string date, std::string creator,int id_number);
		~Event();
		std::string get_name();
		std::string get_creator();
		int get_id_number();
		Record* availabilites;
		
		
		//std::string get_description(); //Optional
	private:
		Record* availabilites;
		//boost::gregorian::date date; //Careful!, not sure how to do this yet.
	
		std::string name;
		std::string creator_username;
		int id_number;
		
		//std::string description; //Optional
		//bool completed; //Optional
};

#endif
