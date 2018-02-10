#ifndef USER_H
#define USER_H

#include <string>
#include <list>

/*
 * TO BE IMPLEMENTED BY: DOUG
 */

class User {
	public:
	    /**
	     * The default constructor. Initializes user_name and real_name to the empty string ("");
	     * attending_events points to a list containing -1
	     * @pre none
	     * @post user_name == ""
	     * @post user_name == ""
	     * @post attending_events == new std::list<int>()
	     */
		User();

	    /**
	     * Non-empty constructor. Initializes user_name and real_name to nonempty strings.
	     * attending_events points to a list containing -1
	     * @param std::string uid -- String that user_name gets initialized to
	     * @param std::string pnm -- String that real_name gets initialized to
	     * @pre: uid and pnm are valid strings
	     * @post: user_name == uid
	     * @post: real_name == pnm
	     * @post: attending_events == new std::list<int>()
	     */
		User(std::string uid, std::string pnm);

	    /**
	     * User destructor; deallocates the data pointed to by std::list<int> attending_events
	     * @pre none
	     * @post data pointed to by attending_events is deleted
	     */
		~User();

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
		User(std::string uid, std::string pnm, std::list<int> atev);

	    /**
	     * Retriever method for user_name member.
	     * @pre: none
	     * @post: none
	     * @return: std::string -- user_name
	     */
		std::string getUserName() const;

	    /**
	     * Retriever method for real_name member.
	     * @pre: none
	     * @post: none
	     * @return: std::string -- real_name
	     */
		std::string getRealName() const;
		
	    /**
	     * Overloaded == operator for User objects; compares user_name members.
	     * @param User rhs -- Some User object
	     * @pre: rhs is a valid user object
	     * @post: none
	     * @return: (user_name == rhs.user_name)
       	     */
		bool operator==(User rhs) const;

	    /**
	     * Retriever method for attending_events member
	     * @pre: none
	     * @post: none
	     * @return: std::list<int>* -- attending_events
	     */
		std::list<int>* getAttendingEvents();

	    /**
	     * Method for adding an event to attending_events
	     * @param int event_id -- event_id to add to attending_events
	     * @pre event_id is valid; that is, it references an actual event
	     * @post event_id is added to attending_events
	     */
		void addEvent(int event_id);

	    /**
	     * Method for removing an event from attending_events
	     * @param int event_id -- event_id to remove from attending events
	     * @pre event_id exists within attending_events
	     * @post event_id is removed from attending_events
	     */
		void removeEvent(int event_id);
	
		//void change_user_name(); //Optional Feature
	private:
		std::string user_name; /**<String variable which holds the unique identifier of the User */
		std::string real_name; /**<String variable which holds the proper identifier of the User */
		std::list<int>* attending_events; /**<Pointer to a list which contains the event IDs that the User is attending */
};

#endif
