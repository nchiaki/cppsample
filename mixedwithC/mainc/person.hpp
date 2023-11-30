#include <string>

using namespace std;

class Person {
    private:
        string country;
        string name;
        int age;

    public:
        Person(string country, string name, int age);

        string getCountry();
        string getName();
        int getAge();

        virtual void greeting();
};

class USA : public Person {
    public:
        USA(string name, int age);
        void greeting();
};

class French : public Person {
    public:
        French(string name, int age);
        void greeting();
};

class Japanese : public Person {
    public:
        Japanese(string name, int age);
        void greeting();
};
