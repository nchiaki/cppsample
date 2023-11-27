#include <iostream>
#include "AirPlane.h"


using namespace std;

//  コンストラクタ
AirPlane::AirPlane()
{
    m_type = "飛行機";
}

//  タイプの取得
string AirPlane::getType()
{
    return m_type;
}

#if 0
//  飛行する
void AirPlane::fly()
{
    cout << "飛行する" << endl;
}
#endif
