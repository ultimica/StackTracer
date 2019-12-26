#include <iostream>

#include "another_file.hpp"
#include "h_cpp.h"
#include "linux_stacktrace.h"

void BB_Fun()
{
    std::cout<<"BBFUN"<<std::endl;
    boost_api::PrintCallStack();
}

struct AA
{
    void AA_Fun()
    {
        int x=0;
        int y=9;
        BB_Fun();
    }
};
int main()
{
    std::cout<<"PGKAPGKAPGKA"<<std::endl;

    Fun<10>();
    HHH hobj;
    hobj.Print();

    boost_api::RegisterSignal();
    std::vector<std::string> retvec=boost_api::LocateExtension("d:/","dump");
    AA tmp;
    tmp.AA_Fun();
    boost_api::DecodeDumpFileList(retvec);
    return 0;
}