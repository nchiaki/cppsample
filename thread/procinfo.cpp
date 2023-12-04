#include "procinfo.hpp"

Processinfo::Processinfo(int start, int num, int mode)
{
    this->start_cnt = start;
    this->num_cnt = num;
    this->procmode = mode;
    this->srcdata = new uint8_t[num];
    this->dstdata = new uint8_t[num];
    this->rsltdata = new uint8_t[num];
    this->rslt2data = new uint8_t[num];
}

Processinfo::~Processinfo()
{
    delete[] this->srcdata;
    delete[] this->dstdata;
    delete[] this->rsltdata;
    delete[] this->rslt2data;
}

bool Processinfo::cmprslt()
{
    int ix;
    bool rslt = true;

    for (ix=0; ix<this->num_cnt; ++ix)
    {
        if (this->rsltdata[ix] != this->rslt2data[ix])
        {
            rslt = false;
            break;
        }
    }

    return rslt;
}