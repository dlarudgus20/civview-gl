#include "pch.h"

int main()
{
    std::cout << "test output\n";
    boost::thread([] { std::cout << "thread output\n"; }).join();
    std::cin.get();
}
