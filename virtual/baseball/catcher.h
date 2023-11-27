#ifndef _CATCHER_H_
#define _CATCHER_H_
 
#include "BaseballPlayer.h"
 
class Catcher : public BaseballPlayer{
public:
    //  コンストラクタ
    Catcher(string name,int number);
    //  キャッチャーがプレイする
    void play();
};
 
#endif //_CATCHER_H_
