#pragma once

#include <string>
#include "User.h"

class Task
{
public:
	Task();
	Task(std::string name); //creates task and sets m_name = name
	~Task();

	bool assignTask(User*); //Assigns a user to m_taskUser
	bool m_isAssigned; //True if task is assigned, else false.
	std::string m_name; //The name of the task, e.g. "Bring Chips."

	User* m_taskUser; //Points to the user that has accepted this task.


private:
	
	
};

