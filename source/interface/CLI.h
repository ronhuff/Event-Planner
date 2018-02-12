#ifndef CLI_H
#define CLI_H

#include <iostream>
#include <string>
#include "../backend/Executive.h"
#include "CLIInput.h"

class CLI{
    private:
        Executive exec;
        CLIInput input;
        enum EventSet{all, attending, created};
        bool longtime;
        bool loggedin;
        bool quit;
    public:
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
        void listEvents(int);
        /**
	     * Allows for the creation of a new event by the user
	     * @pre: none
	     * @post: new event is created
	     * @return: none
	     */
        void newEvent();
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
};

#endif
