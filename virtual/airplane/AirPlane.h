#ifndef _AirPlane_h_
#define _AirPlane_h_

#include <iostream>
#include <string>

using namespace std;

class AirPlane{
private:
    string m_type;

public:
    //  コンストラクタ
    AirPlane();

    //  タイプの取得
    string getType();

    //  飛行する
    //virtual void fly()
    void fly()
    {
        cout << "飛行する" << endl;
    }
};


#endif
