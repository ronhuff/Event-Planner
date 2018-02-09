#include "Executive.h"

Executive::Executive(){
	//Initialization of objects
	event_list = new std::vector<Event>();
	current_user = nullptr;

	/* DIRECTORY INITIALIZATION */

	if (!boost::filesystem::is_directory("data")) { //data directory does not exist; create it and sub-directories
	    boost::filesystem::create_directory("data");
	    boost::filesystem::create_directory("data/events");
	    boost::filesystem::create_directory("data/records");
	    boost::filesystem::create_directory("data/users");
	}

	if (!boost::filesystem::is_directory("data/events")) {
	    boost::filesystem::create_directory("data/events");
	}

	if (!boost::filesystem::is_directory("data/records")) {
	    boost::filesystem::create_directory("data/records");
	}

	if (!boost::filesystem::is_directory("data/users")) {
	    boost::filesystem::create_directory("data/users");
	}

	/* EVENT LIST INITIALIZATION */

	//If the file does not already exist, make it.
	if(!does_file_exist(df_event_list)){
		//Generate the file.
		std::ofstream create_directory_and_file(get_file_name(df_event_list));
		create_directory_and_file.close();
	}else{
		//Read the file.
		std::ifstream event_list(get_file_name(df_event_list));
		event_list >> event_num;
		event_list.close();
	}

	//Rebuild all information from .txt files if possible
	std::string viewing_file;
	for(auto&& it : boost::filesystem::directory_iterator(boost::filesystem::path("./data/events"))){
		//This iterates over every file in the directory
		//The name of the file is accessed with it.filename()
		viewing_file = it.path().filename().string();
		rebuild_event(viewing_file);
	}
	//Sort the events by date.
	sort_event_list();
}
Executive::~Executive(){
	delete event_list;
	if (current_user != nullptr) {
	    delete current_user;
	}
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
		event_list->push_back(Event(name,date,*current_user,get_event_num()));
		
		//This is a reference to the event we want to input data for.
		Event &new_event = event_list->back();
		
		//Using the event at the back of the list (that we just created), we create the info and record files that correspond to it.
		std::ofstream file_info_writer(get_file_name(df_event,std::to_string((new_event.get_id_number()))));
		std::ofstream file_record_writer(get_file_name(df_record,std::to_string((new_event.get_id_number()))));
			
		//Now, we write the basic information of the event to the file in question.
		file_info_writer << new_event.get_name() << '\n' << new_event.get_date() << '\n' << new_event.get_creator_user_name() << '\n' << new_event.get_creator_real_name() << '\n' << new_event.get_id_number();
		
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
			file_name+="users/user_";
		break;
		case df_event_list:
			file_name+="EventList";
		break;
		case df_record:
			file_name+="records/record_";
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
	std::string name,date,creator_user_name,creator_real_name,temp;
	
	if(!text_file.is_open()){
		throw std::logic_error("File does not exist");
	}
	
	//Put the information in various lines into these variables.
	std::getline(text_file,name);
	std::getline(text_file,date);
	std::getline(text_file,creator_user_name);
	std::getline(text_file,creator_real_name);
	//temp stores the int as a string, it will be converted.
	std::getline(text_file,temp);
	num = std::stoi(temp);
	//Generate the event.
	event_list->push_back(Event(name,date,User(creator_user_name,creator_user_name),num));
}
std::vector<Event>& Executive::get_event_list(){
	return (*event_list);
}
void Executive::sort_event_list(){
	std::sort(event_list->begin(),event_list->end());
}

bool Executive::setCurrentUser(std::string uid) {
    if(does_file_exist(df_user, uid)) {

	std::string pnm = "";
	std::string attending_string = "";
	std::list<int> attending_list;

	std::ifstream user_file;
	user_file.open(get_file_name(df_user, uid));

	std::getline(user_file, pnm, '\n'); //Store the proper name
	std::getline(user_file, attending_string, '\n'); //Get string of attending events

	storeIntsFromString(attending_list, attending_string); //Store the attending event list

	current_user = new User(uid, pnm, attending_list);

	user_file.close();

	return (true);

    }
    else { //File does not exist; return false

	current_user = new User();
	return (false);

    }

}

<<<<<<< HEAD
void Executive::storeIntsFromString(std::list<int> &int_list, std::string int_string) {
    std::stringstream ss;
    std::string temp_string = "";
    int temp_int = 0;
    ss.str(int_string);

    while (!ss.eof()) {
	std::getline(ss, temp_string, ',');
	temp_int = std::stoi(temp_string);
	int_list.push_back(temp_int);
    }
}

User* Executive::getCurrentUser() {
    return (current_user);
}

bool Executive::writeCurrentUser() {

    std::string uid = current_user -> getUserName();
    if (uid == "") {
	return (false);
    }
    else {
	std::string pnm = current_user -> getRealName();
	std::list<int>* att_ev = current_user -> getAttendingEvents();

	boost::filesystem::remove(get_file_name(df_user, uid)); //Remove the file to stage for new creation
	std::ofstream user_file;
	user_file.open(get_file_name(df_user, uid));

	user_file << pnm << '\n';

	for (std::list<int>::iterator it = att_ev -> begin(); it != att_ev -> end(); ++it) {
	    if (it == att_ev -> begin())
		user_file << *it;
	    else
		user_file << ',' << *it;
	}
	user_file << '\n';

	user_file.close();

	return (true);
    }
}

std::list<Record>* Executive::readRecord(int event_id)
{
	std::string filename = get_file_name(df_record, std::to_string(event_id));
	int flag = 0;
	std::list<Record>* recordList = new std::list<Record>;
	std::string tempTime, tempString;
	
	//open file
	std::ifstream recordFile("./data/records/" + filename);
	Record tempRecord;
	
	//throw if the file does not exist
	if(!recordFile.is_open())
	{
		throw std::logic_error("Record file does not exist.");
	}
	
	//read through the file
	while(!recordFile.eof())
	{
		recordFile >> flag;
		if(flag == 0)
		{
			recordFile >> tempTime;
			tempRecord = Record(tempTime);
		}
		recordFile >> flag;
		while(flag != 0)
		{
			recordFile >> tempString;
			tempRecord.add_user(tempString);
			recordFile >> flag;
		}
		recordList->push_front(tempRecord);
	}
	
	recordFile.close();
	
	return recordList;
}


void  Executive::writeRecord(int eid, std::list<Record>* List)
{
	std::string filename = get_file_name(df_record, std::to_string(eid));
	std::list<std::string>* tempUserlist;
	std::string tempTime;
	
	//if the previous file exists, delete it
	if(does_file_exist(df_record, std::to_string(eid)))
	{
		boost::filesystem::remove(filename);
	}
	
	//start write a new file with the same filename
	std::ofstream outF ("./Data/records/" + filename);
	for(auto&& it = List->begin(); it != List->end(); it++)
	{
		//write the time block
		tempTime = it->getTime();
		outF << 0 << " " << tempTime << std::endl;
		tempUserlist = it->getUserList();
		
		for(auto it2 = tempUserlist->begin(); it2 != tempUserlist->end(); it2++)
		{
			//write the users
			outF << 1 << " " << *it2 <<std::endl;
		}
	}
	
}

bool Executive::removeRecord(int eid)
{
	//get filename
	std::string filename = get_file_name(df_record, std::to_string(eid));
	
	//if the file exists, delete it, if the file does not exist, do nothing
	if(does_file_exist(df_record, std::to_string(eid)))
	{
		boost::filesystem::remove("./Data/records/" + filename);
	}
	
	return true;
}

bool Executive::is_attending(int eid)
{
	bool isAttending = false;
	std::list<Record>* List = readRecord(eid); //get the list.
	std::list<string>* tempUserList;
	std::string username = current_user -> getUserName(); //get username
	
	//check the user is attending
	for(auto&& it = List -> begin(); it != List -> end(); it++)
	{
		tempUserList = it->getUserList()
		for(auto&& it2 = tempUserList -> begin(); it2 != tempUserList -> end(); it2++)
		{
			if(*it2 == username)
			{
				isAttending = true; //the current user is attending the event
			}
		}
	}
	
	delete List; //delete the List
	
	
	return isAttending;
}

bool Executive::addUserTo(std::string time, std::list<Record>* List)
{
	bool added = false;
	
	for(auto&& it = List -> begin(); it != List -> end(); it++)
	{
		if(it -> getTime() == time) //if the time exist, add the user to that Record
		{
			it -> add_user(current_user -> getUserName());
			added = true;
		}
	}
	
	return added;
	
}

bool Executive::removeUserFrom(std::string time, std::list<Record>* List)
{
	bool removed = false;
	
	for(auto&& it = List -> begin(); it != List -> end(); it++)
	{
		if(it -> getTime() == time) //if the time exist, remove the user from that Record
		{
			it -> remove_user(current_user -> getUserName());
			removed = true;
		}
	}
	
	return removed;
}

std::list<Record>* Executive::createRecordList(std::list<std::string>* timeList)
{
	std::list<Record>* List = new std::list<Record>; //create a new pointer to a list
	
	for(auto&& it = timeList -> begin(); it != List -> end(); it++)
	{
		Record tempRecord(*it); // create Record object
		List -> push_front(tempRecord); // push to the list
	}
	
	delete timeList; // delete the timeList
	
	return List;
}
