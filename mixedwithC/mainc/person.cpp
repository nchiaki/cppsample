#include <iostream>
#include "person.hpp"

using namespace std;

extern "C" int c_peopleoftheworld (char *, char *, int);

Person::Person(string country, string name, int age) {
    this->country = country;
    this->name = name;
    this->age = age;
}

string Person::getCountry() {
    return this->country;
}

string Person::getName() {
    return this->name;
}

int Person::getAge() {
    return this->age;
}

void Person::greeting() {
    cout << "Hogehoge, I'm " << this->name << " from " << this->country << endl;
}

USA::USA(string name, int age) : Person("USA", name, age) {
}

void USA::greeting() {
    cout << "Hello, I'm " << this->getName() << " from " << this->getCountry() << endl;
}

French::French(string name, int age) : Person("French", name, age) {
}

void French::greeting() {
    cout << "Bonjour, I'm " << this->getName() << " from " << this->getCountry() << endl;
}

Japanese::Japanese(string name, int age) : Person("Japanese", name, age) {
}

void Japanese::greeting() {
    cout << "こんにちは、" << this->getName() << "です。" << this->getCountry() << "から来ました" << endl;
}

extern "C" int peopleoftheworld (char *flnm, char *fcnm, int line) 
{
    cout << (string)flnm << ":" << (string)fcnm << ":" << line << endl;

    Person *p1 = new USA("John", 20);
    Person *p2 = new French("Jean", 20);
    Person *p3 = new Japanese("太郎", 20);

    p1->greeting();
    p2->greeting();
    p3->greeting();

    delete p1;
    delete p2;
    delete p3;

    cout << "====================" << endl;
    c_peopleoftheworld((char *)__FILE__, (char *)__func__, __LINE__);

    return 3;
}