#include "CLI.h"

CLI::CLI(){
    exec = new Executive();
    loggedin = false;
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
        case created:

            break;
        default:

            break;
    }
}
