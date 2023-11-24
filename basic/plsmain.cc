#include <iostream>
#include <string>

#include "keisan.h"
#include "minmax.h"
#include "data.h"
#include "2strings.h"
#include "calculation.h"
#include "number.h"
#include "hoge.h"
#include "function.h"
#include "object.h"
#include "counter.h"
#include "airplane.h"
#include "fundcalc.h"
#include "newcalc.h"
#include "counter2.h"
#include "vector.h"

using namespace std;

void    greeting(string msg);

int main()
{
    int        inv;
    string  msg = "Hello, world!";

    cout << "数値を入力してください: ";
    cin >> inv;

    cout << __LINE__ << ":" << inv << "を２倍した値は" << (inv * 2) << "です。" << endl;

    greeting (msg);

    cout << "=====================================" << endl;
    Keisan k;
    k.a = rand()%100;
    k.b = rand()%100;
    cout << k.a << " + " << k.b << " = " << k.add() << endl;
    cout << k.a << " - " << k.b << " = " << k.sub() << endl;

    cout << "=====================================" << endl;
    MinMax m;
    int a = rand() % 100;
    int b = rand() % 100;
    int c = rand() % 100;
    cout << a << "と" << b << "," << c << "のうち、最大のものは" << m.max(a,b,c) << endl;
    cout << a << "と" << b << "," << c << "のうち、最小のものは" << m.min(a,b,c) << endl;
 
    cout << "=====================================" << endl;
    CData d;
    d.init();   //  パラメータを初期化
    d.setNumber(rand()%1000);
    d.setComment("Programming C++");
    cout << "number = " << d.getNumber() << " comment = " << d.getComment() << endl;

    cout << "=====================================" << endl;
    TwoStrings s;
    s.setString1("Hello");
    s.setString2("World");
    cout << "一つ目の文字列は" << s.getString1() << endl;
    cout << "二つ目の文字列は" << s.getString2() << endl;
    cout << "二つの文字列を合成したものは" << s.getConnectedString() << endl;
    cout << "合成した文字列の長さは" << s.getConnectedLength() << "文字" << endl;

    cout << "=====================================" << endl;
    Calculation cal;
    cal.setNumber1(rand()%100);    //  一つ目の数をセット
    cal.setNumber2(rand()%100);    //  二つ目の数をセット
    //  二つの数の和を表示
    cout << cal.getNumber1() << " + " << cal.getNumber2() << " = " << cal.add() << endl;
    //  二つの数の差を表示
    cout << cal.getNumber1() << " - " << cal.getNumber2() << " = " << cal.sub() << endl;

    cout << "=====================================" << endl;
    Number* pN;
    pN = new Number();
    pN->setNumbers(rand()%100, rand()%100);
    cout << pN->getAdd() << endl;
    delete pN;

    cout << "=====================================" << endl;
    Hoge* pH;
    pH = new Hoge();
    pH->foo();
    delete pH;

    cout << "=====================================" << endl;
    //  配列を生成
    int* num = new int[4];
    int i;
    //  配列に値を代入
    for (i = 0; i < 4; i++){
        num[i] = rand()%10;
    }
    //  配列の内容を表示
    for (i = 0; i < 4; i++){
        cout << "num[" << i << "]=" << num[i] << " ";
    }
    cout << endl;
    delete[] num;

    cout << "=====================================" << endl;
    {
        int m = rand()%100, n = rand()%100;
        cout << m << "と" << n << "のうち、最大のものは" << Function::max(m, n) << endl;
        cout << m << "と" << n << "のうち、最小のものは" << Function::min(m, n) << endl;
    }


    cout << "=====================================" << endl;
    {
        Object *o1, *o2, *o3;
        o1 = new Object();
        o2 = new Object();
        o3 = new Object();
        cout << "オブジェクトの数:" << Object::getObjectNum() << endl;
        delete o3;
        cout << "オブジェクトの数:" << Object::getObjectNum() << endl;
        delete o2;
        delete o1;
    }

    cout << "=====================================" << endl;
    {
        Counter c1, c2;
        c1.count();
        c2.count();
        c2.count();
        c2.reset();
        c1.count();
        c1.count();
        c2.count();
        cout << "c1のカウント数：" << c1.getCount() << endl;
        cout << "c2のカウント数：" << c2.getCount() << endl;
        cout << "トータルのカウント数:" << c1.getCount() + c2.getCount() << endl;
        cout << "トータルのカウント数:" << Counter::getTotalCount() << endl;
    }

    cout << "=====================================" << endl;
    {
        Fighter f;  //  戦闘機クラス
        Airplane a; //  飛行機クラス
        //  飛行機が飛行する
        a.fly();
        //  戦闘機が飛行する
        f.fly();
        //  戦闘機が戦闘する
        f.fight();
    }

    cout << "=====================================" << endl;
    {
        NewCalc n;
        n.setNumber1(rand()%100);   //  一つ目の数を設定
        n.setNumber2(rand()%10);    //  二つ目の数を設定
        cout << n.getNumber1() << " + " << n.getNumber2() << " = " << n.add() << endl;
        cout << n.getNumber1() << " - " << n.getNumber2() << " = " << n.sub() << endl;
        cout << n.getNumber1() << " * " << n.getNumber2() << " = " << n.mul() << endl;
        cout << n.getNumber1() << " / " << n.getNumber2() << " = " << n.div() << endl;
    }

    cout << "=====================================" << endl;
    {
        Counter2* pC = new Counter2();
        pC->count(); //  １回カウント
        pC->count(); //  １回カウント
        cout << "回数:" << pC->getCount() << "回" << endl;
        pC->count(4);    //  ４回カウント
        cout << "回数:" << pC->getCount() << "回" << endl;
        //  カウンタをリセット
        pC->reset();
        cout << "回数:" << pC->getCount() << "回" << endl;
        //  カウンタを消去
        delete pC;
    }

    cout << "=====================================" << endl;
    {
        Vector *v1, *v2;
        //  引数なしのコンストラクタで生成
        v1 = new Vector();
        //  引数つきのコンストラクタで生成
        v2 = new Vector(1.1, 2.3);
        v1->set(3.8, 2.7);
        cout << "v1 =(" << v1->getX() << " , " << v1->getY() << ")" << endl;
        cout << "v2 =(" << v2->getX() << " , " << v2->getY() << ")" << endl;
        delete v1;
        delete v2;
    }
    return 0;
}
