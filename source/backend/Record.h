#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <list>

class Record{
	public:
	
		/**
		 * Class default Constructor, this method should not be call.
		 */
		Record();
	
		/**
		 * Class Constructor
		 * @param time block string
		 */
		Record(std::string t);
	
		/**
		 * Class Destructor, this method will delete class member userlist
		 */
		~Record();
	
		/**
		 * This method will add a user id into the class member userlist.
		 * @param username string
		 * @post add user to class member userlist.
         */
		void addUser(std::string uid);
    
    	/**
         * This method will remove a certain user from the class member userlist.
         * @param username string
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
		std::string time;
        std::list<std::string> userList;
};

#endif
