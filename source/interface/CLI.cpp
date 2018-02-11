#include "CLI.h"

CLI::CLI(){
    loggedin = false;
    quit = false;
}

void CLI::run(){
    login()

    while(!quit){
        menu();
    }
    std::cout << "Have a wonderful day.\n";
    logout();
}

void CLI::menu(){
    std::cout << "You have a choice to make. Choose one of the following actions by typing in the command.\n";
                 "" <<
                 "Do Something:\t\t\"\"" <<
                 "Manage Settings:\t\"options\"\n" <<
                 "Logout of Account:\t\"logout\"\n" <<
                 "Exit Application:\t\"exit\"\n"; <<
    std::string action = input.getString("What would you like to do?: ");

    if(action == ""){

    }else if(action == "options"){
        options();
    }else if(action == "logout"){
        logout();
        login();
    }else if(action == "exit"){
        quit = true;
    }else{
        std::cout << "Invalid command entered.\n";
    }
}

/*Logs a user into the application*/
void CLI::login(){

    while(!loggedin){
        std::string identifier;
        std::cout << "You need to login to continue. If you do not have an account enter \"CreateAccount\".\nEnter your username: ";
        std::cin >> identifier;

        if(identifier == "CreateAccount"){
            newAccount();
        }else if(exec->setCurrentUser(identifier)){
            loggedin = true;
        }else{
            std::cout << "No valid username input.\n";
        }
    }
}

void logout(){
    loggedin = false;
}

void CLI::newAccount(){
    std::string name;
    std::string username;
    bool validIdentifier = false;

    while(!validIdentifier){
        std::cout << "Enter your full name: ";
        std::cin >> name;

        std::cout << "Enter your prefered username: ";
        std::cin >> username;


    }
}

void CLI::listEvents(EventSet set, int first){
    switch(set){
        case attending:

            break;
        //case created:

        //    break;
        default:

            break;
    }
}

void CLI::newEvent(){
    int year = 0, month = 0, day = 0;
    std::string date = "";
    std::cout << "You are creating a new event.\nTo get started with, we need an event title.\n";
    std::string name = input.getString("Enter event name: ");

    std::cout << "Next there needs to be a date for the event.\n";
    do{
        if( month != 0 && day != 0){
            std::cout << "An invalid date was entered.\n";
        }

        year = input.getInteger("Enter the year: ", 9999, 1400);
        month = input.getInteger("Enter the month: ", 12, 1);
        day = input.getInteger("Enter the day: ", 31, 1);

        date = std::toString(year) + "/" + std::toString(month) + "/" + std::toString(day);
    }while(!exec.generateEvent(name, date));
}

void viewEvent(int i){
    try{
        Event e = getEventByID(i);
    }catch(Excption e){
        std::cout << "Invalid event number.\n";
    }

    std::cout << "Title:\t" << e.getName() <<
                 "Creator: " << e.getCreator().getName();
}
