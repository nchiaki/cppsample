#include <iostream>
#include <string>
#include <thread>
#include <sys/time.h>

#include "procinfo.hpp"

using namespace std;

void procfunc(Processinfo* pinfo)
{
    int localcnt;
    int ix;

    //cout << "Start: start_cnt = " <<  pinfo->start_cnt << " num_cnt = " << pinfo->num_cnt << endl;

    localcnt = 0;
    for (ix=pinfo->start_cnt; ix<pinfo->start_cnt+pinfo->num_cnt; ++ix)
    {
        localcnt++;
    }

    //cout << "End:   start_cnt = " << pinfo->start_cnt << " endcnt = " << ix << " localcnt = " << localcnt << endl;

    delete pinfo;
}

void
usage(string iam)
{
    cout << "Usage: " << iam << " count <count> group <group>" << endl;
}

int main(int argc, char* argv[])
{
    int count;
    int group;

    cout << "Hello, C++ World!" << endl;

    for (int i = 1; i < argc; ++i)
    {
        if (string(argv[i]) == "count")
        {
            i++;
            count = stoi(argv[i]);
        }
        else if (string(argv[i]) == "group")
        {
            i++;
            group = stoi(argv[i]);
        }
        else
        {
            usage(argv[0]);
            return 0;
        }   
    }

    cout << "count = " << count << endl;
    cout << "group = " << group << endl;

    struct timeval starttv, endtv, resulttv;

    Processinfo* pinfo[10];
    for (int ix=0; ix<group; ++ix)
    {
        int strtcnt = ix*count;
        pinfo[ix] = new Processinfo(strtcnt, count);
        for (int jx=0; jx<count; ++jx)
        {
            pinfo[ix]->srcdata[jx] = rand() % 256;
            pinfo[ix]->dstdata[jx] = rand() % 256;
        }
    }

    gettimeofday(&starttv, NULL);

    for (int ix=0; ix<group; ++ix)
    {
        //int strtcnt = ix*count;
        //Processinfo* pinfo = new Processinfo(strtcnt, count);
        thread t(procfunc, pinfo[ix]);
        t.join();
        //cout << "=============================" << endl;
    }

    gettimeofday(&endtv, NULL);
    timersub(&endtv, &starttv, &resulttv);
    cout << "Elapsed time: " << resulttv.tv_sec << " sec " << resulttv.tv_usec << " usec" << endl;

    cout << "=============================" << endl;

    for (int ix=0; ix<group; ++ix)
    {
        int strtcnt = ix*count;
        pinfo[ix] = new Processinfo(strtcnt, count);
        for (int jx=0; jx<count; ++jx)
        {
            pinfo[ix]->srcdata[jx] = rand() % 256;
            pinfo[ix]->dstdata[jx] = rand() % 256;
        }
    }

    gettimeofday(&starttv, NULL);

    thread thrds[10];
    for (int ix=0; ix<group; ++ix)
    {
        //int strtcnt = ix*count;
        //Processinfo* pinfo = new Processinfo(strtcnt, count);
        thread t(procfunc, pinfo[ix]);
        thrds[ix] = move(t);
        //cout << "=============================" << endl;
    }
    for (int ix=0; ix<group; ++ix)
    {
        thrds[ix].join();
    }
 
    gettimeofday(&endtv, NULL);
    timersub(&endtv, &starttv, &resulttv);
    cout << "Elapsed time: " << resulttv.tv_sec << " sec " << resulttv.tv_usec << " usec" << endl;

    return 0;
}
