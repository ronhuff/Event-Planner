#ifndef RECORD_H
#define RECORD_H


class Record{
	public:
		Record();
		Record(int in_id, std::string t);
		~Record();
		
		void add_user(User u);
		void remove_user(User u);
	private:
		std::string time;
		//list of users
		//int id; //may not need this
};

#endif
