#ifndef USER_H
#define USER_H

#include <string>

/*
 * TO BE IMPLEMENTED BY: DOUG
 */

class User{
	public:
	    /**
	     * The default constructor. Initializes user_name and real_name to the empty string ("").
	     * @pre none
	     * @post user_name == ""
	     * @post user_name == ""
	     */
		User();

	    /**
	     * Non-empty constructor. Initializes user_name and real_name to nonempty strings.
	     * @param std::string uid -- String that user_name gets initialized to
	     * @param std::string pnm -- String that real_name gets initialized to
	     * @pre: uid and pnm are valid strings
	     * @post: user_name == uid
	     * @post: real_name == pnm
	     */
		User(std::string uid, std::string pnm);

	    /**
	     * Retriever method for user_name member.
	     * @pre: none
	     * @post: none
	     * @return: std::string -- user_name
	     */
		std::string get_user_name();

	    /**
	     * Retriever method for real_name member.
	     * @pre; none
	     * @post: none
	     * @return: std::string -- real_name
	     */
		std::string get_real_name();
		
	    /**
	     * Overloaded == operator for User objects; compares user_name members.
	     * @param User rhs -- Some User object
	     * @pre: rhs is a valid user object
	     * @post: none
	     * @return: (user_name == rhs.user_name)
       	     */
		bool operator==(User rhs);
		//void change_user_name(); //Optional Feature
	private:
		std::string user_name; /**<String variable which holds the unique identifier of the User */
		std::string real_name; /**<String variable which holds the proper identifier of the User */

		//Attending events (list of ids)
};

#endif
