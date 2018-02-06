#ifndef USER_H
#define USER_H

#include <string>

/*
 * TO BE IMPLEMENTED BY: DOUG
 */

class User{
	public:
		User();
		User(std::string uid, std::string pnm);
		std::string get_user_name();
		std::string get_real_name();
		//void change_user_name(); //Optional Feature
		bool operator==(User rhs);
	private:
		std::string user_name;
		std::string real_name;
		//Attending events (list of ids)
};

#endif
