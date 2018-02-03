#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include "UserList.h"
#include "Event.h"
#include "Record.h"
#include <fstream>
#include <string>

class Executive{
	public:
		/**
		 * The empty constructor. 
		 * This builds the Executive class.
		 */
		Executive();
		/**
		 * The empty constructor. 
		 * This destroys the Executive class.
		 */
		~Executive();
		/**
		 * The getter method of the event num. 
		 * This gets a number to assign to a new event and increments it.
		 */
		int get_event_num();
		/**
		 * This method creates an event. 
		 * @param name The name of the event.
		 * @param date The date of the event.
		 * @return true if the event was created, false otherwise.
		 */
		bool generate_event(std::string name, std::string date);
		/**
		 * This method removes an event. 
		 * @param event_id The id of the event to be deleted.
		 * @return true if the event was deleted, false otherwise.
		 */
		bool delete_event(int event_id);
		
		void write_user(std::string user_name);
	private:
		User current_user;
		int event_num;
		//List of users
		//List of events
};

#endif
