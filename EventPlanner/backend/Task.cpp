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

std::ostream& operator<<(std::ostream& out, Task& task)
{
	out << task.m_name << task.m_isAssigned;
	return(out);
	// TODO: insert return statement here
}

std::istream& operator>>(std::istream& in, Task& task)
{
	in >> task.m_name >> task.m_isAssigned;
	return(in);
}