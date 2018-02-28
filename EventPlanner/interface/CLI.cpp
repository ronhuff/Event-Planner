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
    std::cout << "\nPlease choose from the following options:\n\n" <<
                 "1) View Events List\n" <<
				 "2) Create New Event\n"
                 "3) Manage Settings\n" <<
                 "4) Logout of Account\n" <<
                 "5) Exit Application\n";
	std::cout << "Selection: ";
	int action;
	std::cin >> action;
	while (action != 1 && action != 2 && action != 3 && action != 4 && action != 5) {
		
		std::cin.clear(); // unset failbit
		std::cin.ignore(numeric_limits<streamsize>::max(), '\n'); // skip bad input
		std::cout << "Please simply choose one of the options (1-5) and press enter/return.\n";
		std::cout << "\nSelection: ";
		std::cin >> action;
	}

    if(action == 1){
        listEvents(0);

    }else if(action == 2){
		try {
			newEvent();
		}
		catch (std::exception& e) {
			std::cout << e.what();
		}
    }else if(action == 3){
        options();
    }else if(action == 4){
        logout();
        login();
    }else if(action == 5){
        quit = true;
    }else{
        std::cout << "Invalid command entered.\n";
    }
}

void CLI::options(){
    std::string choice;
    std::cout << "Here you may change the settings. To toggle a setting simply enter its name, to go to the main menu enter \"menu.\"\n";
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
    std::string username = "";
    bool validIdentifier = false;

    while(!validIdentifier){
        name = input.getLine("Enter your full name: ");
        username = input.getString("Enter your prefered username: ");

        if(username != "CreateAccount" && username != "Quit"){
            validIdentifier = exec.createUser(username, name);
        }

        if(!validIdentifier){
            std::cout << "You may not use that username.\n";
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
    }else if(choice == "next" && first < size){
        listEvents(first + 25 );
    }else if(choice == "previous" && first >= 0){
        listEvents(first - 25);
    }
}

void CLI::newEvent(){
    int year = 0, month = 0, day = 0;
    int eventID;
    std::string date = "";
    std::cout << "You are creating a new event.\nTo get started with, we need an event title.\n";
    std::string name = input.getLine("Enter event name: ");

    std::cout << "Next there needs to be a date for the event.\n";
    bool validDate = false;
    while(!validDate){
        year = input.getInteger("Enter the year: ", 9999, 1400);
        month = input.getInteger("Enter the month integer: ", 12, 1);
        day = input.getInteger("Enter the day: ", 31, 1);

        date = std::to_string(year) + "/" + std::to_string(month) + "/" + std::to_string(day);
        try{
            eventID = exec.generateEvent(name, date);
            validDate = true;
        }catch(std::exception& e){
            std::cout << "The date you have entered is invalid.\n";
        }
    }

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
    exec.writeRecord(eventID, exec.createRecordList(times));
    delete times;
}

void CLI::viewEvent(int i){
    try{
        Event* e = exec.getEventByID(i);
        std::cout << "Title:\t\t" << e->getName() << "\n" <<
                     "Creator:\t" << e->getCreatorRealName() << "\n" <<
                     "Date:\t\t" << e->getDate() << "\n";

        std::string choice;
        while(choice != "menu"){
            if(exec.getCurrentUser()->getUserName() != e->getCreatorUserName()){
                std::cout << "You may set your availability buy entering \"set\".\n";
            }
            std::cout << "You may view users availability by entering \"view\"\n" <<
                         "Return to menu by entering \"menu\"\n";
            choice = input.getString("Enter your choice: ");

            if(choice == "set" && exec.getCurrentUser()->getUserName() != e->getCreatorUserName()){
                setAvailability(i);
            }else if(choice == "view"){
                viewAvailability(i);
            }
        }

        delete e;
    }catch(std::exception& e){
        std::cout << "Invalid event number.\n";
    }
}

void CLI::setAvailability(int eid){
    std::list<Record>* eventRecords = exec.readRecord(eid);
    std::cout << "For each of the following times enter 'y' or 'n' to confirm or deny availablity.\n";

    for(auto i : *(eventRecords)){
        std::string slot;
        if(longtime){
            slot = i.getTime();
        }else{
            slot = to12Hour(i.getTime());
        }


        if(input.getCharacter(slot + " - ") == 'y'){
            exec.addUserTo(i.getTime(), eventRecords);
        }
    }

    exec.writeRecord(eid, eventRecords);
}

void CLI::viewAvailability(int eid){
    std::list<Record>* eventRecords = exec.readRecord(eid);
    Event* event = exec.getEventByID(eid);

    //Runs for each time slot
    for(auto i : *(eventRecords)){
        std::string slot;
        if(longtime){
            slot = zeroAppender(i.getTime());//here zeroAppender is taking the std::string parameter returned by i.getTime());

			//add zeroappend
        }else{
            slot = to12Hour(i.getTime());
        }

        std::cout << "Time: " << slot << "\nAtendees: ";

        //Shows all attending users
        std::list<std::string> users = i.getUserList();
        std::cout << event->getCreatorRealName();
        for(auto i : users){
            try{
                User* temp = exec.getUser(i);
                std::cout << ", " << temp->getRealName();
                delete temp;
            }catch(std::exception& e){}
        }
        std::cout << std::endl;
    }

    delete event;
    delete eventRecords;
}
std::string CLI::to12Hour(std::string input){
	std::size_t delimiter = input.find_first_of(":");
	int hour = std::stoi(input.substr(0,delimiter));
	if(hour == 12){
		return (input + " PM");
	}else if(hour > 12){
		hour -= 12;
		return (std::to_string(hour) + std::string(input.substr(delimiter)) + " PM");
	}else{
		return (input + " AM");
	}
}

bool CLI::checkTime(std::string stime, std::string etime){
//HH:MM
//Convert these values to Numbers to make math easier.

int startHr = stoi(stime.substr(0, 2));
int startMin = stoi(stime.substr(3, 2));
int endHr = stoi(etime.substr(0, 2));
int endMin = stoi(etime.substr(3, 2));

std::cout << "stime = " + stime + " etime = " + etime + "\n";

if (((startMin % 20 == 0) && (endMin % 20 == 0)) == false){
	std::cout << "startMin || endMin not on timeslot  *DBG\n";
	std::cout << "Meeting must begin and end on the hour or 20 minute increments thereof.\n";
	return(false);
}

//Check for overnight
if ((startHr >= 0 && startHr < 5) || (endHr > 0 && endHr <= 5)){
	if (endHr == 5 && startHr == 5 && (endMin > startMin)) return(true);
	else {
		std::cout << "Error: Meeting Start || End overnight. *DBG \n";
		std::cout << "Meetings may not occur between 12:00am - 5:00am\n";
		return(false);
	}
}
else if ((startHr >= 12 && startHr < 13) || ((endHr >= 12 && endMin > 0) && endHr <= 13)){
	std::cout << "Error: Meeting Start || End lunch. *DBG \n";
	std::cout << "Meetings may not occur between 12:00pm - 1:00pm\n";
	return(false);
}

//Check if meeting would span the restricted overnight period.
//NOTE: Even though they can choose only one day, a user could attempt to schedule
//      an end time in the AM even though their begin time is PM. This will account for that.
//      Also, we can use >= 13 because we already checked for meetings that span lunch.
else if (startHr >= 13 && endHr < 13){
	std::cout << "Meetings must begin and end on the same calendar day.\n";
	return(false);
}

//Check if meeting would span the restricted lunch period.
else if ((startHr >= 5 && startHr < 12) && endHr > 13){
	std::cout << "Hour values indicate that the meeting would go through lunch.\n";
	std::cout << "Meetings may not extend through lunch.\n";
	return(false);
}

//Check to assure that meeting will start and end on the same calendar day.
//Perhaps redundant now but it's not broke so we won't fix it yet.
if (etime < stime){
	std::cout << "Meeting may not extend into next calendar day.\n";
	std::cout << "User attempted to set end time for calendar day that is not same as start time calendar day.\n";
	return (false);
}
std::cout << "Time does not appear to conflict with time constraints.\n";
return (true);
}


std::string CLI::zeroAppender(std::string time) throw(std::logic_error)
{
	//in this case, the time must be in format "HH:MM" + "XYZ, etc." so disregard for this method.
	//Or the time is in format "HH:" where for some reason the time is completely invalid.}
	/*std::cout << "time param = " + time + " time.length() = " << time.length() << "\n";*/
	if (time.length() == 4 && time[1] == ':')
	{
		/*std::cout << "Entered First If Block.\n";*/
		//This will ensure that format read in as H:MM will not be reformatted...
		/*std::cout << "Entered next If time[time.length() - 1] = " + time[time.length() - 1] + '\n';
		std::cout << "time[time.length() - 2] = " + time[time.length() - 2] << '\n';
		std::cout << (time[3] == '0');*/
		return (time.substr(0, 3) + "0");
	}
	if (time.length() > 5 || time.length() < 4) {
		if (time.length() < 4) {
			//throw std::logic_error("Unable to format the time, timeslot somehow given with length < 4 must debug.");
			return(time);
		}
		return(time);
	}
	else if (time.length() == 4)
	{
		return (time + "0");
	}
	else
	{
		//std::cout << "time param = " + time + " time.length() = " << time.length() << "\n";
		//std::cout << "ERROR, zeroAppender took no action and returned.\n";
		return(time);
	}
}
