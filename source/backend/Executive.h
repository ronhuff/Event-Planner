#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include "UserList.h"
#include "Event.h"
#include "Record.h"
#include <fstream>
#include <string>

class Executive{
	public:
		Executive();
		~Executive();
		int get_event_num();
		
		void write_event(int event_id);
		void write_user(std::string user_name);
		
		void delete_event(int event_id);
	private:
		int event_num;
};

#endif
