#include "CLI.h"

CLI::CLI(){
    longtime = true;
    loggedin = false;
    quit = false;
}

void CLI::run(){
    login();

    while(!quit){
        menu();
    }
    std::cout << "Have a wonderful day.\n";
    logout();
}

void CLI::menu(){
    std::cout << "You have a choice to make. Choose one of the following actions by typing in the command.\n" <<
                 "" <<
                 "View Events List:\t\"events\"\n" <<
                 "Create New Event:\t\"create\"\n"
                 "Manage Settings:\t\"options\"\n" <<
                 "Logout of Account:\t\"logout\"\n" <<
                 "Exit Application:\t\"exit\"\n";
    std::string action = input.getString("What would you like to do?: ");

    if(action == "events"){
        listEvents(all, 0);
    }else if(action == "create"){
        newEvent();
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

void CLI::options(){
    std::string choice;
    std::cout << "Here you may change the settings. To toggle a setting simply enter its name, to go to the main menu enter menu.\n";
    while(choice != "menu"){
        if(longtime){
            std::cout << "clock: 24 Hour Clock\n";
        }else{
            std::cout << "clock: 12 Hour Clock\n";
        }

        choice = input.getString("Make a choice: ");

        if(choice == "clock"){
            (longtime) ? longtime = false : longtime = true;
        }
    }
}

void CLI::login(){

    while(!loggedin){
        std::string identifier;
        std::cout << "You need to login to continue.\nIf you do not have an account enter \"CreateAccount\".\nTo exit enter \"Quit\".\nEnter your username: ";
        std::cin >> identifier;

        if(identifier == "CreateAccount"){
            newAccount();
        }else if(identifier == "Quit"){
            quit = true;
            return;
        }else if(exec.setCurrentUser(identifier)){
            loggedin = true;
        }else{
            std::cout << "No valid username input.\n";
        }
    }
}

void CLI::logout(){
    loggedin = false;
}

void CLI::newAccount(){
    std::string name;
    std::string username;
    bool validIdentifier = false;

    while(!validIdentifier){
        name = input.getLine("Enter your full name: ");
        username = input.getString("Enter your prefered username: ");

        validIdentifier = exec.createUser(username, name);
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

        date = std::to_string(year) + "/" + std::to_string(month) + "/" + std::to_string(day);
    }while(!exec.generateEvent(name, date));
}

void CLI::viewEvent(int i){
    try{
        Event* e = exec.getEventByID(i);
        std::cout << "Title:\t" << e -> getName() <<
                     "Creator:\t" << e -> getCreatorRealName();
    }catch(std::exception& e){
        std::cout << "Invalid event number.\n";
    }
}

void setAvailability(){

}

void viewAvailability(){

}
