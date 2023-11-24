#ifndef _COUNTER2_H_
#define _COUNTER2_H_
 
//  カウンタークラス
class Counter2{
private:
    //  カウント
    int m_count;
public:
    //  コンストラクタ
    Counter2();
    //  カウンタをリセット
    void reset();
    //  カウントされた回数を取得
    int getCount();
    //  1ずつカウント
    void count(void);
    void count(int n);
};
 
#endif // _COUNTER_H_
