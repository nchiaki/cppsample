
#include <iostream>

using namespace std;

extern "C" int c_peopleoftheworld (char *flnm, char *fcnm, int line);

int main(int argc, char *argv[])
{
    int n;

    cout << "Hello C++ World!" << endl;

    n = c_peopleoftheworld((char *)__FILE__, (char *)__func__, __LINE__);

    return 0;
}

