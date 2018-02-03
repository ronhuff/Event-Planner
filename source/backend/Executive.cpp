#include "Executive.h"

Executive::Executive(){
	//Initialization of objects
	event_list = new std::vector<Event>();
	
	if(!does_file_exist(df_event_list)){
		std::ifstream create_directory_and_file("./data/EventList.txt");
		create_directory_and_file.close();
	}
			
	//Rebuild all information from .txt files
	for(auto&& it : directory_iterator(boost::filesystem::path("./data/"))){
		//This iterates over every file in the directory
		//The name of the file is accessed with it.filename()
	}
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
		//Create the event at the back of the vector.
		event_list->push_back(Event(name,date,current_user.get_real_name(),get_event_num()));
		
		//This is a reference to the event we want to input data for.
		Event &new_event = event_list->back();
		
		//Using the event at the back of the list (that we just created), we create the info and record files that correspond to it.
		std::ofstream file_info_writer(
			"./data/info_"
			+ std::to_string((new_event.get_id_number()))
			+ std::string(".txt")
			);
		std::ofstream file_record_writer(
			"./data/record_"
			+ std::to_string((new_event.get_id_number()))
			+ std::string(".txt")
			);
			
		//Now, we write the basic information of the event to the file in question.
		file_info_writer << new_event.get_name() << '\n' << new_event.get_date() << '\n' << new_event.get_creator() << '\n' << new_event.get_id_number();
		
		//Close the files.
		file_info_writer.close();
		file_record_writer.close();
		
		return true;
	}catch(std::string m){
		return false;
	}
}
bool Executive::does_file_exist(DataFile type, std::string identifer){
	//The name of the file we are looking for.
	std::string file_name = "./data/"; 
	
	//Add the "prefix" of the file.
	switch(df_event_list){
		case df_event:
			file_name+="info_";
		break;
		case df_user:
			file_name+="user_";
		break;
		case df_event_list:
			file_name+="EventList";
		break;
	}
	
	//Finally, add the identifer and .txt extension to the file.
	file_name += (identifer + ".txt");
	
	//Returns whether a file exists or not.
	return (boost::filesystem::exists(file_name));
}

