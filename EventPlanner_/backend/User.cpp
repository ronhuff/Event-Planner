#include "User.h"
/*
 * TO BE IMPLEMENTED BY: DOUG
 */

User::User() : user_name(""), real_name(""), attending_events(new std::list<int>()) {}


User::User(std::string uid, std::string pnm) : user_name(uid), real_name(pnm), attending_events(new std::list<int>()) {}


User::User(std::string uid, std::string pnm, std::list<int> atev) : user_name(uid), real_name(pnm), attending_events(new std::list<int>(atev)) {}

User::~User() {
    if (attending_events != nullptr) {
	delete attending_events;
	attending_events = nullptr;
    }
}

std::string User::getUserName() const {
	return (user_name);
}

std::string User::getRealName() const {
	return (real_name);
}


bool User::operator==(User rhs) const {
	return (rhs.user_name == user_name);
}
std::list<int>* User::getAttendingEvents() {
	return (attending_events);
}
void User::addEvent(int event_id) {
    attending_events -> push_back(event_id);
}
void User::removeEvent(int event_id) {
    attending_events -> remove(event_id);
}


