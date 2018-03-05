#pragma once

#include <string>
#include "User.h"

class Task
{
public:
	Task();
	Task(std::string name); //creates task and sets m_name = name
	~Task();

	bool assignTask(std::string); //Assigns a user to m_taskUser
	bool m_isAssigned; //True if task is assigned, else false.

	std::string m_assignName; // The name of the assignee.

	std::string m_name; //The name of the task, e.g. "Bring Chips."


	friend std::ostream& operator<<(std::ostream& out, Task& task);
	friend std::istream& operator>>(std::istream& in, Task& task);
private:
	
	
};

