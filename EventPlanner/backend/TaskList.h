#pragma once

#include <iostream>
#include <string>
#include <limits>
#include "Task.h"
#include <vector>


class TaskList{
public:
	TaskList();
	~TaskList();

	bool addTask(Task*);
	bool createTask(); // Gets name of task from user and attempts to call addTask(new Task(name));

	int m_numTasks;
	int m_numAvailTasks;
	std::vector<Task*>* m_tasks; // contains all tasks related to this task list.

	//ADD VIEW METHODS HERE, e.g. viewTasks(bool isCreator);

private:

	

};
