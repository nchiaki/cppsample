#include "Vector3.h"
 
//  +演算子のオーバーロード
Vector3 operator+(const Vector3& v1,const Vector3& v2)
{
    Vector3 v;
    v.x = v1.x + v2.x;
    v.y = v1.y + v2.y;
    v.z = v1.z + v2.z;
    return v;
}
//  -演算子のオーバーロード
Vector3 operator-(const Vector3& v1,const Vector3& v2)
{
    Vector3 v;
    v.x = v1.x - v2.x;
    v.y = v1.y - v2.y;
    v.z = v1.z - v2.z;
    return v;
}
//  スカラー倍
Vector3 operator*(const double d, const Vector3& v)
{
    Vector3 r;
    r.x = d * v.x;
    r.y = d * v.y;
    r.z = d * v.z;
    return r;
}
//  =演算子のオーバーロード
Vector3& Vector3::operator=(const Vector3& v)
{
    x = v.x;
    y = v.y; 
    z = v.z;
    return *this; 
}
//  +=演算子のオーバーロード
Vector3& Vector3::operator+=(const Vector3& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}
//  -=演算子のオーバーロード
Vector3& Vector3::operator-=(const Vector3& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}
