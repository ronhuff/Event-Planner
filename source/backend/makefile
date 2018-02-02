Event_Planner: main.o Event.o User.o Record.o UserList.o Executive.o
	export LD_LIBRARY_PATH=./lib/
	g++ -L "./lib/" -l boost_date_time -g -Wall -std=c++11 main.o Event.o -o Event_Planner
	
main.o: main.cpp
	g++ -I"./include/" -L"./lib/" -g -Wall -std=c++11 -c main.cpp
	
Event.o: Event.cpp
	g++ -I"./include/" -L"./lib/" -g -Wall -std=c++11 -c Event.cpp
	
User.o: User.cpp
	g++ -I"./include/" -L"./lib/" -g -Wall -std=c++11 -c User.cpp
	
Record.o: Record.cpp
	g++ -I"./include/" -L"./lib/" -g -Wall -std=c++11 -c Record.cpp
	
UserList.o: UserList.cpp
	g++ -I"./include/" -L"./lib/" -g -Wall -std=c++11 -c UserList.cpp

Executive.o: Executive.cpp
	g++ -I"./include/" -L"./lib/" -g -Wall -std=c++11 -c Executive.cpp

clean:
	rm *.o Event_Planner
