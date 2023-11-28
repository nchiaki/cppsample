#include "newstring.h"
 
//  コンストラクタ
NewString::NewString()
{
    m_value = "";
}
//  値を代入するコンストラクタ①（文字列から）
NewString::NewString(string value)
{
    m_value = value;
}
//  値を代入するコンストラクタ②（他のクラスから)
NewString::NewString(NewString& value)
{
    m_value = value.getValue();
}
//  値を代入
NewString& NewString::operator= (NewString& n)
{
    m_value = n.getValue();
    return *this;
}
//  stringで値を取得
string NewString::getValue()
{
    return m_value;
}

//  ==演算子のオーバーロード
bool operator== (NewString& n1, NewString& n2)
{
    string s1 = n1.getValue(), ls1;
    string s2 = n2.getValue(), ls2;

    transform(s1.begin(), s1.end(), back_inserter(ls1), ::tolower);
    transform(s2.begin(), s2.end(), back_inserter(ls2), ::tolower);

    return ls1 == ls2;
}

//  !=演算子のオーバーロード
bool operator!= (NewString& n1, NewString& n2)
{
    string s1 = n1.getValue(), ls1;
    string s2 = n2.getValue(), ls2;

    transform(s1.begin(), s1.end(), back_inserter(ls1), ::tolower);
    transform(s2.begin(), s2.end(), back_inserter(ls2), ::tolower);

    return ls1 != ls2;
}