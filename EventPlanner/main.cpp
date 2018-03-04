// #include "interface/CLI.h"
// #include <iostream>
//
// int main(int argc, char* argv[]){
//     CLI interface;
//     interface.run();
//
// 	system("pause");
//     return (0);
// }

// EventPlannerRework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "backend/Executive.h"
#include <iostream>
#include <memory>
#include "interface/CLI.h"

class CLI;
class Executive;

int main()
{
	CLI cli;
	cli.run();
	

	std::cout << "\n";
	std::cout << "Have a pleaseant day...\n";
	system("pause");
    return 0;
}
