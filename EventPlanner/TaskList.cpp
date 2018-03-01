#include "TaskList.h"



TaskList::TaskList(){
	m_numTasks = 0;
	m_numAvailTasks = 0;
}


TaskList::~TaskList(){}

bool TaskList::addTask(Task* newTask){
	m_tasks->push_back(newTask);
	return(m_tasks->back() == newTask);
}

bool TaskList::createTask(){
	std::string taskName;
	std::cout << "Please enter a brief description of the task.\n";
	std::cout << "(e.g. \"Bring Snacks,\" \"Prepare Presentation,\" etc.)\n";
	std::cout << "Task Description: ";
	std::cin >> taskName;

	while(std::cin.fail()) {//naive input control.
		std::cin.clear(); // unset failbit
		std::cin.ignore();
		std::cout << "\nError: Input not accepted, please re-enter description.\n";
		std::cin >> taskName;
	}
	return(addTask(new Task(taskName)));
}