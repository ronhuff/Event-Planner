#include "CLI.h"

CLI::CLI(){
    longtime = true;
}

void CLI::run(){
	std::cout   << "\n*=========Welcome to Group 1's Project 2 Event Planner!==========*\n"
				<< "*\tCredits:                                        \t*\n"
				<< "*\t\tDiego Garcia                           \t\t*\n"
				<< "*\t\tKyle Berkley                           \t\t*\n"
				<< "*\t\tRon Huff                               \t\t*\n"
				<< "*\t\tSurabhi Khachar                        \t\t*\n"
				<< "*\t\tWeiting Wei                            \t\t*\n"
				<< "*================================================================*\n\n";

	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);

	std::cout << "\t\t~ The current date is " << (newtime.tm_mon+1) << "/" << newtime.tm_mday << "/" << newtime.tm_year+1900 << " ~" <<endl;

	login();
}

void CLI::login() {
	int choice;
	std::cout << "\n========================== LOGIN MENU ===========================\n";
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
	for (std::vector<std::shared_ptr<TaskList>>::iterator tlit = exec.m_taskLists.begin(); tlit != exec.m_taskLists.end(); ++tlit)
	{
		int eid = (*tlit)->m_eventId;

		exec.writeTaskList(eid, *tlit);
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
        listEvents();
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
		for (std::vector<std::shared_ptr<TaskList>>::iterator tlit = exec.m_taskLists.begin(); tlit != exec.m_taskLists.end(); ++tlit)
		{
			int eid = (*tlit)->m_eventId;

			exec.writeTaskList(eid, *tlit);
		}
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

void CLI::listEvents(){
    std::vector<Event>* list = exec.getEventList();
    int size = list->size();
	std::cout << "\n\tCurrently Scheduled Events:\n\n";
	if (size == 0) {
		std::cout << "No events have been created yet!\n";
		return;
	}
        
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	int maxlength = 0;
	for (int i = 0; i < size; i++) {
		try {
			Event e = list->at(i);
			if (e.getName().length() > maxlength) maxlength = e.getName().length();
		}
		catch (std::exception& e) {
			return;
		}
	}

	int choice;
	std::string inString;
	//The template for the below while loop was borrowed from https://stackoverflow.com/a/10553849 and modified to our needs.
	while (1){
		for (int i = 0; i < size; i++) {
			try {
				Event e = list->at(i);
				std::string strngTabs = "\t\t";
				int tabs = (maxlength/8) - (e.getName().length()/8);

				for (int i = 0; i < tabs; i++) strngTabs += "\t";

				std::cout << std::to_string(e.getIDNumber()) + ")" << "\t" << e.getName() << strngTabs;
				for (int i = 0; i < e.getSizeOfDateVector(); i++)
				{
					std::cout << e.getDate(i) << "\t\t";
				}
				std::cout << e.getCreatorRealName() << "\n";
			}
			catch (std::exception& e) {
				std::cout << "Failed to load an event... :(\n";
				return;
			}
		}

		inString = input.getString("\nPlease select a meeting to view or press enter to go back.\nSelection: ");
		//getline(std::cin, inString);
		if (inString.empty()) break;
		else if (inString.find_first_not_of("0123456789") != std::string::npos) std::cout << "Only numbers are accepted...\n\n";
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
			date = year + "/" + month + "/" + day;
			validDate = true;
		}
    }
	std::vector<std::string> dList;
	dList.push_back(date);

	std::vector<std::list<std::string>*> tList;
	std::cout << "\nPlease enter a beginning time for your meeting.\n";
	std::cout << "Your time will be rounded down to the nearest 20-minite interval.\n";
	
	std::cout << "\nPlease enter a beginning and end time for your meeting.\n";
	std::cout << "Your time must be on a 20-minite interval.\n";
	//BEGIN NEW CODE
	std::string stime = "";
	std::string etime = "";

	int startMin;
	int endMin;
	int myendhr;
	stime = input.getString("\n");
	while(1) {
		//Start initial start time constraints
		stime = input.getString("Enter start time in format HH:MM\n");
		if (stime.length() != 5) {
			std::cout << "Time must be of format \"HH:MM\"\n";
			continue;
		}
		try {
			stoi(std::string() + stime.at(0) + stime.at(1));
			startMin = stoi(std::string() + stime.at(3) + stime.at(4));
			if (stime.at(2) != ':') continue;

		}
		catch (std::exception& e) {
			std::cout << "Your input must be valid.\n";
			continue;
		}
		if (stime == "23:40" || stime == "11:40") {
			std::cout << "There is not enough time to start an event at that time!\n";
			continue;
		}

		//start initial end time constraints.
		etime = input.getString("Enter end time in format HH:MM\n");
		if (etime.length() != 5) {
			std::cout << "End time must be of format \"HH:MM\"\n";
			continue;
		}
		try {
			myendhr = stoi(std::string() + etime.at(0) + etime.at(1));
			endMin = stoi(std::string() + etime.at(3) + etime.at(4));
			if (etime.at(2) != ':') continue;
		}
		catch (std::exception& e) {
			std::cout << "Your input must be valid and contain integers.\n";
			continue;
		}
		if (myendhr < 5 || myendhr > 24) {
			std::cout << "Can not end event at that time.\n";
			continue;
		}
		if (checkTime(stime, etime)) break;
	}

	std::string startHr = stime.substr(0, 2);
	std::string endHr = etime.substr(0, 2);

	int TOTAL_MINS = (stoi(endHr) - stoi(startHr)) * 60 + endMin - startMin;
	int timeslots = TOTAL_MINS / 20;
	
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
	tList.push_back(times);

	int addNewDates;
	std::cout << "Would you like to add more dates to this event:\n";
	std::cout << "1) Yes\n";
	std::cout << "2) No\n";
	std::cout << "Enter Your Choice: ";
	std::cin >> addNewDates;
	int repeat = 1;
		if (addNewDates == 1) {
			while(repeat == 1){
				int nYear = 0;
				int nMonth = 0;
				int nDay = 0;
				std::string nDate;
				bool valid = false;
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
					else if (stoi(year) == (newtime.tm_year + 1900) && (newtime.tm_mon + 1) > stoi(month)) {
						std::cout << "No meetings permitted to be scheduled in a past month.\n";
						continue;
					}
					else if (stoi(year) == (newtime.tm_year + 1900) && (newtime.tm_mon + 1) == stoi(month) && stoi(day) < newtime.tm_mday) {
						std::cout << "No meetings permitted to be scheduled in a past date.\n";
						continue;
					}
					//New Year's Day.
					else if (month == "01" && day == "01") {
						std::cout << "No meetings permitted to be scheduled on New Year's Day.\n";
						continue;
					}
					//Independence Day
					else if (month == "07" && day == "04") {
						std::cout << "No meetings permitted to be scheduled on Independence Day.\n";
						continue;
					}
					//Christmas Day
					else if (month == "12" && day == "25") {
						std::cout << "No meetings permitted to be scheduled on Christmas Day.\n";
						continue;
					}
					else {
						validDate = true;
					}
					date = year + "/" + month + "/" + day;
					validDate = true;
				}
				dList.push_back(nDate);
				int choiceForTimeSlots;
				std::cout << "1) Use the time slots from the other dates\n";
				std::cout << "2) Use new time slots for this date\n";
				std::cout << "Enter your choice: ";
				std::cin >> choiceForTimeSlots;
				if (choiceForTimeSlots == 1) {
					if (dList.size() == 1) {
						std::list<std::string>* newTimeSlots = tList.at(0);
						tList.push_back(newTimeSlots);
					}
					else {
						std::string lookUpDate = "";
						int position;
						for (int i = 0; i < dList.size(); i++) {
							std::cout << dList.at(i) + "\n";
						}
						std::cout << "Enter one of the dates from above int the same format of MM/DD/YYYY: ";
						std::cin >> lookUpDate;
						for (int i = 0; i < dList.size(); i++) {
							if (dList.at(i) == lookUpDate) {
								position = i;
							}
						}
						std::list<std::string>* oldTSlots = tList.at(position);
						tList.push_back(oldTSlots);
					}
				}
				else if (choiceForTimeSlots == 2) {
					std::string newStart = "";
					std::string newEnd = "";
					std::cout << "Enter start time in format HH:MM\n";
					std::cin >> newStart;
					if (!cin) {//This will still allow for bad input for now but at least it forces it to be a string for testing.
						std::cout << "ERROR: Please enter the time in the format of HH:MM\n";
						std::cin >> newStart;
					}
					std::cout << "Enter end time in format HH:MM\n";
					std::cin >> newEnd;
					if (!cin) {
						std::cout << "ERROR: Please enter the time in the format of HH:MM\n";
						std::cin >> newEnd;
					}
					while (!checkTime(newStart, newEnd)) {
						std::cout << "Enter start time in format HH:MM\n";
						std::cin >> newStart;
						if (!cin) {
							std::cout << "ERROR: Please enter the time in the format of HH:MM\n";
							std::cin >> newStart;
						}
						std::cout << "Enter end time in format HH:MM\n";
						std::cin >> newEnd;
						if (!cin) {
							std::cout << "ERROR: Please enter the time in the format of HH:MM\n";
							std::cin >> newEnd;
						}
					}

					std::string sHr = newStart.substr(0, 2);
					int sMin = stoi(newStart.substr(3, 2));
					std::string eHr = newEnd.substr(0, 2);
					int eMin = stoi(newEnd.substr(3, 2));
					int TOTAL_MINS = ((stoi(eHr) - stoi(sHr)) * 60 + eMin - sMin);

					int totalSlots = TOTAL_MINS / 20;

					//std::cout << "Total Minutes: " + TOTAL_MINS + " timeslots: " + (TOTAL_MINS / 20) << "\n";


					std::list<std::string>* ntimes = new std::list<std::string>();

					//the first slot.
					std::string nslot = sHr + ":" + std::to_string(eMin);
					eMin += 20;
					ntimes->push_back(nslot);
					for (int i = 1; i < totalSlots; i++)
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
						ntimes->push_back(slot);
					}
					tList.push_back(ntimes);
				}
				else {
					//TODO Error for invalid input
				}
				std::cout << "Would you like to add more dates to this event:\n";
				std::cout << "1) Yes\n";
				std::cout << "2) No\n";
				std::cout << "Enter Your Choice: ";
				std::cin >> repeat;
			}
		}
		else if (addNewDates == 2) {

		}
		else {
			//TODO Invalid input
		}
		eventID = exec.generateEvent(name, dList, tList);
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
		exec.writeRecord(eventID, exec.createRecordList(tList,dList));
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
		//exec.writeTaskList(eventID, false);
		exec.writeRecord(eventID, exec.createRecordList(tList,dList));
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
		std::cout << "\n=========================== TASK MENU ===========================\n\n" <<
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
			"Creator:\t" << e->getCreatorRealName() << "\n";
		std::cout << "Date:\t\t";
		
		for (int i = 0; i < e->getSizeOfDateVector(); i++) {
			std::cout << e->getDate(i) << "\t\t";
		}
		std::cout << "\n\n";
		std::cout << "Tasks: ";

		//"Start: " << /*starttime here*/ "\tEnd: " << /*endtime*/ "\n\n" << 
		//---------------------------------------
		//some loop That Shows tasks and statuses
		//---------------------------------------

		bool creator = false;
		creator = exec.getCurrentUser()->getUserName() == e->getCreatorUserName();
		if (creator) {
			std::cout << "Welcome, event creator!\n\n";
			viewAvailability(i);
			std::string waiter = input.getString("Press enter to continue...");
			return;
		}

		while(1) {//this condition is annoying and I don't want to further refactor this so I am doing a less than optimal work around.
			int menuchoice;

			std::cout << "Welcome Attendee! Here are your options:\n";
			std::cout << "1) Indicate your availability.\n"; //WE WILL ADD OTHER OPTIONS TO THIS MENU SO FULL MENU IMPLENTATION AT THIS POINT IS WORTH.
			std::cout << "2) Sign up for event tasks.\n"; 
			std::cout << "3) Return to menu.\n"; //3 or a blank input will return to menu.

			std::cout << "Selection:";//NOTE: returning from this function may not actually cause the user to "go back"
			std::cin >> menuchoice;
			while (menuchoice != 1 && menuchoice != 2 && menuchoice != 3) {
				std::cin.clear(); // unset failbit
				std::cout << "Please choose one of the options (1-3).\n";
				std::cin.ignore(numeric_limits<streamsize>::max(), '\n'); // skip bad input
				std::cout << "\nSelection: ";
				std::cin >> menuchoice;
			}
			if (menuchoice == 1) {
				setAvailability(i);//unknown if/how this works at this point, but am attempting to keep things integrated with Team 8 code.
				std::cout << "\n";
			}

			else if (menuchoice == 2) {
				std::cout << "Eventually, we'll be able to add your task list availability!\n";
			}
			else if (menuchoice == 3) {
				break;
			}
        }
        delete e;
    }catch(std::exception& e){
        std::cout << "Invalid event number.\n";
    }
}

void CLI::setAvailability(int eid){
    std::list<Record>* eventRecords = exec.readRecord(eid);
    std::cout << "For each of the following times enter 'yes', or 'y', or really anything to confirm availability.\n";
	std::cout << "Can't go at a specific time? Just press enter!\n";
	input.getString("\n");
    for(auto i : *(eventRecords)){
        std::string slot;
        if(longtime){
            slot = i.getTime();
        }else{
            slot = to12Hour(i.getTime());
        }

        if(!input.getString(slot + " - ").empty()){
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
std::string CLI::to12Hour(std::string myInput){

	int hour = std::stoi(myInput.substr(0, 2));
	if(hour <= 12){
		return (myInput + " AM");
	}else {                              //if(hour > 12){
		hour -= 12;
		std::string hrStr = std::to_string(hour);
		if (myInput == "24:00") return ("12:00 AM");
		return(hrStr + myInput.substr(2, 3) + " PM");
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
		std::cout << "startMin || endMin not on timeslot.\n";
		std::cout << "Meeting must begin and end on the hour or 20 minute increments thereof.\n";
		return(false);
	}

	//Check for overnight
	if ((startHr >= "00" && startHr < "05") || (endHr > "00" && endHr <= "05")){
		std::cout << "Error: Meeting Start || End overnight. \n";
		std::cout << "Meetings may not occur between 12:00am - 5:00am\n";
		return(false);
	}
	//Check for lunch.
	else if ((startHr == "12") || (endHr == "12" && endMin > 0)){
		std::cout << "Error: Meeting Start || End lunch. \n";
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