#include <iostream>

#include "another_file.hpp"
#include "h_cpp.h"
#include "linux_stacktrace.h"

int main()
{
    std::cout<<"PGKAPGKAPGKA"<<std::endl;

    Fun<10>();
    HHH hobj;
    hobj.Print();

    boost_api::RegisterSignal();
    return 0;
}