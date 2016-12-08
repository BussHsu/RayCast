#include "Error.h"
#include<iostream>
#include <cstdlib>

//Report error
void fatalerror(std::string errstring)
{
	std::cout << errstring << std::endl;
	std::cout << "Press any key to quit..." << std::endl;
	int a;
	std::cin >> a;
	exit(69);
}