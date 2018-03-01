#pragma once

#include <string>
#include "backend/User.h"

class Task
{
public:
	Task();
	Task(std::string name);
	~Task();

	bool assignTask(User*); //Assigns a user to m_taskUser
	bool m_isAssigned;
	std::string m_name; //The name of the task, e.g. "Bring Chips."

	User* m_taskUser; //Points to the user that has accepted this task.


private:
	
	
};

