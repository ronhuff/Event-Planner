#include "Record.h"

Record::Record()
{
    //This should not be call.
}

Record::Record(std::string t)
{
    time = t;
}

Record::~Record()
{
    //Remove all users.
	userList -> clear();
	delete userList;
}

void Record::addUser(std::string uid)
{
    //add user to the list.
    userList->push_back (uid);
}

void Record::removeUser(std::string uid)
{
    //remove an user from the list, if the list is not empty.
    if(userList->empty())
    {
    }
    else
    {
        userList->remove(uid);
    }
}

std::list<std::string>* Record::getUserList()
{
    return userList;
}

std::string Record::getTime()
{
	return (time);
}
