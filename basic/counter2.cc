#include "counter2.h"
 
//  コンストラクタ
Counter2::Counter2() : m_count(0)
{
 
}
//  カウンタをリセット
void Counter2::reset()
{
    m_count = 0;
}
//  回数を取得
int Counter2::getCount()
{
    return m_count;
}
//  1ずつカウント
void Counter2::count(void)
{
    m_count++;
}

void Counter2::count(int n)
{
    m_count += n;
}
