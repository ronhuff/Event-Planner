#ifndef EVENT_H
#define EVENT_H

#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>
#include "Record.h"
#include "User.h"
#include <exception>

/**
 * Event Class. 
 * The class encapsulates the basic details of an event and contains a reference to its attendence record.
 */

class Event{
	public:
		/**
		 * The empty constructor.
		 * This builds an empty event and is not intended for use.
		 * @pre None.
		 * @post Creates a completely empty event.
		 */
		Event();
		/**
		 * The constructor that takes 4 arguments. 
		 * This builds an event with information based on its input.
		 * @param input_name The name of the event. 
		 * @pre None.
		 * @post Creates an empty event using parameters
		 * @param input_date The date of the event.
		 * @param input_create The creator of the event.
		 * @param input_id_number The id number associated with the event.
		 * @throw std::logic_error This error occurs whenever an event is put into a holiday.
		 */
		Event(std::string input_name, std::string input_date, std::string input_creator, int input_id_number);
		/**
		 * The destructor.
		 * @pre Event exists.
		 * @post Destroys this Event.
		 * This should destroy any objects created by this.
		 */
		~Event();
		/**
		 * A getter method for the date.
		 * @pre Event exists.
		 * @post N/A.
		 * @return the date as a string.
		 */
		std::string get_date();
		/**
		 * A getter method for the event's name.
		 * @pre Event exists.
		 * @post N/A.
		 * @return the event's name as a string.
		 */
		std::string get_name();
		/**
		 * A getter method for the creator's name.
		 * @pre Event exists.
		 * @post N/A.
		 * @return the creator's name as a string.
		 */
		std::string get_creator();
		/**
		 * A getter method for the id number.
		 * @pre Event exists.
		 * @post N/A.
		 * @return the id number as an integer.
		 */
		int get_id_number();
		/**
		 * An operator that compares this event's date with another's date.
		 * @pre Event exists and rhs exists.
		 * @post N/A.
		 * @param rhs The value to be compared with.
		 * @return true if the event happens after or on the same day as rhs.
		 */
		bool operator>=(Event rhs);
		/**
		 * An operator that compares this event's date with another's date.
		 * @pre Event exists and rhs exists.
		 * @post N/A.
		 * @param rhs The value to be compared with.
		 * @return true if the event happens before or on the same day as rhs.
		 */
		bool operator<=(Event rhs);
		/**
		 * An operator that compares this event's date with another's date.
		 * @pre Event exists and rhs exists.
		 * @post N/A.
		 * @param rhs The value to be compared with.
		 * @return true if the event happens after rhs.
		 */
		bool operator>(Event rhs);
		/**
		 * An operator that compares this event's date with another's date.
		 * @pre Event exists and rhs exists.
		 * @post N/A.
		 * @param rhs The value to be compared with.
		 * @return true if the event happens before rhs.
		 */
		bool operator<(Event rhs);
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
		 * A User variable.
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
