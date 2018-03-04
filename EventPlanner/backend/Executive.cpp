#include "../stdafx.h"
#include "Executive.h"




Executive::Executive()
{
	m_quit = false;
	m_loggedIn = false;
}


Executive::~Executive()
{
}


void Executive::run(std::shared_ptr<Executive> executiveObj)
{
	cli = std::make_shared<CLI>(executiveObj);
	/*menu();*/
	cli->run();
	//while (!m_quit)
	//{
	//	while (!m_loggedIn) {
	//		bool needCreate = false;
	//		std::cout << "1) Login.\n";
	//		std::cout << "2) Create Account.\n";
	//		std::cout << "3) Exit.\n";
	//		std::cout << "Selection: ";
	//		int choice;
	//		std::cin >> choice;
	//		while (choice != 1 && choice != 2 && choice != 3) {
	//			std::cin.clear(); // unset failbit
	//			std::cout << "Please simply choose one of the options (1-3) and press enter/return.\n";
	//			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // skip bad input
	//			std::cout << "\nSelection: ";
	//			std::cin >> choice;
	//		}
	//		if (choice == 1)
	//		{
	//			try {
	//				if (verifyUserName()) {
	//					m_loggedIn = true;
	//					break;
	//				}
	//				else
	//				{
	//					m_loggedIn = false;
	//				}
	//			}
	//			catch (std::exception& e)
	//			{
	//				std::cout << e.what();
	//			}
	//		}
	//		else if (choice == 2)
	//		{
	//			bool m_validAccount = false;
	//			while (!m_validAccount)
	//			{
	//				m_validAccount = createAccount();
	//				if (m_validAccount)
	//				{
	//					std::cout << "\nAccount creation successful. Please login in with your new account.\n";
	//					break;
	//				}
	//				else {
	//					std::cout << "Error: unknown error occured.\n";
	//				}
	//			}
	//		}
	//		else if (choice == 3)
	//		{
	//			m_quit = true;
	//			return;
	//		}
	//	}//exit while(!m_loggedIn)
	//	int menuChoiceNum = menu();// as long as m_quit is not set true, and the user has not logged out(setting m_loggedIn to false), menu() will keep being called.

	//	menuChoice(menuChoiceNum);
	//}// exit while(!m_quit) user must have chosen to quit, program will exit.
	
}

//login helper
bool Executive::verifyUserName(std::string uname) throw(std::exception)
{
	/*std::string uname = "";
	std::cout << "Please enter your user name: ";
	std::cin >> uname;
	while (std::cin.fail() || uname == "") {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Unrecognized input... Please re-enter your user name: ";
		std::cin >> uname;
	}*/
	if (m_knownUsers.empty())
	{
		throw std::exception("Unrecognized user, please create an naccount.\n");
	}
	else {//this loops through known users to find the appropriate User object.
		for (std::vector<std::shared_ptr<User>>::iterator it = m_knownUsers.begin(); it != m_knownUsers.end(); ++it) {
			if ((*it)->m_userName == uname) {
				std::cout << "\nLogin information accepted.\n\n";
				m_currentUser = (*it);
				return(true);
			}
		}
		throw std::exception("Username not recognized... Please re-enter login information or create a new account.\n\n");
	}
}

bool Executive::createAccount()
{
	std::shared_ptr<User> temp = std::make_shared<User>();
	std::cin.get();
	temp->m_realName = stringInput("Please enter your first and last name:");
	temp->m_userName = stringInput("Please choose your user name:");
	for (std::vector<std::shared_ptr<User>>::iterator it = m_knownUsers.begin(); it != m_knownUsers.end(); ++it) {
		if ((*it)->m_userName == temp->m_userName) {
			std::cout << "User name unavailable, please try again.\n\n";
			return(false);
		}
	}
	
	m_knownUsers.push_back(temp);
	return(true);
}



int Executive::menu()
{
	std::cout << "Testing area!!!\n";
	std::cout << "-=============-\n\n";
	std::cout << "1) Create Meeting.\n";
	std::cout << "2) View Meeting.\n";
	std::cout << "3) Logout.\n";
	std::cout << "4) Exit.\n";
	int choice;
	std::cout << "Selection: ";
	std::cin >> choice;
	
	while (choice != 1 && choice != 2 && choice != 3 && choice != 4) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // skip bad input
		std::cin.clear(); // unset failbit
		std::cout << "Please simply choose one of the options (1-4) and press enter/return.\n";
		std::cout << "\nSelection: ";
		std::cin >> choice;
	}
	std::cin.get();//this fixes an output issue.
	return(choice);// choice is passed on to menuChoice()
}

void Executive::menuChoice(int choice)
{
	std::cout << "\nYou chose option " << choice << "\n";
	if (choice == 1)
	{
		//addEvent();
	}
	else if (choice == 2)
	{
		std::cout << "\n **Implement view meeting here ** \n";
	}
	else if (choice == 3)
	{
		m_loggedIn = false;
		return;
	}
	else if (choice == 4)
	{
		m_loggedIn = false;
		m_quit = true;
	}
}

void Executive::addEvent(std::string eventName)
{
	std::shared_ptr<Event> newEvent = std::make_shared<Event>();//allocates the Event object on the heap;
	newEvent->m_name = eventName;// sets the event name.
	m_eventList.push_back(newEvent);
}

void Executive::viewMeetingList()
{
	// loop through all meetings.
	for (std::vector<std::shared_ptr<Event>>::iterator it = m_eventList.begin(); it != m_eventList.end(); ++it) {
		std::cout << "\nMeeting Name: " + (*it)->m_name + ".\n";

		//loop through dates in meeting.
		for (std::vector<std::shared_ptr<Date>>::iterator it1 = (*it)->m_meetDates.begin(); it1 != (*it)->m_meetDates.end(); ++it1)
			std::cout << "Date(s):\t" << (*it1)->m_date + "\n";

	}
}
std::string Executive::stringInput(std::string message) {
	std::string input;
	std::cout << message;

	std::getline(std::cin, input);
	while (std::cin.fail() || input == "") {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Unrecognized input...try again: ";
		std::getline(std::cin, input);
	}
	return(input);
}

