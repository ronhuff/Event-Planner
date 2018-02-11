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
		 * @pre None.
		 * @post Creates an empty event using parameters
		 * @param inputName The name of the event. 
		 * @param inputDate The date of the event.
		 * @param inputCreatorUsername The creator's user name of the event.
		 * @param inputIDNum The id number associated with the event.
		 * @throw std::logic_error This error occurs whenever an event is put into a holiday.
		 */
		Event(std::string inputName, std::string inputDate, std::string inputCreatorUsername, int inputIDNum);
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
		std::string getDate();
		/**
		 * A getter method for the event's name.
		 * @pre Event exists.
		 * @post N/A.
		 * @return the event's name as a string.
		 */
		std::string getName();
		/**
		 * A getter method for the creator's real name.
		 * @pre Event exists.
		 * @post N/A.
		 * @return the creator's real name as a string.
		 */
		std::string getCreatorRealName();
		/**
		 * A getter method for the creator's user name.
		 * @pre Event exists.
		 * @post N/A.
		 * @return the creator's user name as a string.
		 */
		std::string getCreatorUserName();
		/**
		 * A getter method for the id number.
		 * @pre Event exists.
		 * @post N/A.
		 * @return the id number as an integer.
		 */
		int getIDNumber();
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
		 * A variable representing the username of the creator.
		 * This is the name of the creator.
		 */
		std::string creatorUserName;
		/**
		 * A variable representing the realname of the creator.
		 * This is the name of the creator.
		 */
		std::string creatorRealName;
		/**
		 * An integer variable.
		 * This is the identifer number assigned to an event.
		 */
		int idNum;
};

#endif
