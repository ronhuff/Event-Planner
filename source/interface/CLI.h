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
        void run();
    private:
        void menu();
        void options();
        void login();
        void logout();
        void newAccount();
        void listEvents(EventSet, int);
        void newEvent();
        void viewEvent(int);
        void setAvailability();
        void viewAvailability();
};

#endif
