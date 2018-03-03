#pragma once

#include "User.h"
#include <string>
#include <memory>

class User;

class Task
{
public:
	Task();
	Task(std::string name); //creates task and sets m_name = name
	~Task();

	void assignTask(std::weak_ptr<User>); //Assigns a user to m_taskUser
	bool m_isAssigned; //True if task is assigned, else false.
	std::string m_name; //The name of the task, e.g. "Bring Chips."

	std::weak_ptr<User> m_assignedUser; //Points to the user that has accepted this task.


private:


};
