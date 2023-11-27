#ifndef _PASSENGERPLANE_H_
#define _PASSENGERPLANE_H_
 
#include <iostream>
#include <string>
#include "AirPlane.h"
 
using namespace std;
 
//  旅客機クラス
class PassengerPlane: public AirPlane {
private:
    string m_type;

public:
    //  コンストラクタ
    PassengerPlane();

    //  タイプの取得
    string getType();

#if 1
    //  飛行する
    void fly()
    {
        cout << "乗客を乗せて目的地まで飛行します。" << endl;
    }
#endif

    //  乗客を運ぶ
    void carryPassengers();
};
 
#endif // _PASSENGERPLANE_H_
