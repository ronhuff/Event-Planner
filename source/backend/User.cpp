#include "User.h"
/*
 * TO BE IMPLEMENTED BY: DOUG
 */

/**
 * The default constructor. Initializes user_name and real_name to the empty string ("");
 * attending_events points to a list containing -1
 * @pre none
 * @post user_name == ""
 * @post user_name == ""
 * @post attending_events == new std::list<int> {-1}
 */
User::User() : user_name(""), real_name(""), attending_events(new std::list<int> {-1}) {}

/**
 * Non-empty constructor. Initializes user_name and real_name to nonempty strings.
 * attending_events points to a list containing -1
 * @param std::string uid -- String that user_name gets initialized to
 * @param std::string pnm -- String that real_name gets initialized to
 * @pre: uid and pnm are valid strings
 * @post: user_name == uid
 * @post: real_name == pnm
 * @post: attending_events == new std::list<int> {-1}
 */
User::User(std::string uid, std::string pnm) : user_name(uid), real_name(pnm), attending_events(new std::list<int> {-1}) {}

/**
 * Non-empty contructor. Initializes user_name, real_name, and attending_events
 * @param std::string uid -- String that user_name gets initialized to
 * @param std::string pnm -- String that real_name gets initialized to
 * @param std::list<int> atev -- Integer list that attending_events gets initialized to
 * @pre uid and pnm are valid strings
 * @pre atev is a valid integer list container
 * @post: user_name == uid
 * @post: real_name == pnm
 * @post: attending_events has all elemets from atev
 */
User::User(std::string uid, std::string pnm, std::list<int> atev) : user_name(uid), real_name(pnm) attending_events(new std::list<int>(atev)) {}

/**
 * Retriever method for user_name member.
 * @pre: none
 * @post: none
 * @return: std::string -- user_name
 */
std::string User::getUserName() const {
	return (user_name);
}

/**
 * Retriever method for real_name member.
 * @pre: none
 * @post: none
 * @return: std::string -- real_name
 */
std::string User::getRealName() const {
	return (real_name);
}

/**
 * Overloaded == operator for User objects; compares user_name members.
 * @param User rhs -- Some User object
 * @pre: rhs is a valid user object
 * @post: none
 * @return: (user_name == rhs.user_name)
 */
bool User::operator==(User rhs) const {
	return (rhs.user_name == user_name);
}

/**
 * Retriever method for attending_events member
 * @pre: none
 * @post: none
 * @return: std::list<int>* -- attending_events
 */
std::list<int>* User::getAttendingEvents() {
	return (attending_events);
}
