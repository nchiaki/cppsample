#include <iostream>
#include <string>
#include <thread>
#include <sys/time.h>

#include "procinfo.hpp"
#include "simddef.h"

#define DMPLOG 0
#define CHKSIMD 0
#define CMPCHK 0

using namespace std;

void procfunc(Processinfo* pinfo)
{
    int localcnt;
    int ix;

    //cout << "Start: start_cnt = " <<  pinfo->start_cnt << " num_cnt = " << pinfo->num_cnt << endl;

    if (pinfo->procmode == 0)
    {
        localcnt = 0;
        for (ix=pinfo->start_cnt; ix<pinfo->start_cnt+pinfo->num_cnt; ++ix)
        {
            localcnt++;
        }
    }
    else
    { cout << "Error: Invalid procmode = " << pinfo->procmode << endl;}

    //cout << "End:   start_cnt = " << pinfo->start_cnt << " endcnt = " << ix << " localcnt = " << localcnt << endl;

    delete pinfo;
}

void procfunc10(Processinfo* pinfo)
{
    int ix;

    //cout << "Start10: start_cnt = " <<  pinfo->start_cnt << " num_cnt = " << pinfo->num_cnt << endl;

    if (pinfo->procmode == 10 || pinfo->procmode == 20 || pinfo->procmode == 30)
    {
        for (ix=0; ix<pinfo->num_cnt; ++ix)
        {
            pinfo->rslt2data[ix] = (pinfo->srcdata[ix] + pinfo->dstdata[ix] + 1) >> 1;
        }
    }
    else if (pinfo->procmode == 11)
    {
        __m128i  vsrc, vdst;
        
        for (ix=0; ix<pinfo->num_cnt; ix+=16)
        {
            vsrc = _mm_loadu_si128((__m128i*)&pinfo->srcdata[ix]);
            vdst = _mm_loadu_si128((__m128i*)&pinfo->dstdata[ix]);
            vsrc = _mm_avg_epu8(vsrc, vdst);
            _mm_storeu_si128((__m128i*)&pinfo->rslt2data[ix], vsrc);
        }
    }
#if isSIMD(SIMD_AVX2)
    else if (pinfo->procmode == 21)
    {
        __m256i  vsrc, vdst;

        for (ix=0; ix<pinfo->num_cnt; ix+=32)
        {
            vsrc = _mm256_loadu_si256((__m256i*)&pinfo->srcdata[ix]);
            vdst = _mm256_loadu_si256((__m256i*)&pinfo->dstdata[ix]);
            vsrc = _mm256_avg_epu8(vsrc, vdst);
            _mm256_storeu_si256((__m256i*)&pinfo->rslt2data[ix], vsrc);
        }
    }
#endif
#if isSIMD(SIMD_AVX512)
    else if (pinfo->procmode == 31)
    {
        __m512i  vsrc, vdst;

        for (ix=0; ix<pinfo->num_cnt; ix+=64)
        {
            vsrc = _mm512_loadu_si512((__m512i*)&pinfo->srcdata[ix]);
            vdst = _mm512_loadu_si512((__m512i*)&pinfo->dstdata[ix]);
            vsrc = _mm512_avg_epu8(vsrc, vdst);
            _mm512_storeu_si512((__m512i*)&pinfo->rslt2data[ix], vsrc);
        }
    }
#endif
    else
    { cout << "Error: Invalid procmode = " << pinfo->procmode << endl;}
#if DMPLOG
    cout << "Cmp[" << ix << "]";
    for (ix=0; ix<pinfo->num_cnt; ++ix)
    {
        cout << " " << (int)pinfo->rslt2data[ix];
    }
    cout << endl;
#endif

#if CMPCHK
    if (pinfo->cmprslt() == false)
    {
        cout << "Error: Invalid result" << endl;
    }
#endif
    //cout << "End10:   start_cnt = " << pinfo->start_cnt << " endcnt = " << ix << endl;

    delete pinfo;
}

void prepare_processinfo(Processinfo* pinfo[], int count, int group, int procmode)
{
    for (int ix=0; ix<group; ++ix)
    {
        int strtcnt = ix*count;
        int jx;
        pinfo[ix] = new Processinfo(strtcnt, count, procmode);
        for (jx=0; jx<count; ++jx)
        {
            pinfo[ix]->srcdata[jx] = rand() % 256;
            pinfo[ix]->dstdata[jx] = rand() % 256;
#if CMPCHK
            if (10 <= procmode)
            {pinfo[ix]->rsltdata[jx] = (pinfo[ix]->srcdata[jx] + pinfo[ix]->dstdata[jx] + 1) >> 1;}
#endif
        }
#if DMPLOG
        cout << "Set[" << ix << "]";
        for (jx=0; jx<count; ++jx)
        {
            cout << " " << (int)pinfo[ix]->rsltdata[jx];
        }
        cout << endl;
#endif
    }
}

double seek_perf_0(int count, int group, int procmode)
{
    struct timeval starttv, endtv, resulttv;

    // スレッド毎のデータ領域を予め確保
    Processinfo* pinfo[10];
    prepare_processinfo(pinfo, count, group, procmode);

    // スレッド毎に完了待ちした場合の処理時間を求める

    gettimeofday(&starttv, NULL);

    for (int ix=0; ix<group; ++ix)
    {
        thread t(procfunc, pinfo[ix]);
        t.join();
    }
    gettimeofday(&endtv, NULL);
    timersub(&endtv, &starttv, &resulttv);
    cout << "Elapsed time: " << resulttv.tv_sec << " sec " << resulttv.tv_usec << " usec" << endl;

    double case1usec = resulttv.tv_sec * 1000000 + resulttv.tv_usec;

    cout << "=============================" << endl;

    // スレッド毎に完了待ちした場合の処理時間を求める
    prepare_processinfo(pinfo, count, group, procmode);

    // 全スレッドを同時に起動した場合の処理時間を求める

    gettimeofday(&starttv, NULL);

    thread thrds[10];
    for (int ix=0; ix<group; ++ix)
    {
        thread t(procfunc, pinfo[ix]);
        thrds[ix] = move(t);
    }
    for (int ix=0; ix<group; ++ix)
    {
        thrds[ix].join();
    }
 
    gettimeofday(&endtv, NULL);
    timersub(&endtv, &starttv, &resulttv);
    cout << "Elapsed time: " << resulttv.tv_sec << " sec " << resulttv.tv_usec << " usec" << endl;

    double case2usec = resulttv.tv_sec * 1000000 + resulttv.tv_usec;

    cout << "=============================" << endl;

    double speedup = (case1usec / case2usec) * 100.0;
    cout << "Speedup = " << speedup << "%" << endl;

    return speedup;
}

double seek_perf_10(int count, int group, int procmode)
{
    struct timeval starttv, endtv, resulttv;
    Processinfo* pinfo[10];
    double speedup;
    int simdno;

    simdno = procmode == 10 ? 128 : procmode == 20 ? 256 : 0;
#if CHKSIMD
    {
        int ix;
        uint8_t src[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
        uint8_t dst[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
        uint8_t rslt[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
        uint8_t rslt2[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

        cout << "Set[16]";
        for (ix=0; ix<16; ++ix)
        {
            src[ix] = rand() % 256;
            dst[ix] = rand() % 256;
            rslt[ix] = (src[ix] + dst[ix] + 1) >> 1;
            cout << " " << (int)rslt[ix];
        }
        cout << endl;

        __m128i  vsrc, vdst, vrslt;
        
        vsrc = _mm_load_si128((__m128i*)&src[0]);
        vdst = _mm_load_si128((__m128i*)&dst[0]);
        vrslt = _mm_avg_epu8(vsrc, vdst);
        _mm_store_si128((__m128i*)&rslt2[0], vrslt);

        cout << "Cmp[16]";
        for (int ix=0; ix<16; ++ix)
        {
            cout << " " << (int)rslt2[ix];
        }
        cout << endl;
    }
#endif

    // スレッド毎のデータ領域を予め確保
    prepare_processinfo(pinfo, count, group, procmode);

    // スレッド毎に完了待ちした場合の2点間の通常計算処理時間を求める
    gettimeofday(&starttv, NULL);

    for (int ix=0; ix<group; ++ix)
    {
        thread t(procfunc10, pinfo[ix]);
        t.join();
    }
    gettimeofday(&endtv, NULL);
    timersub(&endtv, &starttv, &resulttv);
    cout << "Normal avarage time: " << resulttv.tv_sec << " sec " << resulttv.tv_usec << " usec" << endl;

    double case1usec = resulttv.tv_sec * 1000000 + resulttv.tv_usec;

    cout << "=============================" << endl;

    // スレッド毎に完了待ちした場合の2点間のSIMDSIMD(128)計算処理時間を求める
    // スレッド毎のデータ領域を予め確保
    prepare_processinfo(pinfo, count, group, procmode+1);

    gettimeofday(&starttv, NULL);

    for (int ix=0; ix<group; ++ix)
    {
        thread t(procfunc10, pinfo[ix]);
        t.join();
    }
    gettimeofday(&endtv, NULL);
    timersub(&endtv, &starttv, &resulttv);
    cout << "SIMD(" << simdno << ") avarage time: " << resulttv.tv_sec << " sec " << resulttv.tv_usec << " usec" << endl;

    double case2usec = resulttv.tv_sec * 1000000 + resulttv.tv_usec;

    speedup = (case1usec / case2usec) * 100.0;
    cout << "Speedup = " << speedup << "%" << endl;

    cout << "=============================" << endl;

    // 全スレッドを同時に起動した場合の2点間のSIMDSIMD(128)計算処理時間を求める
    // スレッド毎のデータ領域を予め確保
    prepare_processinfo(pinfo, count, group, procmode+1);

    gettimeofday(&starttv, NULL);

    thread thrds[10];
    for (int ix=0; ix<group; ++ix)
    {
        thread t(procfunc10, pinfo[ix]);
        thrds[ix] = move(t);
    }
    for (int ix=0; ix<group; ++ix)
    {
        thrds[ix].join();
    }
 
    gettimeofday(&endtv, NULL);
    timersub(&endtv, &starttv, &resulttv);
    cout << "SIMD(" << simdno << ") thread time: " << resulttv.tv_sec << " sec " << resulttv.tv_usec << " usec" << endl;

    double case3usec = resulttv.tv_sec * 1000000 + resulttv.tv_usec;

    speedup = (case2usec / case3usec) * 100.0;
    cout << "Speedup = " << speedup << "%" << endl;

    cout << "=============================" << endl;

    speedup = (case1usec / case3usec) * 100.0;
    cout << "Total Speedup = " << speedup << "%" << endl;

    return speedup;
}


// procmode := 0
double seek_perf(int count, int group, int procmode)
{
    if ((procmode/10) == 0)
    {
        return seek_perf_0(count, group, procmode);
    }
    else if ((procmode/100) == 0)
    {
        return seek_perf_10(count, group, procmode);
    }
    else
    {
        cout << "Error: Invalid procmode = " << procmode << endl;
        return 0.0;
    }

}

void
usage(string iam)
{
    cout << "Usage: " << iam << " count <count> group <group> [retry <retry>] [mode <procMode>]" << endl;
    cout << "  count: 1スレッド毎の処理回数" << endl;
    cout << "  group: スレッドグループ数" << endl;
    cout << "  retry: 繰り返し回数 0 = ∞" << endl;
#if isSIMD(SIMD_AVX512BW)
    cout << "  mode:  0:=単純繰り返し 10:=SIMD(128) 20:=SIMD(256) 30:=SIMD(512)" << endl;
#elif isSIMD(SIMD_AVX2)
    cout << "  mode:  0:=単純繰り返し 10:=SIMD(128) 20:=SIMD(256)" << endl;
    cout << "         *) SIMD(512) は -mavx512f -mavx512bw オプションで再コンパイル＆ビルド必要" << endl;
    cout << "            g++ -pthread -mavx2 -mavx512f -mavx512bw *.cpp" << endl;
#else
    cout << "  mode:  0:=単純繰り返し 10:=SIMD(128)" << endl;
    cout << "         *) SIMD(256) は -mavx2 オプションで再コンパイル＆ビルド必要" << endl;
    cout << "            g++ -pthread -mavx2 *.cpp" << endl;
#endif
    cout << "HW concurrent thread count = " << thread::hardware_concurrency() << endl;
}

int main(int argc, char* argv[])
{
    int count;
    int group;
    int retry = 1;
    int procmode = 0;

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
        else if (string(argv[i]) == "retry")
        {
            i++;
            retry = stoi(argv[i]);
        }
        else if (string(argv[i]) == "mode")
        {
            i++;
            procmode = stoi(argv[i]);
        }
        else
        {
            usage(argv[0]);
            return 0;
        }   
    }

    cout << "count = " << count << endl;
    cout << "group = " << group << endl;

    double speedup;
    if (0 < retry)
    {
        cout << "Retry = " << retry << endl;
        for (int ix=0; ix<retry; ++ix)
        {
            speedup = seek_perf(count, group, procmode);
        }
    }
    else
    {
        double ttlup = 0.0;
        double aveup = 0.0;
        int loops = 0;
        while (true)
        {
            speedup = seek_perf(count, group, procmode);
            if (loops == 0)
            {
                aveup = speedup;
            }
            else
            {
                ttlup = aveup * loops;
                ttlup += speedup;
                aveup = ttlup / (loops + 1);
            }
            loops++;
            cout << loops << ":Average speedup = " << aveup << "%" << endl << endl;
        }
    }

    return 0;
}
