#pragma once

#include <vector>
#include "User.h"
#include "Date.h"
#include "TaskList.h"
#include <memory>

class User;
class TaskList;
class Date;

class Event
{
public:
	Event();
	~Event();

	std::string m_name;

	std::shared_ptr<User> m_creator;

	std::vector<std::shared_ptr<User>> m_attendees;
	std::shared_ptr<TaskList> m_tasks;

	std::vector<std::shared_ptr<Date>> m_meetDates;

	int m_id;

};

