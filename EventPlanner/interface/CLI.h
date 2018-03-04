#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "../backend/Executive.h"
#include "CLIInput.h"
#include "../backend/TaskList.h"
#include "../backend/Task.h"
#include "../backend/User.h"
#include "../backend/Event.h"
#include "../backend/Date.h"
#include "../backend/Executive.h"

class Event;
class Executive;

class CLI{
    private:
        //Executive exec;
        CLIInput input;
        enum EventSet{all, attending, created};
        bool longtime;
        bool loggedin;
        bool quit;

	    /**
		 * Helper method for checking time constraints.
		 * @pre: a call is made to CLI::newEvent()
		 * @post: none
		 * @return: bool true if no time violations, else false.
		 */
		bool checkTime(std::string stime, std::string etime);
    public:

		std::shared_ptr<Executive> m_execObj;

		CLI(std::shared_ptr<Executive>);

        /**
	     * Default constructor
	     * @pre: none
	     * @post: Variables are set to default values
	     * @return: none
	     */
        CLI();
        /**
	     * Retriever method for user_name member.
	     * @pre: none
	     * @post: none
	     * @return: none
	     */
        void run();
    private:
        /**
	     * The menu that the user sees after they have logged in.
	     * @pre: User is logged in
	     * @post: none
	     * @return: none
	     */
        void menu();
        /**
	     * Allows the user to change programs settings
	     * @pre: none
	     * @post: none
	     * @return: none
	     */
        void options();
        /**
	     * Verifies user exists and logges them in
	     * @pre: none
	     * @post: User is logged in
	     * @return: none
	     */
        void login();
        /**
	     * Logs the user out of the application
	     * @pre: none
	     * @post: User is logged out
	     * @return: none
	     */
        void logout();
        /**
	     * Gives new users the ability to create an account
	     * @pre: none
	     * @post: new user is created
	     * @return: none
	     */
        void newAccount();
        /**
	     * Shows a list of events
         * @param int - the starting index of the set of events
	     * @pre: none
	     * @post: none
	     * @return: none
	     */
        void listEvents();
        /**
	     * Allows for the creation of a new event by the user
	     * @pre: none
	     * @post: new event is created
	     * @return: none
	     */
        void newEvent() throw(std::exception);
        /**
	     * Allows a user to view a specific event
         * @param int - the unique identifier of the event
	     * @pre: none
	     * @post: none
	     * @return: none
	     */
        void viewEvent(int);
        /**
	     * Allows user to set availability for the event
         * @param int - the unique identifier of the event
	     * @pre: user is not the creator
	     * @post: availability set
	     * @return: none
	     */
        void setAvailability(int);
        /**
	     * Allows users to view availabilities for an event
         * @param int - the unique identifier of the event
	     * @pre: none
	     * @post: none
	     * @return: none
	     */
        void viewAvailability(int);
        /**
	     * Converts 24 hour formatting to 12 hour formatting.
         * @param std::string - the unique identifier of the event
	     * @pre: none
	     * @post: none
	     * @return: A 12 hour format version of the input string.
	     */
        std::string to12Hour(std::string);

		/**
		* Appends a zero to the end of a time string if it needs it(e.g. 13:00 instead of 13:0)
		* @param std::string - The string containing the time to be evaluated.
		* @pre: A time parameter is in local scope and we know it's length <5 (this function does NOT correct strings with greater length but will disregard them.)
		* @post: If necessary, a single zero is appended to the time. If other errors, no action taken.
		* @return: std::string - The time either with a zero appended or in it's original state when passed in.
		*/
		std::string zeroAppender(std::string time) throw(std::logic_error);
};