#include "Task.h"



Task::Task()
{
	m_taskUser = nullptr;

}


Task::~Task()
{

}

bool Task::assignTask(User* user)
{
	m_taskUser = user;
	return(m_taskUser == user);
}