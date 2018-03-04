#pragma once

#include <iostream>
#include <string>
#include <limits>
#include "Task.h"
#include <vector>
#include <memory>
#include <fstream>


class TaskList{

public:
	TaskList();
	~TaskList();

	bool addTask(std::shared_ptr<Task> task);
	bool createTask(); // Gets name of task from user and attempts to call addTask(new Task(name));

	int m_numTasks;
	int m_numAvailTasks;
	int m_eventId;
	std::vector<std::shared_ptr<Task>> m_tasks; // contains all tasks related to this task list.


	//ADD VIEW METHODS HERE, e.g. viewTasks(bool isCreator);
	friend std::ostream& operator<<(std::ostream& out, TaskList& tList);
	friend std::istream& operator>>(std::istream& in, TaskList& tlist);

private:

	

};
