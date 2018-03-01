#include "Task.h"



Task::Task()
{
	m_taskUser = nullptr;
	m_isAssigned = false;
}

Task::Task(std::string name) {
	m_name = name;
}


Task::~Task()
{

}

bool Task::assignTask(User* user)
{
	m_taskUser = user;
	return(m_taskUser == user);
}