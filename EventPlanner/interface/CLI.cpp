#include "CLI.h"

CLI::CLI(){
    longtime = true;
    loggedin = false;
    quit = false;
	m_execObj = std::make_shared<Executive>();
}

CLI::CLI(std::shared_ptr<Executive> exec)
{
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
	std::cin.clear();
    std::cout << "\nPlease choose from the following options:\n\n" <<
                 "1) View Events List:\n" <<
				 "2) Create New Event:\n"
                 "3) Manage Settings:\n" <<
                 "4) Logout of Account:\n" <<
                 "5) Exit Application:\n";
	std::cout << "Selection: ";
	int action;
	std::cin >> action;
	while (!cin) {
		
		if (!cin) {
			std::cout << "Please simply choose one of the options (1-5) and press enter/return.\n";
		}
		std::cout << "\nSelection: ";
		std::cin >> action;
	}
	std::cout << "\n";
	if (action == 1) {
		listEvents();
		std::cout << "Please select the menu ID to view or press enter to return to the main menu.\n";
		std::cout << "Meeting ID: ";

		std::string choice;

		std::cin >> choice;
		while ((!(std::stoi(choice) > 0) && !(std::stoi(choice) < 4)) || choice == "") {
			if (choice == "")
			{

			}
			else if (!cin) {
				std::cin.clear(); // unset failbit
				std::cout << "Please simply choose one of the options (1-3) and press enter/return.\n";
				std::cin.ignore(numeric_limits<streamsize>::max(), '\n'); // skip bad input
				std::cout << "\nSelection: ";
				std::cin >> choice;
			}

		}

		viewEvent(std::stoi(choice));
	}
	else if(action == 2){
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

void CLI::options() {
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
					std::cout << "\nInvalid input, please re-enter your user name: ";
					std::cin >> uname;
			}
			try {
				if (m_execObj->verifyUserName(uname)) {
					std::cout << "\nUser name accepted.\n";
					loggedin = true;
				}
				else {
					std::cout << "\nUser name unrecognized or invalid.\n";
				}
			}
			catch (std::exception& e) {
				std::cerr << e.what();
			}
		}
	}
}

void CLI::logout(){
    loggedin = false;
}

void CLI::newAccount(){
	m_execObj->createAccount();
}

void CLI::listEvents(){
   /* std::vector<Event>* list = exec.getEventList();*/
	m_execObj->viewMeetingList();
}


void CLI::newEvent() throw(std::exception) {
	int year = 0, month = 0, day = 0;
	int eventID;
	std::string date = "";
	std::cout << "You are creating a new event.\nTo get started with, we need an event title.\n";
	std::string name = input.getLine("Enter event name: ");

	int meetDates = 1;
	bool createDays = true;
	std::cout << "Next there needs to be a date for the event.\n";
	bool validDate = false;
	while (createDays)// if user wants to add additional days this remains true. false when done.
	{
		while (!validDate) {
			if (meetDates == 1)
			{
				std::cout << "Please enter a date in the format MM/DD/YYYY.\n";
			}
			else
			{
				std::cout << "Please enter a date for day " + std::to_string(meetDates) + ":";
			}

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
			if (month == "01" && day == "01") {
				throw std::logic_error("No meetings permitted to be scheduled on New Year's Day.\n");
			}
			//Independence Day
			else if (month == "07" && day == "04") {
				throw std::logic_error("No meetings permitted to be scheduled on Independence Day.\n");
			}
			//Christmas Day
			else if (month == "12" && day == "25") {
				throw std::logic_error("No meetings permitted to be scheduled on Christmas Day.\n");
			}
			else {
				validDate = true;
			}
			date = year + "/" + month + "/" + day;

			validDate = true;
		}
		if (meetDates > 1)
		{
			std::cout << "Automatically declare the same times for this date or define new times?\n";
			std::cout << "1) Apply the same times.\n";
			std::cout << "2) Define new times.\n";
			int choice;
			std::cin >> choice;
			while (!(choice > 0) && !(choice < 3)) {
				if (!cin) {
					std::cin.clear(); // unset failbit
					std::cout << "Please simply choose one of the options (1-2) and press enter/return.\n";
					std::cin.ignore(numeric_limits<streamsize>::max(), '\n'); // skip bad input
				}
				std::cout << "\nSelection: ";
				std::cin >> choice;
			}
			if (choice == 1)
			{
				std::shared_ptr<Date> temp = ((*m_execObj).m_eventList.back()->m_meetDates.back()); //Date constructor should create timeslots and assign creator as attendee for each.
				temp->m_date = date;
				(*m_execObj).m_eventList.back()->m_meetDates.push_back(temp);
			}
		}
		else
		{
			std::cout << "Please enter a beginning time for your meeting. ";
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

			m_execObj->addEvent(name);
			m_execObj->m_numMeetings++;
			m_execObj->m_eventList.back()->m_id = m_execObj->m_numMeetings;
			m_execObj->m_eventList.back()->m_creator = m_execObj->m_currentUser;

			std::shared_ptr<Date> temp = std::make_shared<Date>(date, stime, timeslots, m_execObj->m_currentUser);//Date constructor should create timeslots and assign creator as attendee for each.
																												  //the first slot.
			m_execObj->m_eventList.back()->m_meetDates.push_back(temp);
		}

		std::cout << "Would you like to add another date for this meeting?\n";
		std::cout << "1) Yes.\n";
		std::cout << "2) No.\n";
		std::cout << "Selection: ";
		int choice;
		std::cin >> choice;
		while (!(choice > 0) && !(choice < 3)) {
			if (!cin) {
				std::cin.clear(); // unset failbit
				std::cout << "Please simply choose one of the options (1-2) and press enter/return.\n";
				std::cin.ignore(numeric_limits<streamsize>::max(), '\n'); // skip bad input
			}
			std::cout << "\nSelection: ";
			std::cin >> choice;
		}
		if (choice == 1) {
			validDate = false;// user must validate the new date for the meeting.
			meetDates++;
		}
		else if (choice == 2){
			createDays = false;
		}
	}
	std::cout << "\nWe can now include a list of tasks for the meeting!\n";
	std::cout << "Would you like to add a list now? (you can still add one later.)\n";
	std::cout << "1) Yes.\n";
	std::cout << "2) No.\n";
	int newList;
	std::cin >> newList;
	while (!(newList > 0) && !(newList < 3)) {
		if (!cin) {
			std::cin.clear(); // unset failbit
			std::cout << "Please simply choose one of the options (1-2) and press enter/return.\n";
			std::cin.ignore(numeric_limits<streamsize>::max(), '\n'); // skip bad input
		}
		std::cout << "\nSelection: ";
		std::cin >> newList;
	}
	while (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore();
		std::cout << "Error: Unrecognized input, please try again.\n";
		std::cin >> newList;
	}
	if (newList == 1)
	{
		while (1)
		{
			std::shared_ptr<TaskList> temp = std::make_shared<TaskList>();
			if (temp->createTask()) {
				std::cout << "\nTask created.\n\n";
				std::cout << "Create another?\n";
				std::cout << "1) Yes.\n";
				std::cout << "2) No.\n";
				int choice;
				std::cin >> choice;
				while (!(choice > 0) && !(choice < 3)) {
					if (!cin) {
						std::cin.clear(); // unset failbit
						std::cout << "Please simply choose one of the options (1-2) and press enter/return.\n";
						std::cin.ignore(numeric_limits<streamsize>::max(), '\n'); // skip bad input
					}
					std::cout << "\nSelection: ";
					std::cin >> choice;
				}
				if (choice == 2)
				{
					std::cout << "Task list created!\n";
					break;
				}
			}


		}
		//code for addint list here. Will require analysis of data structure.
		/*m_tasks = new TaskList();*/
	}
	else if (newList == 2)
	{

	}
		/*exec.writeRecord(eventID, exec.createRecordList(times));*/
}

//END NEW CODE
void CLI::viewEvent(int i){
    try{
		bool creator = false;
		bool viewing = true;
		while (viewing) {//this condition is annoying and I don't want to further refactor this so I am doing a less than optimal work around.
			std::shared_ptr<Event> e = m_execObj->getEventByID(i);
			std::cout << "Title:\t\t" + e->m_name + "\nCreator:\t" + e->m_creator->m_realName + "\n";

			for (std::vector<std::shared_ptr<Date>>::iterator it = e->m_meetDates.begin(); it != e->m_meetDates.end(); ++it) {
				std::cout << "Date(s):\t" + (*it)->m_date + "\n" +
					"Start: " + (*it)->m_startTime + "\tEnd: " + (*it)->m_endTime + "\n\n";
				for (std::vector<std::shared_ptr<TimeSlot>>::iterator ts = (*it)->m_timeSlots.begin(); ts != (*it)->m_timeSlots.end(); ++ts) {
					std::cout << (*ts)->m_startTime;
					for (std::vector<std::shared_ptr<User>>::iterator att = (*ts)->m_attendees.begin(); att != (*ts)->m_attendees.end(); ++att)
					{
						std::cout << " " + (*att)->m_realName + "\n";
					}
				}
			}
			std::string choice = "";
			
        
			std::string currName = m_execObj->m_currentUser->m_realName;
			std::string creatorName = e->m_creator->m_realName;
            if(currName == creatorName){
				creator = true;
            }
			else
			{
			}
			
			while (1) {
				std::string inString = "x";
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

				int choice;
				std::cin >> choice;
				while (choice != 1 && choice != 2 && choice != 3)
				{
					if (!cin) {
						std::cin.clear(); // unset failbit
						std::cout << "Please simply choose one of the options (1-3) and press enter/return.\n";
						std::cin.ignore(numeric_limits<streamsize>::max(), '\n'); // skip bad input
					}
					std::cout << "\nSelection: ";
					std::cin >> choice;
				}
				if(choice == 1 && m_execObj->m_currentUser->m_realName != e->m_creator->m_realName) {
					creator = false;
					setAvailability(i);//unknown if/how this works at this point, but am attempting to keep things integrated with Team 8 code.
					std::cout << "\n";
				}
				else if (choice == 1 && creator)
				{
					std:: cout << "\n";
					viewAvailability(i);
				}
				else if (choice == 2 && !creator) {
					viewAvailability(i);
				}
				else if (choice == 2 && creator)
				{
					viewing = false;
					break;
				}
				else {
					std::cout << "Error: Invalid meeting number.\n";
				}
			}
        }
    }catch(std::exception& e){
        std::cout << "Invalid event number.\n";
    }
}

void CLI::setAvailability(int eid){
	
	std::shared_ptr<Event> thisEvent = m_execObj->m_eventList.at(eid - 1);

    std::cout << "For each of the following times enter 'y' or 'n' to confirm or deny availablity.\n";

	for (std::vector<shared_ptr<Date>>::iterator it = thisEvent->m_meetDates.begin(); it != thisEvent->m_meetDates.end(); ++it) {
		std::cout << "Date(s):\t" << (*it)->m_date + "\n" <<
			"Start: " << (*it)->m_startTime + "\tEnd: " + (*it)->m_endTime + /*endtime*/ "\n\n";

		for (auto i : (*it)->m_timeSlots) {
			std::string slot;
			if (longtime) {
				slot = i->m_startTime;
			}
			else {
				slot = to12Hour(i->m_startTime);
			}

			if (input.getCharacter(slot + " - ") == 'y') {
				i->m_attendees.push_back(m_execObj->m_currentUser);
				
			}
		}
	}
}

void CLI::viewAvailability(int eid){

	std::shared_ptr<Event> thisEvent = m_execObj->m_eventList.at(eid - 1);

	for (std::vector<std::shared_ptr<Date>>::iterator date = thisEvent->m_meetDates.begin(); date != thisEvent->m_meetDates.end(); ++date)
	{
		/*std::cout << thisEvent->m_creator->m_realName;*/
		for (std::vector<shared_ptr<TimeSlot>>::iterator time = (*date)->m_timeSlots.begin(); time != (*date)->m_timeSlots.end(); ++time)
		{
			std::string slot;
			if (longtime) {
				slot = zeroAppender((*time)->m_startTime);//here zeroAppender is taking the std::string parameter returned by i.getTime());
			}
			else {
				slot = to12Hour((*time)->m_startTime);
			}
			std::cout << "Time: " << slot << "\nAttendees: ";

			//SHows all attending users
			
			for (std::vector<shared_ptr<User>>::iterator att = (*time)->m_attendees.begin(); att != (*time)->m_attendees.end(); ++att)
			{
				std::cout << (*att)->m_realName << "\n\t";
			}
		}
	}
	std:: cout << "\n";
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