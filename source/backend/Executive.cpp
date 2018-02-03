#include "Executive.h"
Executive::Executive(){
	event_list = new std::vector<Event>();
}
Executive::~Executive(){
	delete event_list;
}
int Executive::get_event_num(){
	//Increment event_num before returning it because this will guarantee unique numbers.
	event_num++;
	return event_num;
}
bool Executive::generate_event(std::string name, std::string date){
	try{
		//Create the event at the back of the list.
		event_list.push_back(Event(name,date,current_user.get_real_name,user,date,get_event_num()));
		//Using the event at the back of the list (that we just created), we create the info and record files that correspond to it.
		std::ofstream file_info_writer(
			"./data/info_"+std::string(event_list.back().get_id_number())+".txt")
			);
		std::ofstream file_record_writer(
			"./data/record_"+std::string(event_list.back().get_id_number())+".txt")
			);
		return true;
	}catch(std::string m){
		return false;
	}
}
