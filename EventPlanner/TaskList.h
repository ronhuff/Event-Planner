#pragma once

#include "Task.h"
#include <vector>

class TaskList
{
public:
	TaskList();
	~TaskList();

	bool addTask(Task*);

private:

	int m_numTasks;
	int m_numAvailTasks;

	std::vector<Task*> m_tasks;

};
