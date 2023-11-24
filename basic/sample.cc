#include <iostream>
#include <string>


void
greeting(std::string msg)
{
    std::cout << msg << std::endl << msg << std::endl;
}

extern "C" void greeting__(std::string msg)
{
    greeting(msg);
}
