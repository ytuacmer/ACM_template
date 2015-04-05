#include <iostream>
#include <cmath>
using namespace std;
#define eps 1e-10
/********** 定义点 **********/
struct Point{
    double x,y;
    Point(double x=0,double y=0):x(x),y(y) {}
};
/********** 定义三维点 ***********/
struct Point3{
    double x,y,z;
    Point3(double x=0,double y=0,double z=0):x(x),y(y),z(z) {}
};
/********** 定义圆 **********/
struct Circle{
    Point c;
    double r;
    Circle(Point c,double r):c(c),r(r){}
    Point point(double a){
        return Point(c.x + cos(a)*r,c.y + sin(a)*r);
    }
};
/*********** 三维点距离 **********/
double dis3(Point3 A,Point3 B)
{
    return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y)+(A.z-B.z)*(A.z-B.z));
}
/*********** 球面 ***********/
/*********** 角度转换成弧度 ***********/
double torad(double deg)
{
    return deg/180 * acos(-1);    //acos(-1)就是PI
}
/*********** 经纬度（角度）转化为空间坐标 **********/
void get_coord(double R,double lat,double lng,double &x ,double &y,double &z)
{
    lat = torad(lat);    //纬度
    lng = torad(lng);    //经度
    x = R*cos(lat)*cos(lng);
    y = R*cos(lat)*sin(lng);
    z = R*sin(lat);
}
/*********** 两点的球面距离 ***********/
double disA2B(double R,Point3 A,Point3 B)
{
    //将球面距离看成求点A，B和半径R构成的扇形的弧长
    double d = dis3(A,B);    //弦长
    double a = 2*asin(d/2/R);    //圆心角
    double l = a*R;        //弧长
    return l;
}
