#include "CLI.h"

CLI::CLI(){
    longtime = true;
}

void CLI::run(){
	std::cout   << "\n*=========Welcome to Group 1's Project 2 Event Planner!=========*\n"
				<< "*\tCredits:                                        \t*\n"
				<< "*\t\tDiego Garcia                           \t\t*\n"
				<< "*\t\tKyle Berkley                           \t\t*\n"
				<< "*\t\tRon Huff                               \t\t*\n"
				<< "*\t\tSurabhi Khachar                        \t\t*\n"
				<< "*\t\tWeiting Wei                            \t\t*\n"
				<< "*===============================================================*\n\n";

	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);

	std::cout << "\t\t~ The current date is " << (newtime.tm_mon+1) << "/" << newtime.tm_mday << "/" << newtime.tm_year+1900 << " ~" <<endl;

	login();
}

void CLI::login() {
	int choice;
	std::cout << "\n======================== Login Menu =======================\n";
	std::cout << "\t1) Login.\n";
	std::cout << "\t2) Create Account.\n";
	std::cout << "\t3) Exit.\n";
	std::cout << "\nSelection: ";

	std::cin >> choice;
	while (choice != 1 && choice != 2 && choice != 3) {
		std::cin.clear(); // unset failbit
		std::cout << "Please choose one of the options (1-3).\n";
		std::cin.ignore(numeric_limits<streamsize>::max(), '\n'); // skip bad input
		std::cout << "\nSelection: ";
		std::cin >> choice;
	}
	if (choice == 1) {
		std::string uname = "";
		std::cout << "Please enter your user name: ";
		std::cin >> uname;
		while (std::cin.fail() || uname == "") {
			std::cin.clear();
			std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
			std::cout << "Invalid username... Please re-enter your user name: ";
			std::cin >> uname;
		}

		if (exec.setCurrentUser(uname)) {
			std::cout << "\nUsername accepted.\n";
			menu();
		}
		else {
			std::cout << "Username not recognized...\n\n";
			login();
		}
	}
	else if (choice == 2) {
		newAccount();
		login();
	}
	else {
		std::cout << "Have a pleasant day...\n";
	}
}

void CLI::menu() {
    std::cout << "\n\n=========================== MAIN MENU ===========================\n" <<
				 "\nPlease choose from the following options:\n\n" <<
                 "1) View Events List:\n" <<
				 "2) Create New Event:\n"
                 "3) Manage Settings:\n" <<
                 "4) Logout of Account:\n" <<
                 "5) Exit Application:\n";
	std::cout << "Selection: ";
	int action;
	std::cin >> action;
	while (action != 1 && action != 2 && action != 3 && action != 4 && action != 5) {	
		std::cin.clear(); // unset failbit
		std::cout << "Please simply choose one of the options (1-5) and press enter/return.\n";
		std::cin.ignore(numeric_limits<streamsize>::max(), '\n'); // skip bad input
		std::cout << "\nSelection: ";
		std::cin >> action;
	}
	std::cout << "\n";
    if(action == 1) {
        listEvents(0);
		menu();
    }
	else if(action == 2) {
		try {
			newEvent();
		}
		catch (std::exception& e) {
			std::cout << e.what();
		}
		menu();
    }
	else if(action == 3) {
        options();
		menu();
    }
	else if(action == 4) {
		std::cout << "Logout successful.\n\n";
		login();
    }else if(action == 5) {
		std::cout << "Have a pleasant day...\n";
		return;
    }
}

void CLI::options() {
	int choice = 0;
	std::cout << "Please select from the following options:\n";//We can add more here if necessary for Project 2 requirements.

	while (choice != 1 && choice != 2) {
		if (longtime) std::cout << "1) Switch to 12 hour display.\n";
		else std::cout <<          "1) Switch to 24 hour display.\n";

		std::cout << "2) Close time-toggle.\n";
		std::cout << "\nSelection: ";
		std::cin >> choice;  // = input.getString("\nSelection: ");

		if (choice != 1 && choice != 2) {
			std::cin.clear(); // unset failbit
			std::cout << "Please simply choose one of the options (1 or 2) and press enter/return.\n";
			std::cin.ignore(numeric_limits<streamsize>::max(), '\n'); // skip bad input
			continue;
		}
	}

	if (choice == 1) longtime = (longtime) ? false : true;
	if (longtime) std::cout << "You've switched to 24 hour display mode.\n";
	else		  std::cout << "You've switched to 12 hour display mode.\n";
}

void CLI::newAccount() {
    std::string name = "";
    std::string username = "";
    bool validIdentifier = false;

	name = input.getLine("\nEnter your full name: ");
	while (name.length() < 5 || name.length() > 64) {
		if (name.empty() || name == "quit" || name == "Quit") {
			std::cout << "Returning to login menu...\n";
			return;
		}
		std::cout << "Hm. Try a name between 5 and 50 characters.\nYou can \"Quit\"to return to the login menu.\n";
		name = "";
		name = input.getLine("Enter your full name: ");
	}

	//std::cout << "You've created full name: \"" << name << "\".\n";

    while(!validIdentifier) {
        username = input.getString("\nEnter your preferred username (no spaces): ");
		if (username.empty() || username == "quit" || username == "Quit") {
			std::cout << "Returning to login menu...\n";
			return;
		}
		else if (username == "CreateAccount" || username == "Quit") { //username.find(" ") != std::string::npos
			std::cout << "You may not use that username.\n";
			std::cout << "\nYou can \"Quit\" to cancel...\n";
			continue;
		}
		else if (username.length() < 5 || username.length() > 32) {
			std::cout << "Keep your username between 5 and 32 characters please.\n";
			std::cout << "\nYou can \"Quit\" to cancel...\n";
			continue;
		}
		else if (username.find(' ') != std::string::npos) {
			cout << "Username cannot have spaces!" << endl;
			continue;
		}


		validIdentifier = exec.createUser(username, name);
		if (!validIdentifier) {
			std::cout << "Someone has that username already.\n";
			username = "";
			std::cout << "\nYou can \"Quit\" to cancel...\n";
			continue;
		}
		std::cin.clear();
		std::cout << "\nAccount " + username + " has been created under the name \"" + name + "\".\n";
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
		//std::cout << "\nPlease select a meeting to view or press enter to go back.\n";//NOTE: returning from this function may not actually cause the user to "go back"
		//std::cout << "Selection: ";
		inString = input.getString("\nPlease select a meeting to view or press enter to go back.\nSelection: ");
		//getline(std::cin, inString);
		if (inString.empty()){
			break;
		}
		else if (inString.find_first_not_of("0123456789") != std::string::npos) {
			std::cout << "Only numbers are accepted...\n\n";
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
}


void CLI::newEvent() throw(std::exception) {
    int year = 0, month = 0, day = 0;
    int eventID;
    std::string date = "";
    std::cout << "You are creating a new event.\n";
    std::string name = input.getLine("First, provide an event title: ");


    std::cout << "\nTo create event \"" << name << "\", there needs to be a date.\n";
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);
	 
    bool validDate = false; //Hahaha like "validate"
	while (!validDate) {
		std::cout << "\nPlease enter a date in the format MM/DD/YYYY.\n";
		std::cin >> date;

		while (std::cin.fail() || date.length() != 10 || (date[2] != '/' || date[5] != '/')) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			std::cout << "For ease of use, enter a date in the format MM/DD/YYYY.\n";
			std::cin >> date;
		}
		std::string year = date.substr(6, 4);
		std::string day = date.substr(3, 2);
		std::string month = date.substr(0, 2);

		try {
			stoi(year);
			stoi(month);
			stoi(day);
		}
		catch (std::exception& e) {
			std::cout << "Each date value (MM, DD, and YYYY) must be a valid integer.\nTry again.\n";
			continue;
		}

		//Checks if date is in the past:
		if (stoi(year) < newtime.tm_year + 1900) {
			std::cout << "No meetings permitted to be scheduled in a past year.\n";
			continue;
		}
		else if (stoi(year) == (newtime.tm_year + 1900) && (newtime.tm_mon+1) > stoi(month)) {
			std::cout << "No meetings permitted to be scheduled in a past month.\n";
			continue;
		}
		else if (stoi(year) == (newtime.tm_year+1900) && (newtime.tm_mon+1) == stoi(month) && stoi(day) < newtime.tm_mday) {
			std::cout << "No meetings permitted to be scheduled in a past date.\n";
			continue;
		}
		//New Year's Day.
		else if (month == "01" && day == "01"){
			std::cout << "No meetings permitted to be scheduled on New Year's Day.\n";
			continue;
		}
		//Independence Day
		else if (month == "07" && day == "04"){
			std::cout << "No meetings permitted to be scheduled on Independence Day.\n";
			continue;
		}
		//Christmas Day
		else if (month == "12" && day == "25"){
			std::cout << "No meetings permitted to be scheduled on Christmas Day.\n";
			continue;
		}
		else {
			validDate = true;
		}
		date = year + "/" + month + "/" + day;
		validDate = true;
    }

	eventID = exec.generateEvent(name, date);
	
	std::cout << "\nPlease enter a beginning time for your meeting.\n";
	std::cout << "Your time will be rounded down to the nearest 20-minite interval.\n";
	//BEGIN NEW CODE
	std::string stime = "";
	std::string etime = "";
	std::cout << "Enter start time in format HH:MM\n";
	std::cin >> stime;
	if (!cin) {//This will still allow for bad input for now but at least it forces it to be a string for testing.
		std::cout << "ERROR: Please enter the time in the format of HH:MM\n";
		std::cin >> stime;
	}
	std::cout << "Enter end time in format HH:MM\n";
	std::cin >> etime;
	if (!cin) {
		std::cout << "ERROR: Please enter the time in the format of HH:MM\n";
		std::cin >> etime;
	}
	while (!checkTime(stime, etime)) {
		std::cout << "Enter start time in format HH:MM\n";
		std::cin >> stime;
		if (!cin) {
			std::cout << "ERROR: Please enter the time in the format of HH:MM\n";
			std::cin >> stime;
		}
		std::cout << "Enter end time in format HH:MM\n";
		std::cin >> etime;
		if (!cin) {
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
		else {
			slot = startHr + ":" + std::to_string(endMin);
			endMin += 20;
		}
		
		
		times->push_back(slot);
	}
	std::cout << "\nWe can now include a list of tasks for the meeting!\n";
	std::cout << "Would you like to add a list now? (you can still add one later.)\n";
	std::cout << "1) Yes.\n";
	std::cout << "2) No.\n";
	int newList;
	std::cout << "Add tasks? ";
	std::cin >> newList;
	//std::shared_ptr<TaskList> taskList;

	while (newList != 1 && newList != 2) {	
		std::cin.clear();
		std::cin.ignore();
		std::cout << "Only an input of 1 or 2 is accepted.\n";
		std::cout << "Add tasks? ";
		std::cin >> newList;
	}

	if (newList == 1) {
		std::vector<std::string> tasks = populateTaskList();
		//NOTE: THIS EXEC FUNCTION WILL NOT WORK WITHOUT THE UPDATED EXECUTIVE FILE
		//exec.writeRecord(eventID, exec.createRecordList(times), populateTaskList());
		exec.createTaskList(tasks, eventID);
		exec.writeRecord(eventID, exec.createRecordList(times));
		//Switch the two above functions 
		std::cout << "\n~~~~~~~~~ Your event will be created! ~~~~~~~~~~~\n";
		delete times;

		//std::shared_ptr<TaskList> temp = std::make_shared<TaskList>();
		//temp->createTask();
		//temp->createTask();
		//taskList = temp;
		//code for addint list here. Will require analysis of data structure
		/*m_tasks = new TaskList();*/
	}
	else {
		std::cout << "\n~~~~~~~~~ Your event will be created! ~~~~~~~~~~~\n";
		//NOTE: THIS EXEC FUNCTION WILL NOT WORK WITHOUT THE UPDATED EXECUTIVE FILE

		//std::vector<std::string> taskList(0); //Creates an empty task list vector
		//exec.writeRecord(eventID, exec.createRecordList(times), taskList);
		exec.writeRecord(eventID, exec.createRecordList(times));
		delete times;
	}

	//eventID = exec.generateEvent(name, date);
	//exec.writeRecord(eventID, exec.createRecordList(times));
	//exec.writeTaskList(eventID, taskList);
	//delete times;   
}

std::vector<std::string> CLI::populateTaskList() {
	std::vector<std::string> taskList(0);
	std::string task = "test";
	std::string rmTask = "test, also";
	int choice;

	while (1) {
		std::cout << "\nPlease choose from the following task options:\n\n" <<
			"1) View current task list\n" <<
			"2) Add another task\n"
			"3) Remove a task\n" <<
			"4) Complete task list\n";
		std::cout << "Selection: ";
		std::cin >> choice;
		while (choice != 1 && choice != 2 && choice != 3 && choice != 4) {
			std::cin.clear(); // unset failbit
			std::cout << "Please choose one of the options (1-4) and press enter/return.\n";
			std::cin.ignore(numeric_limits<streamsize>::max(), '\n'); // skip bad input
			std::cout << "\nSelection: ";
			std::cin >> choice;
		}
		
		if (choice == 1) {
			if (taskList.size() == 0) std::cout << "\nThere are no tasks right now.\n";
			else {
				std::cout << "\n------ Current Task List ------\n";
				for (int i = 0; i < taskList.size(); i++) {
					std::cout << (i+1) << ") " << taskList[i] << endl;
				}
			}
		}
		else if (choice == 2) {
			while (1) {
				task = "";
				task = input.getString("\n"); //dummy getline because the IOStream is my enemy
				task = input.getString("Provide a task title, or press enter to quit: ");
				//std::cout << "task is " << task;
				if (task.empty() || task == "quit" || task == "Quit") {
					std::cout << "Returning to task menu...\n";
					break;
				}
				else if (task.length() < 6) {
					std::cout << "Try making a longer task title.\n";
					continue;
				}
				for (int i = 0; i < taskList.size(); i++) {
					if (task == taskList[i]) {
						std::cout << "That task already exists. Try again...\n";
						continue;
					}
				}
				//If this code runs, constraints were passed.
				taskList.push_back(task);
				std::cout << "\nTask successfully added!\n";
				break;
			}
		}
		else if (choice == 3) {
			if (taskList.size() == 0) std::cout << "\nThere are no tasks to delete.\n";
			else {
				std::cout << "\n------ Current Task List ------\n";
				for (int i = 0; i < taskList.size(); i++) {
					std::cout << (i + 1) << ") " << taskList[i] << endl;
				}
				int rmIndex = 0;
				rmTask = "";
				rmTask = input.getString("\n"); //dummy getline because the IOStream is my enemy
				while (1) {
					rmTask = input.getString("\nSelect a task to remove, or press enter to exit.: ");
					if (rmTask.empty() || rmTask == "quit" || rmTask == "Quit") {
						std::cout << "Returning to task menu...\n";
						break;
					}
					try {
						rmIndex = stoi(rmTask);
						if (rmIndex < 1 || rmIndex > taskList.size()) {
							std::cout << "Make sure to choose one of the indices above.\n";
							continue;
						}
						std::cout << taskList[rmIndex-1] << " was removed!\n";
						taskList.erase(taskList.begin() + rmIndex-1);
						break;
					}
					catch (std::exception& e) {
						std::cout << "Invalid index number.\n";
						continue;
					}
				}
			}
		}
		else return taskList;
	}
}

void CLI::viewEvent(int i){
    try{
        Event* e = exec.getEventByID(i);
		std::cout << "Title:\t\t" << e->getName() << "\n" <<
			"Creator:\t" << e->getCreatorRealName() << "\n" <<
			"Date:\t\t" << e->getDate(false) << "\n\n" <<
			"Start: " << /*starttime here*/ "\tEnd: " << /*endtime*/ "\n\n";

        std::string choice;
		bool creator = false;
        while(choice != "quit"){//this condition is annoying and I don't want to further refactor this so I am doing a less than optimal work around.
			creator = exec.getCurrentUser()->getUserName() == e->getCreatorUserName();
			/*if(exec.getcurrentuser()->getusername() != e->getcreatorusername()){
				
            }
			else
			{
				creator = true;
			}*/
			
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

				std::cout << "Selection:";//NOTE: returning from this function may not actually cause the user to "go back"
				std::getline(std::cin, inString);
				if (inString.empty() || stoi(inString) == 3) {
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
				std:: cout << "\n";
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
	for (auto list_it = list_rbeg; list_it != list_rend; ++list_it)
	{
		std::string slot;
		if (longtime) {
			slot = zeroAppender((*list_it).getTime());//here zeroAppender is taking the std::string parameter returned by i.getTime());
		}
		else {
			slot = to12Hour((*list_it).getTime());
		}
		std::cout << "Time: " << slot << "\nAttendees: ";

		//SHows all attending users
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
		std::cout << "\n";
	}

	std:: cout << "\n";
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