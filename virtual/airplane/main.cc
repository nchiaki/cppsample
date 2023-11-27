#include <iostream>
#include "AirPlane.h"
#include "fighteraircraft.h"
#include "passengerplane.h"
 
using namespace std;
 
int main(){
    //  戦闘機クラスのインスタンスの生成(ポインタ)
    AirPlane* airplane = new AirPlane();
    FighterAircraft* fighter = new FighterAircraft();
    PassengerPlane* airlinear = new PassengerPlane();
    // 飛行機クラスの処理
    airplane->fly();                 //  飛行する
    //  戦闘機クラスの処理
    fighter->fly();                  //  飛行する
    fighter->fight();                //  戦闘する
    //  旅客機クラスの処理
    airlinear->fly();                //  飛行する
    airlinear->carryPassengers();    //  乗客を運ぶ
    //  delete処理
    delete fighter;
    delete airlinear;

    cout << "------------------------" << endl;

    //  戦闘機クラスのインスタンスの生成(インスタンス)
    AirPlane s_airplane;
    FighterAircraft s_fighter;
    PassengerPlane s_airlinear;
    // 飛行機クラスの処理
    s_airplane.fly();                 //  飛行する
    //  戦闘機クラスの処理
    s_fighter.fly();                  //  飛行する
    s_fighter.fight();                //  戦闘する
    //  旅客機クラスの処理
    s_airlinear.fly();                //  飛行する
    s_airlinear.carryPassengers();    //  乗客を運ぶ

    cout << "------------------------" << endl;

    //  戦闘機クラスのインスタンスの生成(インスタンス)
    AirPlane ss_airplane = AirPlane();
    FighterAircraft ss_fighter = FighterAircraft();
    PassengerPlane ss_airlinear = PassengerPlane();
    // 飛行機クラスの処理
    ss_airplane.fly();                 //  飛行する
    //  戦闘機クラスの処理
    ss_fighter.fly();                  //  飛行する
    ss_fighter.fight();                //  戦闘する
    //  旅客機クラスの処理
    ss_airlinear.fly();                //  飛行する
    ss_airlinear.carryPassengers();    //  乗客を運ぶ
}
