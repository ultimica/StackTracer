#ifndef __LINUX_STACKTRACE__
#define __LINUX_STACKTRACE__

#include <vector>
#include <string>

namespace boost_api
{
    void RegisterSignal();
    std::vector<std::string> LocateExtension(const std::string &pathstr, const std::string &extension);   
    void DecodeDumpFile(const std::string &dumplist);
    void DecodeDumpFileList(const std::vector<std::string> &dumplist);
    void DumpCallStack(const std::string &dumpstr);
    void PrintCallStack();
}

#endif

