Event_Planner: main.o Event.o
	export LD_LIBRARY_PATH=./lib/
	g++ -L "./lib/" -l boost_date_time -g -Wall -std=c++11 main.o Event.o -o Event_Planner
	
main.o: main.cpp
	g++ -I"./include/" -L"./lib/" -g -Wall -std=c++11 -c main.cpp
	
Event.o: Event.cpp
	g++ -I"./include/" -L"./lib/" -g -Wall -std=c++11 -c Event.cpp
	
clean:
	rm *.o Event_Planner
