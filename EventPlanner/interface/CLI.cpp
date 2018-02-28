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
    std::cout << "Have a wonderful day.\n\n";
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
	std::cout << "\n";
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
    int choice;
    std::cout << "Please select from the following options:\n";//We can add more here if necessary for Project 2 requirements.
    
	if (longtime) {
		std::cout << "1) Switch to 12 hour display.\n";
		std::cout << "2) Close options.\n";//perhaps could have better wording here.
		std::cout << "\nSelection: ";
		std::cin >> choice;
	}
	else {
		std::cout << "1) Switch to 24 hour display.\n";
		std::cout << "2) Close options.\n";
		std::cout << "\nSelection: ";
		std::cin >> choice;
	}

	while (!(choice > 0) && !(choice < 3) && choice != 2) {
		std::cin >> choice;
		if (!cin) {
			std::cin.clear(); // unset failbit
			std::cout << "Please simply choose one of the options (1-2) and press enter/return.\n";
			std::cin.ignore(numeric_limits<streamsize>::max(), '\n'); // skip bad input
		}
		if (longtime) {
			std::cout << "1) Switch to 12 hour display.\n";
			std::cout << "2) Close options.\n";//perhaps could have better wording here.
			std::cout << "\nSelection: ";
			std::cin >> choice;
		}
		else {
			std::cout << "1) Switch to 24 hour display.\n";
			std::cout << "2) Close options.\n";
			std::cout << "\nSelection: ";
			std::cin >> choice;
		}
		std::cin >> choice;
	}
	
	if (choice == 1)
	{
		longtime = (longtime) ? false : true;
	}
	else if (choice == 2)//come back here and check for bad input.
	{

	}
}
/////
void CLI::login() {

	while (!loggedin) {
		int choice;
		std::cout << "\nWelcome to the event planner!\n";
		std::cout << "-===========================-\n\n";
		std::cout << "1) Login.\n";
		std::cout << "2) Create Account.\n";
		std::cout << "3) Exit.\n";
		std::cout << "Selection: ";

		std::cin >> choice;
		while (!(choice > 0) && !(choice < 4)) {
			if (!cin) {
				std::cin.clear(); // unset failbit
				std::cout << "Please simply choose one of the options (1-3) and press enter/return.\n";
				std::cin.ignore(numeric_limits<streamsize>::max(), '\n'); // skip bad input
			}
			std::cout << "\nSelection: ";
			std::cin >> choice;
		}
		if (choice == 2) {
			newAccount();
		}
		else if (choice == 3) {
			quit = true;
			return;
		}
		else if (choice == 1) {
			std::string uname = "";
			std::cout << "Please enter your user name: ";
			std::cin >> uname;
			while (cin.fail()){
					std::cin.clear();
					std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
					std::cout << "Invalid input, please re-enter your user name: ";
					std::cin >> uname;
			}
			if (exec.setCurrentUser(uname)) {
				std::cout << "\nUser name accepted.\n";
				loggedin = true;
			}
			else {
				std::cout << "User name unrecognized or invalid.\n";
			}

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
	std::cout << "\n\tCurrently Scheduled Events:\n\n";
    //Options
    
	//I have removed this functionality below. We can uncomment this if we wish later. We will likely need to change the "next"/"previous
	//to some sort of integer selection.
	
    //if(first > 0 ){//don't remove these two if statements.....they could be implemented in the case where numMeetings > 25 or something.
    //    std::cout << "\t\"previous\" to go back in the list\n";
    //}
    //if(first + 25 < size){
    //    std::cout << "\t\"next\" to go forward in the list\n";
    //}
    //std::cout << "\t\"menu\" to go to the menu\n";

    //Make Choice
	//std::cout << "Please select a meeting to view or press enter to go back.\n";//NOTE: returning from this function may not actually cause the user to "go back"
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	int choice;
	std::string inString;
	//The template for the below while loop was borrowed from https://stackoverflow.com/a/10553849 and modified to our needs.
	while (1){
		for (int i = first; i < (first + 26) && i < size; i += 1) {
			try {
				Event e = list->at(i);
				std::cout << std::to_string(e.getIDNumber()) + ")" << "\t" << e.getName() << "\t\t" << e.getDate(false) << "\t\t" << e.getCreatorRealName() << "\n";
			}
			catch (std::exception& e) {
				return;
			}
		}
		std::cout << "\nPlease select a meeting to view or press enter to go back.\n";//NOTE: returning from this function may not actually cause the user to "go back"
		std::cout << "Selection: ";

		getline (std::cin, inString);
		if (inString.empty()){
			break;
		}
		else if (std::stoi(inString) <= exec.whatIsEventNum() && std::stoi(inString) > 0) {
				std::cout << "\n";
				viewEvent(std::stoi(inString));
				std::cout << "\n";
			}
		else {
			std::cout << "Error: Invalid meeting number.\n";
		}
	}
	/*else if(choice == "next" && first < size){
        listEvents(first + 25 );
    }else if(choice == "previous" && first >= 0){
        listEvents(first - 25);
    }*/

}

void CLI::newEvent() throw(std::exception) {
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
			"Date:\t\t" << e->getDate(false) << "\n" <<
			"Start: " << /*starttime*/ "\tEnd: " << /*endtime*/ "\n\n";


        std::string choice;
		bool creator = false;
        while(choice != "quit"){//this condition is annoying and I don't want to further refactor this so I am doing a less than optimal work around.
            if(exec.getCurrentUser()->getUserName() != e->getCreatorUserName()){//check here if stability issue
            }
			else
			{
				creator = true;
			}
			
			while (1) {
				std::string inString = "";
				if (creator)
				{
					std::cout << "1) Redisplay meeting time slots.\n";
					std::cout << "2) Return to menu.\n";
				}
				else {
					std::cout << "If you are interested in joining this event:\n";
					std::cout << "1) Indicate your availability.\n"; //WE WILL ADD OTHER OPTIONS TO THIS MENU SO FULL MENU IMPLENTATION AT THIS POINT IS WORTH.
					std::cout << "2) Redisplay meeting time slots.\n"; //We can make these menus way more user friendly if we start making this feel more like an actual application
					std::cout << "3) Return to menu.\n"; //3 or a blank input will return to menu.
				}

				std::cout << "Selection: ";//NOTE: returning from this function may not actually cause the user to "go back"
				std::getline(std::cin, inString);
				if (stoi(inString) == 3) {
					choice = "quit";
					break;

				}
				else if (std::stoi(inString) == 1 && exec.getCurrentUser()->getUserName() != e->getCreatorUserName()) {
					creator = false;
					setAvailability(i);//unknown if/how this works at this point, but am attempting to keep things integrated with Team 8 code.
					std::cout << "\n";
				}
				else if (std::stoi(inString) == 1 && creator)
				{
					std::cout << "\n";
					viewAvailability(i);
				}
				else if (std::stoi(inString) == 2 && !creator) {
					viewAvailability(i);
				}
				else if (std::stoi(inString) == 2 && creator)
				{
					choice = "quit";
					break;
				}
				else {
					std::cout << "Error: Invalid meeting number.\n";
				}
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

	auto list_rbeg = (*eventRecords).rbegin();
	auto list_rend = (*eventRecords).rend();
	//Runs for each time slot

	for (auto list_it = list_rbeg; list_it != list_rend; ++list_it)
	{
		std::string slot;
		if (longtime) {
			slot = zeroAppender((*list_it).getTime());//here zeroAppender is taking the std::string parameter returned by i.getTime());
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
        std::cout << "\n";
    }
	std::cout << "\n";


		std::cout << "Time: " << slot << "\nAtendees: ";

		//Shows all attending users
		std::list<std::string> users = (*list_it).getUserList();
		std::cout << event->getCreatorRealName();
		for (auto i : users) {
			try {
				User* temp = exec.getUser(i);
				std::cout << ", " << temp->getRealName();
				delete temp;
			}
			catch (std::exception& e) {}
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
