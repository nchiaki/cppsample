#include "procinfo.hpp"

Processinfo::Processinfo(int start, int num)
{
    this->start_cnt = start;
    this->num_cnt = num;
    this->srcdata = new int8_t[num];
    this->dstdata = new int8_t[num];
}

Processinfo::~Processinfo()
{
    delete[] this->srcdata;
    delete[] this->dstdata;
}

