#include "Executive.h"

Executive::Executive(){
	//Initialization of objects
	event_list = new std::vector<Event>();
	
	//If the directory does not already exist, make it.
	if(!does_file_exist(df_event_list)){
		//Create the directories.
		boost::filesystem::create_directory("data");
		boost::filesystem::create_directory("data/events");
		//Generate the file.
		std::ofstream create_directory_and_file(get_file_name(df_event_list));
		create_directory_and_file.close();
	}else{
		//Read the file.
		std::ifstream event_list(get_file_name(df_event_list));
		event_list >> event_num;
		event_list.close();
	}

	if (!does_file_exist(df_user)) { //Creating the user.txt file, if it doesn't exist already
	    boost::filesystem::create_directory("data"); //Redundancy; just in case it hasn't been created already
	    std::ofstream create_user_file(get_file_name(df_user)); //Create the user.txt file
	    create_user_file.close();
	}

	//Rebuild all information from .txt files if possible
	std::string viewing_file;
	for(auto&& it : boost::filesystem::directory_iterator(boost::filesystem::path("./data/events"))){
		//This iterates over every file in the directory
		//The name of the file is accessed with it.filename()
		//We will look at the first four characters
		viewing_file = it.path().filename().string();
		rebuild_event(viewing_file);
	}
	//Sort the events by date.
	sort_event_list();
}
Executive::~Executive(){
	delete event_list;
}
int Executive::get_event_num(){
	//Increment event_num before returning it because this will guarantee unique numbers.
	event_num++;
	//Save the event_num in this session.
	std::ofstream event_list(get_file_name(df_event_list));
	event_list << event_num;
	event_list.close();
	
	return event_num;
}
bool Executive::generate_event(std::string name, std::string date){
	try{		
		//Create the event at the back of the vector.
		event_list->push_back(Event(name,date,current_user -> getRealName(),get_event_num()));
		
		//This is a reference to the event we want to input data for.
		Event &new_event = event_list->back();
		
		//Using the event at the back of the list (that we just created), we create the info and record files that correspond to it.
		std::ofstream file_info_writer(get_file_name(df_event,std::to_string((new_event.get_id_number()))));
		std::ofstream file_record_writer(get_file_name(df_record,std::to_string((new_event.get_id_number()))));
			
		//Now, we write the basic information of the event to the file in question.
		file_info_writer << new_event.get_name() << '\n' << new_event.get_date() << '\n' << new_event.get_creator() << '\n' << new_event.get_id_number();
		
		//Close the files.
		file_info_writer.close();
		file_record_writer.close();
		
		//Event created.
		return true;
	}catch(std::logic_error m){
		//The event was a holiday was it? Return false.
		return false;
	}
}
bool Executive::does_file_exist(DataFile type, std::string identifer){
	//Returns whether a file exists or not.
	return (boost::filesystem::exists(get_file_name(type,identifer)));
}
std::string Executive::get_file_name(DataFile type, std::string identifer){
	//The name of the file we are looking for.
	std::string file_name = "./data/"; 
	
	//Add the "prefix" of the file.
	switch(type){
		case df_event:
			file_name+="events/info_";
		break;
		case df_user:
			file_name+="user";
		break;
		case df_event_list:
			file_name+="EventList";
		break;
		case df_record:
			file_name+="record_";
		break;
	}
	
	//Finally, add the identifer and .txt extension to the file.
	file_name += (identifer + ".txt");
	
	//Returns whether a file exists or not.
	return file_name;
}
bool Executive::delete_event(int event_id){
	if(!does_file_exist(df_event,std::to_string(event_id))){
		//The event with that id does not even exist.
		return false;
	}else{
		//First, we delete the event from our vector.
		for(auto&& x = event_list->begin(); x != event_list->end(); x++){
			//Iterate over every element in the vector.
			if(x->get_id_number() == event_id){
				//This element is the one to be removed.
				event_list->erase(x);
				break;
			}
		}
		//We remove the files from the data folder.
		boost::filesystem::remove(get_file_name(df_event,std::to_string(event_id)));
		boost::filesystem::remove(get_file_name(df_record,std::to_string(event_id)));
		//We have removed the event from existence.
		return true;
	}
}
void Executive::rebuild_event(std::string filename){
	std::ifstream text_file("./data/events/" + filename);
	
	int num;
	std::string name,date,creator,temp;
	
	if(!text_file.is_open()){
		throw std::logic_error("File does not exist");
	}
	
	//Put the information in various lines into these variables.
	std::getline(text_file,name);
	std::getline(text_file,date);
	std::getline(text_file,creator);
	//temp stores the int as a string, it will be converted.
	std::getline(text_file,temp);
	num = std::stoi(temp);
	//Generate the event.
	event_list->push_back(Event(name,date,creator,num));
}
std::vector<Event>& Executive::get_event_list(){
	return (*event_list);
}
void Executive::sort_event_list(){
	std::sort(event_list->begin(),event_list->end());
}
