#ifndef _FIELDER_H_
#define _FIELDER_H_
 
#include "BaseballPlayer.h"
 
class Fielder : public BaseballPlayer{
public:
    //  コンストラクタ
    Fielder(string name,int number);
    //  野手がプレイする
    void play();
};
 
#endif // _FIELDER_H_
