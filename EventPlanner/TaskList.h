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
	bool createTask();

	int m_numTasks;
	int m_numAvailTasks;
	std::vector<Task*>* m_tasks;
private:

	

};
