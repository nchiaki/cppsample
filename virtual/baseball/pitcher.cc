#include "pitcher.h"
 
Pitcher::Pitcher(string name,int number)
{
    m_name = name;
    m_number = number;
    m_kind = "ピッチャー";
}
//  ピッチャーがプレイする
void Pitcher::play()
{
    cout << "投球する" << endl;
}
