#include "linux_stacktrace.h"

#define ARCH_LINUX()         (__unix__ || __linux__)
#define ARCH_WINDOWS()       (_WIN32   || WIN32)

#define IS_SUPPORT_GNU_SIGNAL()    ARCH_LINUX()


#include <signal.h>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include <boost/stacktrace.hpp>
#include <boost/date_time.hpp>
#include <map>
#include <string>
#include <sstream>


#define DUMP_PREFIX            "/fs-add/fatek-home/root/"
#define CAT_DUPFILE(signalnum)  DUMP_PREFIX signalnum "_dumptrace"
#define INITSIGMAP(signalnum) g_mapstr[signalnum]=std::string(CAT_DUPFILE(#signalnum));

using namespace boost_api;

static std::map<int,std::string>  g_mapstr;


void my_sig_handle(int signum)
{
    ::signal(signum,SIG_DFL);
    boost_api::DumpCallStack(g_mapstr[signum]);
    ::raise(SIGABRT);
}

void boost_api::RegisterSignal()
{
    INITSIGMAP(SIGSEGV);
    INITSIGMAP(SIGABRT);
    INITSIGMAP(SIGFPE);
    INITSIGMAP(SIGINT);
    INITSIGMAP(SIGTERM);

#if IS_SUPPORT_GNU_SIGNAL()
    INITSIGMAP(SIGBUS);
    INITSIGMAP(SIGSYS);
    INITSIGMAP(SIGXFSZ);
    INITSIGMAP(SIGQUIT);
#endif

    std::map<int, std::string>::iterator pos=g_mapstr.begin();
    std::map<int, std::string>::iterator endpos=g_mapstr.end();
    for(;pos!=endpos;pos++)
        ::signal(pos->first,&my_sig_handle);

    boost::posix_time::ptime timeLocal = boost::posix_time::second_clock::universal_time();
    std::time_t curtimet=boost::posix_time::to_time_t(timeLocal);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&curtimet), "_%Y_%m_%d_%H_%M_%S");
    std::cout<<"CURRENT TIme:"<<ss.str()<<std::endl;

    for(pos=g_mapstr.begin();pos!=endpos;pos++)
    {
        std::cout<<"Sig Handle:"<<pos->second+ss.str()<<std::endl;
    }


}

std::vector<std::string> boost_api::LocateExtension(const std::string &pathstr, const std::string &extension)
{
    std::string comparedextension="."+extension;
    
    std::vector<std::string> ret;
    boost::filesystem::path curpath(pathstr);
    boost::filesystem::directory_iterator pos(curpath);
    boost::filesystem::directory_iterator endpos=boost::filesystem::directory_iterator();
    for(;pos!=endpos;pos++)
    {
        boost::filesystem::path filepath=pos->path();
        if(filepath.extension()==comparedextension)
        {
            std::stringstream ss;
            ss<<filepath;
            ret.emplace_back(ss.str());
            //std::cout<<"CURFILE:"<<filepath<<std::endl;
        }

    }
    return ret;
}

void boost_api::DecodeDumpFile(const std::string &dumpfile)
{
    bool isDumpExist=false;
    if (boost::filesystem::exists(dumpfile)) 
    {
    boost::filesystem::path dumpfilepath(dumpfile);
    boost::filesystem::path dcoodedpath=dumpfilepath.replace_extension(".decode_dump");
    isDumpExist=true;
    std::ifstream ifs(dumpfile.c_str());
    std::ofstream decodefile(dcoodedpath.string());
    std::cout<<"==================================Parsing Dump file:"<<dumpfile<<std::endl;

    boost::stacktrace::stacktrace st = boost::stacktrace::stacktrace::from_dump(ifs);
    std::cout << "Previous run crashed:\n" << st << std::endl;


    BOOST_FOREACH (boost::stacktrace::frame frame , st) {
        std::cout << frame.address() << std::endl;
        decodefile<<frame.address()<<std::endl;
    }
    // cleaning up
    ifs.close();
    decodefile.close();
    //  boost::filesystem::remove(recovertarget);

    std::cout << "=================================================================="<< std::endl;
    }

}


void boost_api::DecodeDumpFileList(const std::vector<std::string> &dumplist)
{
    BOOST_FOREACH (const std::string &dumpfile , dumplist) {
        boost_api::DecodeDumpFile(dumpfile);
    }
}

void boost_api::DumpCallStack(const std::string &dumpstr)
{
    boost::posix_time::ptime timeLocal = boost::posix_time::second_clock::universal_time();
    std::time_t curtimet=boost::posix_time::to_time_t(timeLocal);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&curtimet), "_%Y_%m_%d_%H_%M_%S");

    std::string timestampstr=ss.str();
    std::string dumpfile=dumpstr+timestampstr+".dump";
    std::cout<<"DUMP:"<<dumpfile<<std::endl;
    boost::stacktrace::safe_dump_to(dumpfile.c_str());
}

void boost_api::PrintCallStack()
{
    boost::posix_time::ptime timeLocal = boost::posix_time::second_clock::universal_time();
    std::time_t curtimet=boost::posix_time::to_time_t(timeLocal);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&curtimet), "_%Y_%m_%d_%H_%M_%S");

    boost::stacktrace::stacktrace curST;
    std::cout<<"CURRENT Trace:"<<curST;
}
   
