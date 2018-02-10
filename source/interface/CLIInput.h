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
    CLIInput();
    string getLine(string message);
    string getString(string message);
    char getCharacter(string message);
    double getDouble(string message);
    int getInteger(string message);
    int getInteger(string message, int max, int min);
};

#endif
