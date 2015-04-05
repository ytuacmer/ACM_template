﻿/*==========================*\
  |     计算几何基础函数     |
  | 1.点和向量的定义         |
  | 2.向量的基本运算         |
  | 3.点积                   |
  | 4.向量长度               |
  | 5.两向量角度             |
  | 6.叉积（2向量/3点）      |
  | 7.向量旋转               |
  | 8.向量的单位法线         |
  | 9.求两点距离             |
  | 10.直线（射线）交点      |
  | 11.点到直线的距离        |
  | 12.点到线段的距离        |
  | 13.点在直线上的投影      |
  | 14.线段相交判定(规范相交)|
  | 15.点是否在一条线段上    |
  | 16.求多边形面积          |
  | 17.判断点是否在多边形内  |
  | 18.求凸包                |
  | 19.求凸包周长            |
  | 20.求多边形面积          |
  \*==========================*/

#include <iostream>
#include <cmath>
using namespace std;
#define eps 1e-10

/********** 定义点 **********/
struct Point{
    double x,y;
    Point(double x=0,double y=0):x(x),y(y) {}
};

/********** 定义向量 **********/
typedef Point Vector;
/********** 向量 + 向量 = 向量 **********/
Vector operator + (Vector a,Vector b)
{
    return Vector(a.x+b.x,a.y+b.y);
}
/********** 点 - 点 = 向量 **********/
Vector operator - (Point a,Point b)    
{
    return Vector(a.x-b.x,a.y-b.y);
}
/********** 向量 * 数 = 向量 **********/
Vector operator * (Vector a,double b)
{
    return Vector(a.x*b,a.y*b);
}
/********** 向量 / 数 = 向量 **********/
Vector operator / (Vector a,double b)
{
    return Vector(a.x/b,a.y/b);
}
bool operator < (const Point& a,const Point& b)
{
    return a.x<b.x || (a.x==b.x && a.y<b.y);
}
int dcmp(double x)    //减少精度问题
{
    if(fabs(x)<eps)
        return 0;
    else 
        return x<0?-1:1;
}
bool operator == (const Point &a,const Point &b)    //判断两点是否相等
{
    return dcmp(a.x-b.x)==0 && dcmp(a.y-b.y)==0;
}
/********** 向量点积 **********/
double Dot(Vector a,Vector b)
{
    return a.x*b.x+a.y*b.y;
}
/********** 向量长度 **********/
double Length(Vector A)
{
    return sqrt(Dot(A,A));
}
/********** 两向量角度 *********/
double Angle(Vector A,Vector B)
{
    return acos(Dot(A,B)/Length(A)/Length(B));
}

/********** 2向量求叉积 **********/
double Cross(Vector a,Vector b)
{
    return a.x*b.y-b.x*a.y;
}
/********** 3点求叉积 **********/
double Cross(Point a,Point b,Point c)
{
    return (c.x-a.x)*(b.y-a.y) - (c.y-a.y)*(b.x-a.x);
}
/********** 向量旋转 ***********/
Vector Rotate(Vector A,double rad)
{
    return Vector(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad));
}
/********** 向量的单位法线 *********/
Vector Normal(Vector A)
{
    double L = Length(A);
    return Vector(-A.y/L,A.x/L);
}
/********** 点和直线 **********/
/********** 求两点间距离 **********/
double dist(Point a,Point b)
{
    return sqrt( (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) );
}
/********** 直线交点 **********/
Point GetLineIntersection(Point P,Vector v,Point Q,Vector w)
{
    Vector u = P-Q;
    double t = Cross(w,u) / Cross(v,w);
    return P+v*t;
}
/********** 点到直线的距离 ***********/
double DistanceToLine(Point P,Point A,Point B)
{
    Vector v1 = B-A,v2 = P-A;
    return fabs(Cross(v1,v2)) / Length(v1);    //如果不取绝对值，得到的是有向距离
}
/********** 点到线段的距离 **********/
double DistanceToSegment(Point P,Point A,Point B)
{
    if(A==B) return Length(P-A);
    Vector v1 = B-A,v2 = P-A,v3 = P-B;
    if(dcmp(Dot(v1,v2))<0) return Length(v2);
    else if(dcmp(Dot(v1,v3)) > 0) return Length(v3);
    else return fabs(Cross(v1,v2)) / Length(v1);
}
/********** 点在直线上的投影 ***********/
Point GetLineProjection(Point P,Point A,Point B)
{
    Vector v = B-A;
    return A+v*(Dot(v,P-A) / Dot(v,v));
}
/********** 线段相交判定（规范相交） ************/
bool SegmentProperIntersection(Point a1,Point a2,Point b1,Point b2)
{
    double c1 = Cross(a2-a1,b1-a1),c2 = Cross(a2-a1,b2-a1),
           c3 = Cross(b2-b1,a1-b1),c4 = Cross(b2-b1,a2-b1);
    return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
}
/********* 点是否在一条线段上 **********/
bool OnSegment(Point p,Point a1,Point a2)
{
    return dcmp(Cross(a1-p,a2-p)) == 0 && dcmp(Dot(a1-p,a2-p)) <0 ;
}
/*********    求多边形面积 **********/
double ConvexPolygonArea(Point* p,int n)
{
    double area = 0;
    for(int i=1;i<n-1;i++)
        area += Cross(p[i]-p[0],p[i+1]-p[0]);
    return area/2;
}



/********** 判断点是否在多边形内 **********/
//判断点q是否在多边形内
//任意凸或者凹多边形
//顶点集合p[]按逆时针或者顺时针顺序存储(1..pointnum)
struct Point{
    double x,y;
};

struct Line{
    Point p1,p2;
};

double xmulti(Point p1,Point p2,Point p0)    //求p1p0和p2p0的叉积,如果大于0,则p1在p2的顺时针方向
{
    return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
double Max(double a,double b)
{
    return a>b?a:b;
}
double Min(double a,double b)
{
    return a<b?a:b;
}
bool ponls(Point q,Line l)    //判断点q是否在线段l上
{
    if(q.x > Max(l.p1.x,l.p2.x) || q.x < Min(l.p1.x,l.p2.x)
            || q.y > Max(l.p1.y,l.p2.y) || q.y < Min(l.p1.y,l.p2.y) )
        return false;
    if(xmulti(l.p1,l.p2,q)==0)    //点q不在l的延长线或者反向延长线上，如果叉积再为0，则确定点q在线段l上
        return true;
    else
        return false;
}
bool pinplg(int pointnum,Point p[],Point q)
{
    Line s;
    int c = 0;
    for(int i=1;i<=pointnum;i++){    //多边形的每条边s
        if(i==pointnum)
            s.p1 = p[pointnum],s.p2 = p[1];
        else
            s.p1 = p[i],s.p2 = p[i+1];
        if(ponls(q,s))    //点q在边s上
            return true;
        if(s.p1.y != s.p2.y){    //s不是水平的
            Point t;
            t.x = q.x - 1,t.y = q.y;
            if( (s.p1.y == q.y && s.p1.x <=q.x) || (s.p2.y == q.y && s.p2.x <= q.x) ){    //s的一个端点在L上
                int tt;
                if(s.p1.y == q.y)
                    tt = 1;
                else if(s.p2.y == q.y)
                    tt = 2;
                int maxx;
                if(s.p1.y > s.p2.y)
                    maxx = 1;
                else
                    maxx = 2;
                if(tt == maxx) //如果这个端点的纵坐标较大的那个端点
                    c++;
            }
            else if(xmulti(s.p1,t,q)*xmulti(s.p2,t,q) <= 0){    //L和边s相交
                Point lowp,higp;
                if(s.p1.y > s.p2.y)
                    lowp.x = s.p2.x,lowp.y = s.p2.y,higp.x = s.p1.x,higp.y = s.p1.y;
                else
                    lowp.x = s.p1.x,lowp.y = s.p1.y,higp.x = s.p2.x,higp.y = s.p2.y;
                if(xmulti(q,higp,lowp)>=0)
                    c++;
            }
        }
    }
    if(c%2==0)
        return false;
    else
        return true;
}
/********** 求凸包 **********/
struct Point{
    double x,y;
};
double dis(Point p1,Point p2)
{
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
double xmulti(Point p1,Point p2,Point p0)    //求p1p0和p2p0的叉积,如果大于0,则p1在p2的顺时针方向
{
    return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
int graham(Point p[],int n,int pl[])    //点集，点的个数，凸包顶点集
{
    int pl[10005];
    //找到纵坐标（y）最小的那个点，作第一个点 
    int t = 1;
    for(int i=1;i<=n;i++)
        if(p[i].y < p[t].y)
            t = i;
    pl[1] = t;
    //顺时针找到凸包点的顺序，记录在 int pl[]
    int num = 1;    //凸包点的数量
    do{    //已确定凸包上num个点 
        num++; //该确定第 num+1 个点了
        t = pl[num-1]+1;
        if(t>n) t = 1;
        for(int i=1;i<=n;i++){    //核心代码。根据叉积确定凸包下一个点。 
            double x = xmulti(p[i],p[t],p[pl[num-1]]);
            if(x<0) t = i;
        }
        pl[num] = t;
    } while(pl[num]!=pl[1]);
    return num-1;    //凸包顶点数
}
/********** 求凸包周长 **********/
struct Point{
    double x,y;
};
double dis(Point p1,Point p2)
{
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
double xmulti(Point p1,Point p2,Point p0)    //求p1p0和p2p0的叉积,如果大于0,则p1在p2的顺时针方向
{
    return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
double graham(Point p[],int n)    //点集和点的个数 
{
    int pl[10005];
    //找到纵坐标（y）最小的那个点，作第一个点 
    int t = 1;
    for(int i=1;i<=n;i++)
        if(p[i].y < p[t].y)
            t = i;
    pl[1] = t;
    //顺时针找到凸包点的顺序，记录在 int pl[]
    int num = 1;    //凸包点的数量
    do{    //已确定凸包上num个点 
        num++; //该确定第 num+1 个点了
        t = pl[num-1]+1;
        if(t>n) t = 1;
        for(int i=1;i<=n;i++){    //核心代码。根据叉积确定凸包下一个点。 
            double x = xmulti(p[i],p[t],p[pl[num-1]]);
            if(x<0) t = i;
        }
        pl[num] = t;
    } while(pl[num]!=pl[1]);
    //计算凸包周长 
    double sum = 0;
    for(int i=1;i<num;i++)
        sum += dis(p[pl[i]],p[pl[i+1]]);
    return sum;
}
/********** 求多边形面积 **********/
struct Point{    //定义点结构 
    double x,y;
};
double getS(Point a,Point b,Point c)    //返回三角形面积 
{  
    return ((b.x - a.x) * (c.y - a.y) - (b.y - a.y)*(c.x - a.x))/2;  
}
double getPS(Point p[],int n)    //返回多边形面积。必须确保 n>=3，且多边形是凸多边形 
{
    double sumS=0;
    for(int i=1;i<=n-1;i++)
        sumS+=getS(p[1],p[i],p[i+1]);
    return sumS;
}
