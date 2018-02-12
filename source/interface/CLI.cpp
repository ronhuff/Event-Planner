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
        listEvents(0);
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
            longtime = (longtime) ? false : true;
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

        if(username != "CreateAccount" && username != "Quit"){
            validIdentifier = exec.createUser(username, name);
        }
    }
}

void CLI::listEvents(int first){
    std::vector<Event>* list = exec.getEventList();
    int size = list->size();
    for(int i = first; i < (first + 26) && i < size; i += 1){
        try{
            Event e = list->at(i);
            std::cout << std::to_string(e.getIDNumber()) << "\t" << e.getName() << "\t\t" << e.getDate() << "\t\t" <<e.getCreatorRealName() << "\n";
        }catch(std::exception& e){
            return;
        }
    }

    std::string choice;
    //Options
    std::cout << "Your choices are:\n\t\"view\" to view an event\n";
    if(first > 0 ){
        std::cout << "\t\"previous\" to go back in the list\n";
    }
    if(first + 25 < size){
        std::cout << "\t\"next\" to go forward in the list\n";
    }
    std::cout << "\t\"menu\" to go to the menu\n";

    //Make Choice
    choice = input.getString("Now make a choice: ");
    if(choice == "view"){
        viewEvent(input.getInteger("Enter the number of the event you want to view: "));
    }else if(choice == "next"){
        listEvents(first + 25 && first < size);
    }else if(choice == "previous" && first > 0){
        listEvents(first - 25);
    }
}

void CLI::newEvent(){
    int year = 0, month = 0, day = 0;
    std::string date = "";
    std::cout << "You are creating a new event.\nTo get started with, we need an event title.\n";
    std::string name = input.getLine("Enter event name: ");

    std::cout << "Next there needs to be a date for the event.\n";
    do{
        if( month != 0 && day != 0){
            std::cout << "An invalid date was entered.\n";
        }

        year = input.getInteger("Enter the year: ", 9999, 1400);
        month = input.getInteger("Enter the month integer: ", 12, 1);
        day = input.getInteger("Enter the day: ", 31, 1);

        date = std::to_string(year) + "/" + std::to_string(month) + "/" + std::to_string(day);
    }while(!exec.generateEvent(name, date));

    std::cout << "Finally there needs to be some times for the event. In the next section, simply enter 'y' or 'n' after each time.\n";

    std::list<std::string>* times = new std::list<std::string>();
    for(int i = 5; i < 24; i += 1){
        for(int j = 0; j < 59; j += 20){
            std::string slot = std::to_string(i) + ":" + std::to_string(j);

            //Is a time acceptable
            std::string accept;
            if(!longtime){
                if(i < 12){
                    accept = input.getString(slot + "AM - ");
                }else{
                    accept = input.getString(std::to_string(i - 12) + ":" + std::to_string(j) + "PM - ");
                }
            }else{
                accept = input.getString(slot + " - ");
            }


            if(accept == "y"){
                times->push_back(slot);
            }
        }
        if(i == 11){
            i += 1;
        }
    }
    exec.writeRecord(0, exec.createRecordList(times));
    delete times;
}

void CLI::viewEvent(int i){
    try{
        Event* e = exec.getEventByID(i);
        std::cout << "Title:\t" << e->getName() << "\n" <<
                     "Creator:\t" << e->getCreatorRealName() << "\n" <<
                     "Date:\t" << e->getDate() << "\n";

        std::string choice;
        while(choice != "menu"){
            if(exec.getCurrentUser()->getUserName() != e->getCreatorRealName()){
                std::cout << "You may set your availability buy entering \"set\".\n";
            }
            std::cout << "You may view users availability by entering \"view\"\n" <<
                         "Return to menu by entering \"menu\"\n";
            choice = input.getString("Enter your choice: ");

            if(choice == "set" && exec.getCurrentUser()->getUserName() != e->getCreatorRealName()){
                setAvailability(i);
            }else if(choice == "view"){
                viewAvailability(i);
            }else{
                std::cout << "No valid input.\n";
            }
        }

    }catch(std::exception& e){
        std::cout << "Invalid event number.\n";
    }
}

void CLI::setAvailability(int eid){

}

void CLI::viewAvailability(int eid){

}
