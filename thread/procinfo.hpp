#include <iostream>
#include <string>

using namespace std;

class Processinfo {
    private:

    public:
        int start_cnt;
        int num_cnt;
        int procmode;
        uint8_t* srcdata;
        uint8_t* dstdata;
        uint8_t* rsltdata;
        uint8_t* rslt2data;

        Processinfo(int start, int num, int mode);
        ~Processinfo();

        bool cmprslt();
};
