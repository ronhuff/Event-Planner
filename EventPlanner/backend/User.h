#pragma once

#include "Event.h"
#include <string>
#include <vector>
#include <memory>

class Event;

class User
{
public:
	User();
	~User();

	std::string m_userName;
	std::string m_realName;
	
	std::vector<std::weak_ptr<Event>> events; //The events the user is attending.  Perhaps unnecessary.
};

