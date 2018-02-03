#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include "Event.h"
#include "Record.h"
#include <fstream>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>

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
		 * This method creates an event and generates files representing it. 
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
		/**
		 * An enum representing the various information types that are saved. 
		 */
		enum DataFile{
			df_event,	/**< Represents Event text files. */
			df_user		/**< Represents User text files. */
		};
		/**
		 * This helper method verifies if a file exists. 
		 * @param type A value from the DataFile enum
		 * @param identifer The variable part of the file's name that we are trying to verify, like the "23" in "record_23.txt" or "Daniel" in "user_Daniel.txt"
		 * @return true if the file in question exists, false otherwise.
		 */
		bool does_file_exist(DataFile type, std::string identifer);
	
	
		User current_user;
		int event_num;
		/**
		 * This is a vector of Events.
		 * This contains all Events that are available.
		 */
		std::vector<Event>* event_list;
		//List of users
};

#endif
