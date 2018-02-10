#ifndef CLI_H
#define CLI_H

#include <iostream>
#include <string>
#include "../backend/Executive.h"

class CLI{
    private:
        Executive exec;
        enum EventSet{all, attending, created};
    public:
        void run();
    private:
        void login();
        void logout();
        void newAccount();
        void listEvents(EventSet, int);
        void newEvent();
        void viewEvent(int);
        void setAvailability();
};

#endif
