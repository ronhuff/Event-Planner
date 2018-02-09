#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include "Event.h"
#include "Record.h"
#include "User.h"
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
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
		/**
		 * This method returns a reference to the event list. 
		 * @pre Executive exists.
		 * @post No changes occur.
		 * @return a reference to the event list.
		 */
		std::vector<Event>& get_event_list();
		
		/**
		 * Method which sets the current_user variable based on uid
		 * If a matching user_name is in the file user.txt, then
		 * current_user will point to a user with the respective information
		 * otherwise, will point to a default User (see User::User())
		 * @param std::string -- uid: The username to be searched for
		 * @pre: uid is a valid string; user.txt exists in the appropiate location
		 * @post: current_user = returned
		 * @return: bool -- TRUE if uid is found in user.txt, FALSE otherwise
		 */
		bool setCurrentUser(std::string uid); 
		
			
	private:
		/**
		 * An enum representing the various information types that are saved. 
		 */
		enum DataFile{
			df_event,		/**< Represents Event text files. */
			df_record,		/**< Represents Event record files. */
			df_user,		/**< Represents User text files. */
			df_event_list	/**< Represents the event list text file. */
		};
		/**
		 * This helper method verifies if a file exists. 
		 * @pre Executive exists
		 * @post N/A, No changes occur.
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
		/**
		 * This helper method should get the file name of data file given its parameters.
		 * @pre Executive exists
		 * @post N/A, No changes occur.
		 * @param filename The file name of the event information text file.
		 */
		std::string get_file_name(DataFile type, std::string identifer = "");
		/**
		 * This helper method sorts the event list by dates.
		 * @pre Executive exists
		 * @post N/A, No changes occur.
		 * @param filename The file name of the event information text file.
		 */
		void sort_event_list();

		/**
		 * Searches the user file for uid
		 * @param std::string uid -- username to search for
		 * @pre: uid is a valid string; the user file exists
		 * @post: none
		 * @return: Returns TRUE if uid is found; false otherwise
		 */
		bool searchUserFile(std::string uid);
		
		/**
		 * User pointer which points to information about the User object of the current session
		 */
		User* current_user;

		/**
		 * Internal running tally of event identifiers; should make provisions so that no two
		 * events get assigned the same event identifier
		 */
		int event_num = 0;

		/**
		 * This is a vector of Events.
		 * This contains all Events that are available.
		 */
		std::vector<Event>* event_list;
};

#endif
