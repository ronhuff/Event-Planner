#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include "Event.h"
#include "Record.h"
#include "User.h"
#include <fstream>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>

class Executive{
	public:
		/**
		 * The empty constructor. 
		 * This builds the Executive class.
		 * @pre None.
		 * @post Executive is created.
		 * If data and EventList.txt don't exist, they are created.
		 * Executive reads various files in data if they exist to recreate objects.
		 */
		Executive();
		/**
		 * The empty destructor. 
		 * This destroys the Executive class.
		 * @pre Executive exists.
		 * @post Executive is destroyed along with any objects it created.
		 */
		~Executive();
		/**
		 * The getter method of the event num.
		 * This gets a number to assign to a new event and increments it.
		 * @pre Executive exists.
		 * @post "event_num" is incremented prior to being returned. 
		 * @return The "event_num" .
		 */
		int get_event_num();
		/**
		 * This method creates an event and generates files representing it. 
		 * @param name The name of the event.
		 * @param date The date of the event.
		 * @pre Executive exists.
		 * @post A new event is created in text files and in memory. 
		 * @return true if the event was created, false otherwise.
		 */
		bool generate_event(std::string name, std::string date);
		/**
		 * This method removes an event. 
		 * @param event_id The id of the event to be deleted.
		 * @pre Executive exists and the event in question with the id exists.
		 * @post An event is deleted in text files and in memory.
		 * @return true if the event was deleted, false otherwise.
		 */
		bool delete_event(int event_id);
		
		void write_user(std::string user_name);
	private:
		/**
		 * An enum representing the various information types that are saved. 
		 */
		enum DataFile{
			df_event,		/**< Represents Event text files. */
			df_user,		/**< Represents User text files. */
			df_event_list	/**< Represents the event list text file. */
		};
		/**
		 * This helper method verifies if a file exists. 
		 * @param type A value from the DataFile enum
		 * @param identifer The variable part of the file's name that we are trying to verify, like the "23" in "record_23.txt" or "Daniel" in "user_Daniel.txt"
		 * @return true if the file in question exists, false otherwise.
		 */
		bool does_file_exist(DataFile type, std::string identifer = "");
		/**
		 * This helper method rebuilds events given a text file.
		 * @pre The file should should actually exist.
		 * @post The event information in the file is made into an event and put into the event_list.
		 * @param filename The file name of the event information text file.
		 */
		void rebuild_event(std::string filename);
	
		User current_user;
		int event_num = 0;
		/**
		 * This is a vector of Events.
		 * This contains all Events that are available.
		 */
		std::vector<Event>* event_list;
		//List of users
};

#endif
