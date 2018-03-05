//#include "../stdafx.h"
#include "TaskList.h"



TaskList::TaskList() {
	m_numTasks = 0;
	m_numAvailTasks = 0;
}


TaskList::~TaskList() {}

bool TaskList::addTask(std::shared_ptr<Task> newTask) {
	int size = m_tasks.size();
	m_tasks.push_back(newTask);
	m_numTasks++;
	m_numAvailTasks++;
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

bool TaskList::removeTask(int taskNum)
{
	m_tasks.erase(m_tasks.begin() + (taskNum - 1));
	return true;
}

bool TaskList::assignUser(int taskNum, std::string user)
{
	m_tasks.at(taskNum)->m_assignName = user;
	m_tasks.at(taskNum)->m_isAssigned = true;
	return false;
}

bool TaskList::unassignUser(int taskNum)
{
	m_tasks.at(taskNum)->m_assignName = "";
	m_tasks.at(taskNum)->m_isAssigned = false;
	return true;
}

void TaskList::displayTaskList()
{
	std::cout << "Tasklist for meeting number: " + std::to_string(this->m_eventId) << std::endl << std::endl;
	for (std::vector<std::shared_ptr<Task>>::iterator taskit = m_tasks.begin(); taskit != m_tasks.end(); ++taskit)
	{
		std::cout << "Task: ";
		std::cout << (*taskit)->m_name << "\n";
		std::cout << "Assignee: ";
		if ((*taskit)->m_isAssigned == false)
		{
			std::cout << "None. Feel free to sign up!\n";
		}
		else
		{
			if ((*taskit)->m_assignName.length() > 1)
			{
				std::cout << (*taskit)->m_assignName + "\n";
			}
			else
			{
				std::cout << "" << std::endl;
				//print to log no error appears.
			}
		}
	}
}

std::ostream & operator<<(std::ostream & out, TaskList & tList)
{
	// TODO: insert return statement here
	out << tList.m_eventId << "\n" << tList.m_numTasks << "\n" << tList.m_numAvailTasks << "\n";
	for (int i = 0; i < tList.m_numTasks; i++)
	{
		out << *tList.m_tasks.at(i);
	}
	return(out);
}

std::istream & operator>>(std::istream & in, TaskList & tList)
{
	/*in >> tList.m_eventId >> tList.m_numTasks >> tList.m_numAvailTasks;*/
	std::string id;
	std::string numTasks;
	std::string numAvailTasks;

	std::getline(in, id, '\n');
	std::getline(in, numTasks, '\n');
	std::getline(in, numAvailTasks, '\n');
	
	tList.m_numTasks = std::stoi(id);
	tList.m_numTasks = std::stoi(numTasks);
	tList.m_numAvailTasks = std::stoi(numAvailTasks);

	
	for (int i = 1; i <= tList.m_numTasks; i++)
	{
		std::shared_ptr<Task> temp = std::make_shared<Task>();
		in >> *temp;
		tList.m_tasks.push_back(temp);
	}
	return(in);
	// TODO: insert return statement here
}
