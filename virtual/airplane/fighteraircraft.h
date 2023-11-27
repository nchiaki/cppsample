#ifndef _FIGHTERAIRCRAFT_H_
#define _FIGHTERAIRCRAFT_H
 
#include <iostream>
#include <string>
#include "AirPlane.h"
 
using namespace std;
 
//  戦闘機クラス
class FighterAircraft : public AirPlane {
private:
    string m_type;
public:
    //  コンストラクタ
    FighterAircraft();

    //  タイプの取得
    string getType();

#if 1
    //  飛行する
    void fly()
    {
        cout << "攻撃に出るために飛行" << endl;
    }
#endif

    //  戦闘する
    void fight();
};
 
#endif // _FIGHTERAIRCRAFT_H_
