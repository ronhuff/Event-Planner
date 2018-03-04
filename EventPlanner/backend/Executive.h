#pragma once

#include "Event.h"
#include "Date.h"
#include <vector>
#include <memory>
#include <limits>
#include <iostream>
#include <exception>
#include "../interface/CLI.h"

class Date;
class CLI;

class Executive
{
public:
	Executive();
	~Executive();

	void run(std::shared_ptr<Executive>);
	int menu();
	void menuChoice(int);
	void addEvent(std::string eventName);

	std::vector<std::shared_ptr<Event>> m_eventList;
	std::vector<std::shared_ptr<User>> m_knownUsers; //if user exists here then they can login, else they must create account.

	int m_numMeetings;
	std::vector<int> meetingIDs;




	std::shared_ptr<User> m_currentUser;

	bool m_quit;
	bool m_loggedIn;

	bool login();

	std::shared_ptr<CLI> cli;

	//helper

	bool verifyUserName(std::string uname) throw(std::exception);

	std::string stringInput(std::string);
	bool createAccount();
	void viewMeetingList();
};

