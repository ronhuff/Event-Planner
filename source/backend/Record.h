#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <list>

/**
 * The Record class. This file structure stores information regarding a timeslot's attendees.
 */

class Record{
	public:
	
		/**
		 * Class default Constructor, this method should not be call.
		 */
		Record();
	
		/**
		 * Class Constructor
		 * @param t time block string
		 */
		Record(std::string t);
	
		/**
		 * Class Destructor, this method will delete class member userlist
		 */
		~Record();
	
		/**
		 * This method will add a user id into the class member userlist.
		 * @param uid username string
		 * @post add user to class member userlist.
         */
		void addUser(std::string uid);
    
    	/**
         * This method will remove a certain user from the class member userlist.
         * @param uid username string
         * @post remove user from class member userlist
         */
		void removeUser(std::string uid);
    
    	/**
         * This method will return class member userlist when it been called.
         * @return userlist list.
         */
		std::list<std::string> getUserList();
    
    	/**
         * This method will return calss member time.
         * @return time block string
         */
		std::string getTime();
	private:
		/**This string stores the time at this timeslot.*/
		std::string time; 
		/**This list of strings stores the users at this time slot.*/
        std::list<std::string> userList; 
};

#endif
