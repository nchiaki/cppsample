#include <iostream>
#include <string>

#include "bar.h"
#include "foo.h"
#include "collectionint.h"
 
using namespace std;
 

void changeNumber(int&);
void swap(int&, int&);

//  整数値を比較し、大きいほうを返す関数
int max(int,int);
//  実数を比較し、大きいほうを返す関数
double max(double,double);
//  文字列を比較し、長いほうを返す関数
string max(string,string);
template <typename T> T tmax(T a, T b);


int main(){

    cout << "=====================================" << endl;
    {
        int a = 7;
        int &n = a;
        cout << "a= " << a << endl;
        cout << "a= " << n+3 << endl;
    }

    cout << "=====================================" << endl;
    {
        int n = 5;
        cout << "変更前 : " << n << endl;
        changeNumber(n);
        cout << "変更後 : " << n << endl;
    }

    cout << "=====================================" << endl;
    {
        int a = 1, b = 2;
        cout << "a = " << a << " b = " << b << endl;
        swap(a, b);
        cout << "a = " << a << " b = " << b << endl;
    }

    cout << "=====================================" << endl;
    {
        Foo* pFoo;
        Bar* pBar;

        pFoo = new Foo();
        pBar = new Bar();

        pFoo->hoge();
        pBar->func2();
        pFoo->fuga(pBar);
        pFoo->hoge();
    }

    cout << "=====================================" << endl;
    {
        cout << max(1,2) << endl;
        cout << max(1.75,3.12) << endl;
        string s1 = "aiu",s2 = "eo";
        cout << max(s1,s2) << endl;

        cout << tmax(1,2) << endl;
        cout << tmax(1.75,3.12) << endl;
        s1 = "aiu",s2 = "eo";
        cout << tmax(s1,s2) << endl;

    }

    cout << "=====================================" << endl;
    {
        //  配列変数の定義
        int array[] = { 1,5,4,2,3 };
        CollectionInt <int> * c = new CollectionInt <int> (array,5);
        c->showArray();
        cout << "最大値 : " << c->getMax() << endl;
        cout << "最小値 : " << c->getMin() << endl;
        delete c;

        string sarray[] = { "a", "b", "c", "d", "e" };
        CollectionInt <string> * sc = new CollectionInt <string> (sarray,5);
        sc->showArray();
        cout << "最大値 : " << sc->getMax() << endl;
        cout << "最小値 : " << sc->getMin() << endl;
        delete sc;

    }
}


void changeNumber(int& n){
    n *= 2;    //  数値
}

void swap(int& a, int& b)
{
    int tmp;
    tmp = a;
    a = b;
    b = tmp;
}
 
int max(int a,int b)
{
    if(a > b){
        return a;
    }
    return b;
}
double max(double a,double b)
{
    if(a > b){
        return a;
    }
    return b;
}
string max(string a,string b)
{
    if(a > b){
        return a;
    }
    return b;
}

template <typename T>
T tmax(T a, T b)
{
    if(a > b){
        return a;
    }
    return b;
}