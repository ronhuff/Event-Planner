/*****
* Object: CLI Input
* Description: Validates input received from the CLI
* Author: William Graham
* Modified: February 18, 2017
*****/

#ifndef CLIINPUT_H
#define CLIINPUT_H

#include <iostream>
#include <string>
#include <limits>

using namespace std;

class CLIInput{
    private:
        string stringIn;
        int integerIn;
        double doubleIn;
        char characterIn;
    public:
        /**
         * Command Line Input (CLI) Constructor
         * @pre: none
         * @post: none
         * @return: none
         */
        CLIInput();
        /**
	     * Obtains a line of input with a modifiable message
         * @param string message - prompt that lets the user know what to enter
	     * @pre: none
	     * @post: none
	     * @return: line of input as string
	     */
        string getLine(string message);
        /**
	     * Obtains all characters before new line or space
         * @param string message - prompt that lets the user know what to enter
	     * @pre: none
	     * @post: none
	     * @return: string of input
	     */
        string getString(string message);
        /**
	     * Obtains a character
         * @param string message - prompt that lets the user know what to enter
	     * @pre: none
	     * @post: none
	     * @return: character of input
	     */
        char getCharacter(string message);
        /**
	     * Obtains a double
         * @param string message - prompt that lets the user know what to enter
	     * @pre: none
	     * @post: none
	     * @return: a double that is input
	     */
        double getDouble(string message);
        /**
	     * obtains any integer
         * @param string message - prompt that lets the user know what to enter
	     * @pre: none
	     * @post: none
	     * @return: an integer that is input
	     */
        int getInteger(string message);
        /**
	     * Obtains an integer between min and max inclusive
         * @param string message - prompt that lets the user know what to enter
         * @param int max - the maximum value of the integer
         * @param int min - the smallest value of the integer
	     * @pre: none
	     * @post: none
	     * @return: an integer between min and max
	     */
        int getInteger(string message, int max, int min);
};

#endif
