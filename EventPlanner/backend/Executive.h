#pragma once

#include "Event.h"
#include "Date.h"
#include <vector>
#include <memory>
#include <limits>
#include <iostream>
#include <exception>

class Executive
{
public:
	Executive();
	~Executive();

	void run();
	int menu();
	void menuChoice(int);
	void addEvent();

	std::vector<std::shared_ptr<Event>> m_eventList;
	std::vector<std::shared_ptr<User>> m_knownUsers; //if user exists here then they can login, else they must create account.




	std::shared_ptr<User> m_currentUser;

	bool m_quit;
	bool m_loggedIn;

	bool login();

private:

	//helper

	bool verifyUserName() throw(std::exception);

	std::string stringInput(std::string);
	bool createAccount();
	void viewMeetingList();
};

