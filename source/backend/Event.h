#ifndef EVENT_H
#define EVENT_H

#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>
#include "Record.h"

/**
 * Event Class. 
 * The class encapsulates the basic details of an event and contains a reference to its attendence record.
 */

class Event{
	public:
		/**
		 * The empty constructor. 
		 * This builds an empty event and is not intended for use.
		 */
		Event();
		/**
		 * The constructor that takes 4 arguments. 
		 * This builds an event with information based on its input.
		 * @param input_name The name of the event.
		 * @param input_date The date of the event.
		 * @param input_create The creator of the event.
		 * @param input_id_number The id number associated with the event.
		 */
		Event(std::string input_name, std::string input_date, std::string input_creator, int input_id_number);
		/**
		 * The destructor.
		 * This should destroy any objects created by this.
		 */
		~Event();
		/**
		 * A getter method for the date.
		 * @return the date as a string.
		 */
		std::string get_date();
		/**
		 * A getter method for the event's name.
		 * @return the event's name as a string.
		 */
		std::string get_name();
		/**
		 * A getter method for the creator's name.
		 * @return the creator's name as a string.
		 */
		std::string get_creator();
		/**
		 * A getter method for the id number.
		 * @return the id number as an integer.
		 */
		int get_id_number();
	private:
		/**
		 * The date variable.
		 * This contains information regarding the YYYY/MM/DD of the event.
		 */
		boost::gregorian::date date;
		/**
		 * A string variable.
		 * This is the name of the event.
		 */
		std::string name;
		/**
		 * A string variable.
		 * This is the name of the creator.
		 */
		std::string creator;
		/**
		 * An integer variable.
		 * This is the identifer number assigned to an event.
		 */
		int id_number;
};

#endif
