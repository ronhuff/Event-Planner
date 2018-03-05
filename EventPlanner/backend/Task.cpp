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

bool Task::assignTask(std::string user)
{
	m_assignName = user;
	return(m_assignName == user);
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