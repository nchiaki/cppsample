#include "catcher.h"
 
Catcher::Catcher(string name,int number)
{
    m_name = name;
    m_number = number;
    m_kind = "キャッチャー";
}
//  キャッチャーがプレイする
void Catcher::play()
{
    cout << "ピッチャーの投球を受け取る" << endl;
}

