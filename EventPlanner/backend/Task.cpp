#include "stdafx.h"
#include "Task.h"



Task::Task()
{
	m_isAssigned = false;
}

Task::Task(std::string name) {
	m_name = name;
}


Task::~Task()
{

}

void Task::assignTask(std::weak_ptr<User> user)
{
	m_assignedUser = user;
	m_isAssigned = true;
}