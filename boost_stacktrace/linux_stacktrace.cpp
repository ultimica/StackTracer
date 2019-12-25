#include "linux_stacktrace.h"

#define ARCH_LINUX()         (__unix__ || __linux__)
#define ARCH_WINDOWS()       (_WIN32   || WIN32)

#define IS_SUPPORT_GNU_SIGNAL()    ARCH_LINUX()


#include <signal.h>


#include <boost/stacktrace.hpp>
#include <boost/date_time.hpp>
#include <map>
#include <string>

#define DUMP_PREFIX            "/fs-add/fatek-home/root/"
#define CAT_DUPFILE(signalnum)  DUMP_PREFIX##signalnum"_dumptrace"
#define INITSIGMAP(signalnum) g_mapstr[signalnum]=std::string(CAT_DUPFILE(#signalnum));

using namespace boost_api;

static std::map<int,std::string>  g_mapstr;


void my_sig_handle(int signum)
{
    ::signal(signum,SIG_DFL);
    	
    boost::posix_time::ptime timeLocal = boost::posix_time::second_clock::universal_time();
    std::time_t curtimet=boost::posix_time::to_time_t(timeLocal);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&curtimet), "_%Y_%m_%d_%H_%M_%S");

    std::string timestampstr=ss.str();
    std::string dumpfile=g_mapstr[signum]+timestampstr+".dump";
    boost::stacktrace::safe_dump_to(dumpfile.c_str());
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

/*

namespace bs = boost::stacktrace;
bool RecoverDumpFile(std::string& file)
{
    bool isDumpExist=false;
    std::string recovertarget=file+std::string(".dump");
  
    if (boost::filesystem::exists(recovertarget)) {
    // there is a backtrace
    isDumpExist=true;
    std::ifstream ifs(recovertarget.c_str());
    std::cout<<"==================================Parsing Dump file:"<<recovertarget<<std::endl;

    boost::stacktrace::stacktrace st = boost::stacktrace::stacktrace::from_dump(ifs);
    std::cout << "Previous run crashed:\n" << st << std::endl;


    // boost::stacktrace::iterator stpos=st.begin();
    // boost::stacktrace::iterator stendpos=st.end();
    // int index=0;
    // for (;stpos!=stendpos;stpos++) {

    //     std::cout << index<<" "<<stpos->address() << std::endl;
    // }

    BOOST_FOREACH (bs::frame frame , st) {
        std::cout << frame.address() << std::endl;
    }
    // cleaning up
    ifs.close();
    //  boost::filesystem::remove(recovertarget);

    std::cout << "=================================================================="<< std::endl;
    }
    return isDumpExist;

}
//#define DEBUG_TIME_4_LAUNCH
ConfigObjPrj *g_config_prj;
extern SimulationMain *g_simu_main;





int main(int argc, char *argv[])
{
    INITSIGMAP(SIGSEGV);
    INITSIGMAP(SIGABRT);
    INITSIGMAP(SIGFPE);
    INITSIGMAP(SIGINT);
    INITSIGMAP(SIGBUS);
    INITSIGMAP(SIGSYS);
    INITSIGMAP(SIGXFSZ);
    INITSIGMAP(SIGTERM);
    INITSIGMAP(SIGQUIT);

    std::map<int, std::string>::iterator pos=g_mapstr.begin();
    std::map<int, std::string>::iterator endpos=g_mapstr.end();
    for(;pos!=endpos;pos++)
        ::signal(pos->first,&my_sig_handle);

    pos=g_mapstr.begin();
    bool isExit=false;
    for(;pos!=endpos;pos++)
    {
        isExit|=RecoverDumpFile(pos->second);
    }
    
    if(isExit)
    {
        std::cout<<"~~~~~~~~~~~~~~~Dump File Find~~~~~~~~~~~~"<<std::endl;
        return 0;
    }



*/
