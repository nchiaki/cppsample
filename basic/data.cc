#include "data.h"
 
void CData::init()
{
    number = 0;
    comment = "";
}

void CData::setNumber(int n)
{
    number = n;
}

void CData::setComment(string c)
{
    comment = c;
}
