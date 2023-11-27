#include <iostream>
#include <string>

#include "BaseballPlayer.h"

using namespace std;

int BaseballPlayer::getNumber()
{
    return m_number;
}

string BaseballPlayer::getKind()
{
    return m_kind;
}

string BaseballPlayer::getName()
{
    return m_name;
}
