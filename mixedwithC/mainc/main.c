#include <stdio.h>

int peopleoftheworld (const char *flnm, const char *fcnm, int line);

int main(int argc, char *argv[])
{
    int n;

    printf("Hello C World!\n");

    n = peopleoftheworld(__FILE__, __func__, __LINE__);

    return 0;
}

