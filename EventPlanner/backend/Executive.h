#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include "Event.h"
#include "Record.h"
#include "User.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/filesystem.hpp>


/**
 * The Executive class. This deals with file IO and class interactions in the backend.
 */
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
		int getEventNum();
		/**
		 * This method creates an event and generates files representing it.
		 * @param name The name of the event.
		 * @param date The date of the event.
		 * @pre Executive exists.
		 * @post A new event is created in text files and in memory.
		 * @return the id of the newly created event.
		 * @throw std::logic_error if the event is invalid
		 */
		int generateEvent(std::string name, std::string date);
		/**
		 * This method removes an event.
		 * @param event_id The id of the event to be deleted.
		 * @pre Executive exists and the event in question with the id exists.
		 * @post An event is deleted in text files and in memory.
		 * @return true if the event was deleted, false otherwise.
		 */
		bool deleteEvent(int event_id);
		/**
		 * This method returns a reference to the event list.
		 * @pre Executive exists.
		 * @post No changes occur.
		 * @return a reference to the event list.
		 */
		std::vector<Event>* getEventList();

		/**
		 * Method which sets the current_user variable based on uid
		 * If a matching file "user_<uid>.txt" is found, then the information
		 * contained in that file is written to the *(current_user)
		 * @param uid The username to be searched for
		 * @pre: uid is a valid string
		 * @post: current_user is set with appropiate parameters if file is found; is set to empty otherwise
		 * @return: bool -- TRUE if user_<uid> is found, FALSE otherwise
		 */
		bool setCurrentUser(std::string uid);

		/**
		 * Method which re-writes information about current_user back
		 * out to it's file
		 * @pre: current_user has a nonempty user_name
		 * @post: user_<current_user -> user_name>.txt is updated with most recent data
		 * @return: TRUE if operation completed successfully, FALSE otherwise
		 */
		bool writeCurrentUser();

		/**
		 * Retriever method which returns a pointer to current_user
		 * @pre: none
		 * @post: none
		 * @return: User* -- pointer to current_user member
		 */
		User* getCurrentUser();

		/**
		 * This method will add current user to a certain time block
		 * @param time the time block
		 * @param List the pointer to the record list
		 * @pre the record list must valid
		 * @return: bool -- TRUE if the user have be added to the record
		 */
		bool addUserTo(std::string time, std::list<Record>* List);

		/**
		 * This method will remove current user from a certain time block
		 * @param time the time block
		 * @param List the pointer to the record list
		 * @pre the record list must valid
		 * @return: bool -- TRUE if the user have be removed from the record
		 */
		bool removeUserFrom(std::string time, std::list<Record>* List);

		/**
		 * This method should be called when creating a new event
		 * @param timeList a list of time blocks
		 * @post timeList will be deleted
		 * @return a list of Record objects
		 */
		std::list<Record>* createRecordList(std::list<std::string>* timeList);
		/**
		 * This method will return a list of username which are all users attending the given event.
		 * @param eid a event id
		 * @return a list of username
		 */
		std::list<std::string>* getAttending(int eid);
		/**
		 * This method returns a list of events created by a user
		 * @param u The user
		 * @post NA
		 * @return A list of events created by the user parameter
		 */
		std::list<Event>* getEventByCreator(User u);

		/**
		 * This method will return a pointer to a User whose information
		 * will be extracted from a user file with identifier uid.
		 * @pre uid is a valid string; ./data/users/user_"uid".txt exists
		 * @post none
		 * @param uid The username of the user you want.
		 * @return A pointer to a user with information contained in the user_uid text file.
		 * @throw std::logic_error if the user in question does not exist in files.
		 */
		User* getUser(std::string uid);
		/**
		 * This method returns a pointer to an event based on eid.
		 * @pre eid is an int; ./data/users/info_\<eid\>.txt exists
		 * @post none
		 * @return A pointer to an event with information contained in info_<eid>.txt
		 * @throw Error if info_<eid>.txt does not exist
		 */
		Event* getEventByID(int eid);

        /**
         * This method read through a existing record file and create a list pointer of record.
         * @param event_id the event id
         * @pre the record file should exist.
         * @post none
         * @return a list of Record
         */
        std::list<Record>* readRecord(int event_id);

        /**
         * This method will write a Record file of a given list of Record.
         * @param eid the event id
         * @param List the list of Record
         * @post the List will be deleted and saved in files.
         */
        void writeRecord(int eid, std::list<Record>* List);

        /**
         * This method will remove a Record file.
         * @param eid the event id
         * @pre the file should exist
         * @post remove the file
         */
        bool removeRecord(int eid);

		/**
		 * This method creates a user and writes basic information
		 * back out to a file.
		 * @param uid user_name for the new user
		 * @param pnm real_name for the new user
		 * @pre user_<uid>.txt does not exist in the data/user directory
		 * @post user_<uid>.txt is created in the data/user directory
		 * @return TRUE if the file user_<uid> does not already exist, FALSE otherwise
		 */
		bool createUser(std::string uid, std::string pnm);
		/**
		 * This method will check if current user is attending a event.
		 * @param eid The event id.
		 * @post none
		 */
		bool isAttending(int eid);

		/**
		 * This helper method sorts the event list by dates.
		 * @pre Executive exists
		 * @post N/A, No changes occur.
		 */
		void sortEventList();

		/**
		* This method simply returns eventnum.
		*
		*/
		int whatIsEventNum();

	private:
		/**
		 * An enum representing the various information types that are saved.
		 */
		enum DataFile{
			df_event,		/**< Represents Event text files. */
			df_record,		/**< Represents Event record files. */
			df_user,		/**< Represents User text files. */
			df_eventList	/**< Represents the event list text file. */
		};
		/**
		 * This helper method verifies if a file exists.
		 * @pre Executive exists
		 * @post N/A, No changes occur.
		 * @param type A value from the DataFile enum
		 * @param identifer The variable part of the file's name that we are trying to verify, like the "23" in "record_23.txt" or "Daniel" in "user_Daniel.txt"
		 * @return true if the file in question exists, false otherwise.
		 */
		bool doesFileExist(DataFile type, std::string identifer = "");
		/**
		 * This helper method rebuilds events given a text file.
		 * @pre The file should should actually exist.
		 * @post The event information in the file is made into an event and put into the event_list.
		 * @param filename The file name of the event information text file.
		 */
		void rebuildEvent(std::string filename);
		/**
		 * This helper method should get the file name of data file given its parameters.
		 * @pre Executive exists
		 * @post N/A, No changes occur.
		 * @param type A value from the DataFile enum
		 * @param identifer The part of the name of the file that is unique to a specific file
		 * such as the number in info_\<event num\> or the username in user_\<username\>.
		 * @return filename The file name of the event information text file.
		 */
		std::string getFileName(DataFile type, std::string identifer = "");

		/**
		 * Converts a csv string of integer values to an integer list
		 * @param int_list  List to store the values to
		 * @param int_string  csv string of integer values
		 * @pre: int_string is a csv list of integer values
		 * @post: int_list contains integer converted values contained in int_string
		 * @return: none
		 */
		void storeIntsFromString(std::list<int> &int_list, std::string int_string);

		/**
		 * User pointer which points to information about the User object of the current session
		 */
		User* currentUser;

		/**
		 * Internal running tally of event identifiers; should make provisions so that no two
		 * events get assigned the same event identifier
		 */
		int eventNum = 0;

		/**
		 * This is a vector of Events.
		 * This contains all Events that are available.
		 */
		std::vector<Event>* eventList;



};

#endif
