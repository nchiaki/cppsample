#include <stdio.h>
#include "c_person.h"

person japan = {
    .info = {
        .country = "Japan",
        .name = "太郎",
        .age = 20,
        .greeting = "こんにちは、%sです。%sから来ました\n"
    },
    .greeting = greeting
};

person usa = {
    .info = {
        .country = "USA",
        .name = "John",
        .age = 20,
        .greeting = "Hello, I'm %s from %s\n"
    },
    .greeting = greeting
};

person french = {
    .info = {
        .country = "French",
        .name = "Jean",
        .age = 20,
        .greeting = "Bonjour, I'm %s from %s\n"
    },
    .greeting = greeting
};

void greeting (void *vp) {
    struct person *p = (struct person *)vp;
    printf(p->info.greeting, p->info.name, p->info.country);
}

int c_peopleoftheworld (char *flnm, char *fcnm, int line) 
{
    int n;
    
    printf("%s:%s:%d\n", flnm, fcnm, line);

    japan.greeting(&japan);
    usa.greeting(&usa);
    french.greeting(&french);

    return 3;
}
