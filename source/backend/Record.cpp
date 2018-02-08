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
    userList.clear();
}

void Record::add_user(User uid)
{
    //add user to the list.
    userList.push_front (uid);
}

void Record::remove_user(User uid)
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

std::list<User> Record::getUserList()
{
    return userList;
}
