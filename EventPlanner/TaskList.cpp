#include "TaskList.h"



TaskList::TaskList()
{
}


TaskList::~TaskList()
{
}

bool TaskList::addTask(Task* newTask)
{
	m_tasks.push_back(newTask);
	return(m_tasks.back() == newTask);
}