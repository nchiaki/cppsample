#include <iostream>
#include <string>

using namespace std;

class Processinfo {
    private:

    public:
        int start_cnt;
        int num_cnt;
        int8_t* srcdata;
        int8_t* dstdata;

        Processinfo(int start, int num);
        ~Processinfo();
};
