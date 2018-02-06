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
    UserList.clear();
}

void Record::add_user(User uid)
{
    //add user to the list.
    UserList.push_front (uid);
}

void Record::remove_user(User uid)
{
    //remove an user from the list, if the list is not empty.
    if(UserList.empty())
    {
    }
    else
    {
        UserList.remove(uid);
    }
}

std::list<User> Record::getUserList()
{
    return UserList;
}
