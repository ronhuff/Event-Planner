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
		try {
			newEvent();
		}
		catch (std::exception& e) {
			std::cout << e.what();
		}
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

void CLI::newEvent() throw(std::exception) {
    int year = 0, month = 0, day = 0;
    int eventID;
    std::string date = "";
    std::cout << "You are creating a new event.\nTo get started with, we need an event title.\n";
    std::string name = input.getLine("Enter event name: ");

    std::cout << "Next there needs to be a date for the event.\n";
    bool validDate = false;
	while (!validDate) {
		std::cout << "Please enter a date in the format MM/DD/YYYY.\n";

		std::string date = "";
		std::cin >> date;

		while (!cin || date.length() != 10 || (date[2] != '/' || date[5] != '/')) {
			std::cout << "ERROR: Please enter a date in the format MM/DD/YYYY.\n";
			std::cin >> date;
		}
		std::string year = date.substr(6, 4);
		std::string day = date.substr(3, 2);
		std::string month = date.substr(0, 2);
		if (stoi(year) < 2018) {
			throw std::logic_error("No meetings permitted to be scheduled in the past.\n");
		}
		//New Year's Day.
		if (month == "01" && day == "01"){
			throw std::logic_error("No meetings permitted to be scheduled on New Year's Day.\n");
		}
		//Independence Day
		else if (month == "07" && day == "04"){
			throw std::logic_error("No meetings permitted to be scheduled on Independence Day.\n");
		}
		//Christmas Day
		else if (month == "12" && day == "25"){
			throw std::logic_error("No meetings permitted to be scheduled on Christmas Day.\n");
		}
		else {
			validDate = true;
		}
		date = year + "/" + month + "/" + day;
			eventID = exec.generateEvent(name, date);
			validDate = true;
    }
	
	std::cout << "Please enter a beginning time for your meeting. ";
	//BEGIN NEW CODE
	std::string stime = "";
	std::string etime = "";
	std::cout << "Enter start time in format HH:MM\n";
	std::cin >> stime;
	if (!cin)//This will still allow for bad input for now but at least it forces it to be a string for testing.
	{
		std::cout << "ERROR: Please enter the time in the format of HH:MM\n";
		std::cin >> stime;
	}
	std::cout << "Enter end time in format HH:MM\n";
	std::cin >> etime;
	if (!cin)
	{
		std::cout << "ERROR: Please enter the time in the format of HH:MM\n";
		std::cin >> etime;
	}
	while (!checkTime(stime, etime)) {
		std::cout << "Enter start time in format HH:MM\n";
		std::cin >> stime;
		if (!cin)
		{
			std::cout << "ERROR: Please enter the time in the format of HH:MM\n";
			std::cin >> stime;
		}
		std::cout << "Enter end time in format HH:MM\n";
		std::cin >> etime;
		if (!cin)
		{
			std::cout << "ERROR: Please enter the time in the format of HH:MM\n";
			std::cin >> etime;
		}
	}

	std::string startHr = stime.substr(0, 2);
	int startMin = stoi(stime.substr(3, 2));
	std::string endHr = etime.substr(0, 2);
	int endMin = stoi(etime.substr(3, 2));
	int TOTAL_MINS = ((stoi(endHr) - stoi(startHr)) * 60 + endMin - startMin);
	
	int timeslots = TOTAL_MINS / 20;
	
	//std::cout << "Total Minutes: " + TOTAL_MINS + " timeslots: " + (TOTAL_MINS / 20) << "\n";
	
	
	std::list<std::string>* times = new std::list<std::string>();
	
	//the first slot.
	std::string slot = startHr + ":" + std::to_string(endMin);
	endMin += 20;
	times->push_back(slot);
	for (int i = 1; i < timeslots; i++)
	{
		std::string slot = "";
		//etime.substr(3, 2) this returns the endmin string
		if (endMin >= 60) {
			endMin = 0;
			int hourInt = std::stoi(startHr);
			hourInt++;
			startHr = std::to_string(hourInt);
			slot = startHr + ":" + "00";
			endMin += 20;
		}
		else
		{
			slot = startHr + ":" + std::to_string(endMin);
			endMin += 20;
		}
		
		
		times->push_back(slot);
	}
	exec.writeRecord(eventID, exec.createRecordList(times));
	delete times;   
}
//END NEW CODE
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
            }else{
                std::cout << "No valid input.\n";
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
            slot = i.getTime();
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

	int hour = std::stoi(input.substr(0, 2));
	if(hour <= 12){
		return (input + " PM");
	}else if(hour > 12){
		hour -= 12;
		std::string hrStr = std::to_string(hour);
		if (hrStr.length() == 1){//It seems to me that we should append a '0' on these times (e.g.) 01:20 PM
			input[0] = '0';					  //Just for now until we know if there would be errors from other code expecting this format.
			input[1] = hrStr[0];
			return(input + " AM");
		}
		else{
			input[0], input[1] = hrStr[0], hrStr[1];
			return(input + " PM");
		}
		//return (std::to_string(hour) + std::string(input.substr(delimiter)) + " PM");
	}else{
		return (input + " AM");
	}
}

bool CLI::checkTime(std::string stime, std::string etime){
//HH:MM
//Convert these values to Numbers to make math easier.
std::string startHr = stime.substr(0, 2);
int startMin = stoi(stime.substr(3, 2));
std::string endHr = etime.substr(0, 2);
int endMin = stoi(etime.substr(3, 2));

if (((startMin % 20 == 0) && (endMin % 20 == 0)) == false){
	std::cout << "startMin || endMin not on timeslot  *DBG\n";
	std::cout << "Meeting must begin and end on the hour or 20 minute increments thereof.\n";
	return(false);
}

//Check for overnight
if ((startHr >= "00" && startHr < "05") || (endHr > "00" && endHr <= "05")){
	std::cout << "Error: Meeting Start || End overnight. *DBG \n";
	std::cout << "Meetings may not occur between 12:00am - 5:00am\n";
	return(false);
}
//Check for lunch.
else if ((startHr >= "12" && startHr < "13") || ((endHr >= "12" && endMin > 0) && endHr <= "13")){
	std::cout << "Error: Meeting Start || End lunch. *DBG \n";
	std::cout << "Meetings may not occur between 12:00pm - 1:00pm\n";
	return(false);
}

//Check if meeting would span the restricted overnight period.
//NOTE: Even though they can choose only one day, a user could attempt to schedule
//      an end time in the AM even though their begin time is PM. This will account for that.
//      Also, we can use >= 13 because we already checked for meetings that span lunch.
else if (startHr >= "13" && endHr < "13"){
	std::cout << "Meetings must begin and end on the same calendar day.\n";
	return(false);
}

//Check if meeting would span the restricted lunch period.
else if ((startHr >= "05" && startHr < "12") && endHr > "13"){
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