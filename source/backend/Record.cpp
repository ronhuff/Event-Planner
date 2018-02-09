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
	delete userList;
}

void Record::add_user(std::string uid)
{
    //add user to the list.
    userList.push_front (uid);
}

void Record::remove_user(std::string uid)
{
    //remove an user from the list, if the list is not empty.
    if(userList.empty())
    {
    }
    else
    {
        UserList.remove(uid);
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
