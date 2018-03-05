#include "Record.h"

Record::Record()
{
    //This should not be call.
}

Record::Record(std::string t, std::string d)
{
	userList = std::list<std::string>();
    time = t;
	date = d;
}

Record::~Record()
{

}

void Record::addUser(std::string uid)
{
    //add user to the list.
    userList.push_back (uid);
    userList.sort();
    userList.unique();
}

void Record::removeUser(std::string uid)
{
    //remove an user from the list, if the list is not empty.
    if(userList.empty())
    {
    }
    else
    {
        userList.remove(uid);
    }
}

std::list<std::string> Record::getUserList()
{
    return userList;
}

std::string Record::getTime()
{
	return (time);
}

std::string Record::getDate() {
	return(date);
}