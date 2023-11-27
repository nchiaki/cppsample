#include "fighteraircraft.h"
 
//  コンストラクタ
FighterAircraft::FighterAircraft()
{
    m_type = "戦闘機";
}
//  タイプの取得
string FighterAircraft::getType()
{
    return m_type;
}

#if 0
//  飛行する
void FighterAircraft::fly()
{
    cout << "攻撃に出るために飛行" << endl;
}
#endif

//  戦闘する
void FighterAircraft::fight()
{
    fly();
    cout << "戦闘します" << endl;
}
