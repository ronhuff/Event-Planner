#include "Executive.h"

Executive::Executive(){
	//Initialization of objects
	eventList = new std::vector<Event>();
	currentUser = nullptr;

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
	if(!doesFileExist(df_eventList)){
		//Generate the file.
		std::ofstream create_directory_and_file(getFileName(df_eventList));
		create_directory_and_file.close();
	}else{
		//Read the file.
		std::ifstream eventList(getFileName(df_eventList));
		eventList >> eventNum;
		eventList.close();
	}

	//Rebuild all information from .txt files if possible
	std::string viewing_file;
	for(auto&& it : boost::filesystem::directory_iterator(boost::filesystem::path("./data/events"))){
		//This iterates over every file in the directory
		//The name of the file is accessed with it.filename()
		viewing_file = it.path().filename().string();
		rebuildEvent(viewing_file);
	}
	//Sort the events by date.
	sortEventList();
}
Executive::~Executive(){
	delete eventList;
	if (currentUser != nullptr) {
	    delete currentUser;
	}
}
int Executive::getEventNum(){
	//Increment eventNum before returning it because this will guarantee unique numbers.
	eventNum++;
	//Save the eventNum in this session.
	std::ofstream eventList(getFileName(df_eventList));
	eventList << eventNum;
	eventList.close();
	
	return eventNum;
}
bool Executive::generateEvent(std::string name, std::string date){
	try{		
		//Create the event at the back of the vector.
		eventList->push_back(Event(name,date,*currentUser,getEventNum()));
		
		//This is a reference to the event we want to input data for.
		Event &new_event = eventList->back();
		
		//Using the event at the back of the list (that we just created), we create the info and record files that correspond to it.
		std::ofstream file_info_writer(getFileName(df_event,std::to_string((new_event.getIDNumber()))));
		std::ofstream file_record_writer(getFileName(df_record,std::to_string((new_event.getIDNumber()))));
			
		//Now, we write the basic information of the event to the file in question.
		file_info_writer << new_event.getName() << '\n' << new_event.getDate() << '\n' << new_event.getCreatorUserName() << '\n' << new_event.getCreatorRealName() << '\n' << new_event.getIDNumber();
		
		//Close the files.
		file_info_writer.close();
		file_record_writer.close();
		
		//Event created.
		return true;
	}catch(std::logic_error m){
		//The event was a holiday was it? Return false.
		return false;
	}catch(std::exception m){
		//If something caused an error, the creation is probably wrong.
		return false;
	}
}
bool Executive::doesFileExist(DataFile type, std::string identifer){
	//Returns whether a file exists or not.
	return (boost::filesystem::exists(getFileName(type,identifer)));
}
std::string Executive::getFileName(DataFile type, std::string identifer){
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
		case df_eventList:
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
bool Executive::deleteEvent(int event_id){
	if(!doesFileExist(df_event,std::to_string(event_id))){
		//The event with that id does not even exist.
		return false;
	}else{
		//First, we delete the event from our vector.
		for(auto&& x = eventList->begin(); x != eventList->end(); x++){
			//Iterate over every element in the vector.
			if(x->getIDNumber() == event_id){
				//This element is the one to be removed.
				eventList->erase(x);
				break;
			}
		}
		//We remove the files from the data folder.
		boost::filesystem::remove(getFileName(df_event,std::to_string(event_id)));
		boost::filesystem::remove(getFileName(df_record,std::to_string(event_id)));
		//We have removed the event from existence.
		return true;
	}
}
void Executive::rebuildEvent(std::string filename){
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
	eventList->push_back(Event(name,date,User(creator_user_name,creator_user_name),num));
}
std::vector<Event>& Executive::getEventList(){
	return (*eventList);
}
void Executive::sortEventList(){
	std::sort(eventList->begin(),eventList->end());
}

bool Executive::setCurrentUser(std::string uid) {
    if(doesFileExist(df_user, uid)) {

	std::string pnm = "";
	std::string attending_string = "";
	std::list<int> attending_list;

	std::ifstream user_file;
	user_file.open(getFileName(df_user, uid));

	std::getline(user_file, pnm, '\n'); //Store the proper name
	std::getline(user_file, attending_string, '\n'); //Get string of attending events

	storeIntsFromString(attending_list, attending_string); //Store the attending event list

	currentUser = new User(uid, pnm, attending_list);

	user_file.close();

	return (true);

    }
    else { //File does not exist; return false

	currentUser = new User();
	return (false);

    }

}

void Executive::storeIntsFromString(std::list<int> &int_list, std::string int_string) {
    std::stringstream ss;
    std::string temp_string = "";
    int temp_int = 0;
    ss.str(int_string);
    
    std::getline(ss, temp_string, ',');

    if (temp_string != "") {
	do {
	    temp_int = std::stoi(temp_string);
	    int_list.push_back(temp_int);
	    std::getline(ss, temp_string, ',');
	}while (!ss.eof());
    }
}

User* Executive::getCurrentUser() {
    return (currentUser);
}

bool Executive::writeCurrentUser() {

    std::string uid = currentUser -> getUserName();
    if (uid == "") {
	return (false);
    }
    else {
	std::string pnm = currentUser -> getRealName();
	std::list<int>* att_ev = currentUser -> getAttendingEvents();

	boost::filesystem::remove(getFileName(df_user, uid)); //Remove the file to stage for new creation
	std::ofstream user_file;
	user_file.open(getFileName(df_user, uid));

	user_file << pnm << '\n';

	for (std::list<int>::iterator it = att_ev -> begin(); it != att_ev -> end(); ++it) {
		user_file << *it << ',';
	}
	user_file << '\n';

	user_file.close();

	return (true);
    }
}

std::list<Record>* Executive::readRecord(int event_id)
{
	std::string filename = getFileName(df_record, std::to_string(event_id));
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
			tempRecord.addUser(tempString);
			recordFile >> flag;
		}
		recordList->push_front(tempRecord);
	}
	
	recordFile.close();
	
	return recordList;
}

std::list<std::string>* Executive::getAttending(int eid)
{
	std::string filename = getFileName(df_record, std::to_string(eid));
	std::list<Record>* List = readRecord(eid);
	std::list<std::string>* UserList, tempUserList = nullptr;
	
	for(auto&& it = List -> begin(); it != List -> end(); it++)
	{
		tempUserList = it -> getUserList();
		UserList -> merge(tempUserList);
	}
	
	UserList -> unique();
	delete List;
	delete tempUserList;
	
	return UserList;
}

void  Executive::writeRecord(int eid, std::list<Record>* List)
{
	std::string filename = getFileName(df_record, std::to_string(eid));
	std::list<std::string>* tempUserlist;
	std::string tempTime;
	
	//if the previous file exists, delete it
	if(doesFileExist(df_record, std::to_string(eid)))
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
	std::string filename = getFileName(df_record, std::to_string(eid));
	
	//if the file exists, delete it, if the file does not exist, do nothing
	if(doesFileExist(df_record, std::to_string(eid)))
	{
		boost::filesystem::remove("./Data/records/" + filename);
	}
	
	return true;
}

bool Executive::isAttending(int eid)
{
	bool isAttending = false;
	std::list<Record>* List = readRecord(eid); //get the list.
	std::list<std::string>* tempUserList;
	std::string username = currentUser -> getUserName(); //get username
	
	//check the user is attending
	for(auto&& it = List -> begin(); it != List -> end(); it++)
	{
		tempUserList = it->getUserList();
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
			it -> addUser(currentUser -> getUserName());
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
			it -> removeUser(currentUser -> getUserName());
			removed = true;
		}
	}
	
	return removed;
}

std::list<Record>* Executive::createRecordList(std::list<std::string>* timeList)
{
	std::list<Record>* List = new std::list<Record>; //create a new pointer to a list
	
	for(auto&& it = timeList -> begin(); it != timeList -> end(); it++)
	{
		Record tempRecord(*it); // create Record object
		List -> push_front(tempRecord); // push to the list
	}
	
	delete timeList; // delete the timeList
	
	return List;
}
std::list<Event>* Executive::getEventByCreator(User u){
	std::list<Event>* list = new std::list<Event>();
	
	for(auto&& x = eventList->begin(); x != eventList->end(); x++){
		//Iterate over every element in the vector.
		if(x->getCreatorUserName() == u.getUserName()){
			//This element is the one to be removed.
			list->push_back(*x);
			break;
		}
	}
	
	return list;
}
Event Executive::getEventByID(int eid){
	if(doesFileExist(df_event,std::to_string(eid))){
		//We read in everything regarding the event in question.
		std::ifstream text_file(getFileName(df_event,std::to_string(eid)));
		
		int num;
		std::string name,date,creator_user_name,creator_real_name,temp;
		
		//Put the information in various lines into these variables.
		std::getline(text_file,name);
		std::getline(text_file,date);
		std::getline(text_file,creator_user_name);
		std::getline(text_file,creator_real_name);
		//temp stores the int as a string, it will be converted.
		std::getline(text_file,temp);
		num = std::stoi(temp);
		//Generate the event.
		return Event(name,date,User(creator_user_name,creator_user_name),num);
	}else{
		throw std::logic_error("Event with that id does not exist");
	}
}
