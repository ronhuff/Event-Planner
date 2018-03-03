#include "stdafx.h"
#include "TaskList.h"



TaskList::TaskList() {
	m_numTasks = 0;
	m_numAvailTasks = 0;
}


TaskList::~TaskList() {}

bool TaskList::addTask(std::shared_ptr<Task> newTask) {
	int size = m_tasks.size();
	m_tasks.push_back(newTask);
	return((size + 1) == m_tasks.size());
}

bool TaskList::createTask() {
	std::string taskName;
	std::cout << "Please enter a brief description of the task.\n";
	std::cout << "(e.g. \"Bring Snacks,\" \"Prepare Presentation,\" etc.)\n";
	std::cout << "Task Description: ";
	std::cin >> taskName;

	while (std::cin.fail()) {//naive input control.
		std::cin.clear(); // unset failbit
		std::cin.ignore();
		std::cout << "\nError: Input not accepted, please re-enter description.\n";
		std::cin >> taskName;
	}
	return(addTask(std::make_shared<Task>(taskName))); // this creates the shared ptr. for the new task and addTask() will push it to the m_tasks
}