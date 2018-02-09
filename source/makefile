backend = ./backend/
lib = ./lib/
include = ./include/

Event_Planner: main.o Event.o User.o Record.o Executive.o
	g++ -L$(lib) -l boost_system -l boost_date_time -l boost_filesystem -g -Wall -std=c++11 main.o Event.o User.o Record.o Executive.o -o Event_Planner
	
main.o: $(backend)main.cpp
	g++ -I$(include) -L$(lib) -g -Wall -std=c++11 -c $(backend)main.cpp
	
Event.o: $(backend)Event.cpp
	g++ -I$(include) -L$(lib) -g -Wall -std=c++11 -c $(backend)Event.cpp
	
User.o: $(backend)User.cpp
	g++ -I$(include) -L$(lib) -g -Wall -std=c++11 -c $(backend)User.cpp
	
Record.o: $(backend)Record.cpp
	g++ -I$(include) -L$(lib) -g -Wall -std=c++11 -c $(backend)Record.cpp

Executive.o: $(backend)Executive.cpp
	g++ -I$(include) -L$(lib) -g -Wall -std=c++11 -c $(backend)Executive.cpp

clean:
	rm -r *.o Event_Planner ./data
