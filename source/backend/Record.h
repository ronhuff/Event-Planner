#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <list>

class Record{
	public:
		Record();
		Record(std::string t);
		~Record();
		void add_user(std::string uid);
		void remove_user(std::string uid);
		std::list<std::string>* getUserList();
		std::string getTime();

	private:
		std::string time;
		std::list<std::string>* userList;
};

#endif
