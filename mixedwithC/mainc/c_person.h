
void greeting ( void *p);

typedef struct person_info {
    char *country;
    char *name;
    int age;
    char *greeting;
} person_info;

typedef struct person {
    person_info info;
    void (*greeting)( void *);
} person;

int peopleoftheworld (char *flnm, char *fcnm, int line);
