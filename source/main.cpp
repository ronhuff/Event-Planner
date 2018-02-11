#include "./backend/Executive.h"

int main(int argc, char* argv[]){
	Executive* e = new Executive();
	e->setCurrentUser("abba");
	e->generateEvent("John Cena's Party", "2002-1-25");
	if(argc == 2){
		Event* a = e->getEventByID(std::stoi(argv[1]));
		std::cout << a->getDate() << '\n';
		std::cout << a->getCreatorUserName() << '\n';
		std::cout << a->getName() << '\n';
		delete a;
	}
	
}
