#include "User.h"
/*
 * TO BE IMPLEMENTED BY: DOUG
 */
User::User(){
	
}
User::User(std::string uid, std::string pnm){

}
std::string User::get_user_name(){
	return user_name;
}
std::string User::get_real_name(){
	return real_name;
}
bool User::operator==(User rhs){
	return (rhs.user_name == user_name);
}
