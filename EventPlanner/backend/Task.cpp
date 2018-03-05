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
	out << task.m_name << "\n";
	if (task.m_isAssigned == true)
	{
		out << "1 \n";
	}
	else
	{
		out << "0 \n";
	}
	return(out);
	// TODO: insert return statement here
}

std::istream& operator>>(std::istream& in, Task& task)
{
	std::getline(in, task.m_name);
	std::string temp;
	std::getline(in, temp);
	if (temp == "1 ")
	{
		task.m_isAssigned = true;
	}
	else if (temp == "0 ")
	{
		task.m_isAssigned = false;
	}
	return(in);
}