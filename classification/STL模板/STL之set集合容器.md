#STL之set集合容器
**引用声明，来自：http://blog.csdn.net/lyhvoyage/article/details/22989659**

stl set集合容器实现了红黑树（Red-Black Tree）的平衡二叉检索树的的数据结构，在插入元素时，它会自动调整二叉树的排列，把该元素放到适当的位置，以确保每个子树根节点的键值大于左子树所有节点的键值，而小于右子树所有节点的键值；另外，还得确保根节点的左子树的高度与有字数的高度相等，这样，二叉树的高度最小，从而检索速度最快。要注意的是，它不会重复插入相同键值的元素，而采取忽略处理。
平衡二叉检索树的检索使用中序遍历算法，检索效率高于vector、deque、和list的容器。另外，采用中序遍历算法可将键值由小到大遍历出来，所以，可以理解为平衡二叉检索树在插入元素时，就会自动将元素按键值从小到大的顺序排列。
构造set集合的主要目的是为了快速检索，使用set前，需要在程序头文件中包含声明“#include<set>”。

##1.创建set集合对象
创建set对象时，需要指定元素的类型，这一点和其他容器一样。
```cpp
#include<iostream>  
#include<set>  
using namespace std;  
int main()  
{  
    set<int> s;  
    return 0;  
}  
```
##2.元素的插入与中序遍历
采用inset()方法把元素插入到集合中，插入规则在默认的比较规则下，是按元素值从小到大插入，如果自己指定了比较规则函数，则按自定义比较规则函数插入。使用前向迭代器对集合中序遍历，结果正好是元素排序后的结果。
```cpp
#include<iostream>  
#include<set>  
using namespace std;  
int main()  
{  
    set<int> s;  
    s.insert(5); //第一次插入5，可以插入  
    s.insert(1);  
    s.insert(6);  
    s.insert(3);  
    s.insert(5); //第二次插入5，重复元素，不会插入  
    set<int>::iterator it; //定义前向迭代器  
    //中序遍历集合中的所有元素  
    for(it = s.begin(); it != s.end(); it++)  
    {  
        cout << *it << " ";  
    }  
    cout << endl;  
    return 0;  
}  
//运行结果：1 3 5 6  
```
##3.元素的方向遍历
使用反向迭代器reverse_iterator可以反向遍历集合，输出的结果正好是集合元素的反向排序结果。它需要用到rbegin()和rend()两个方法，它们分别给出了反向遍历的开始位置和结束位置。
```cpp
#include<iostream>  
#include<set>  
using namespace std;  
int main()  
{  
    set<int> s;  
    s.insert(5); //第一次插入5，可以插入  
    s.insert(1);  
    s.insert(6);  
    s.insert(3);  
    s.insert(5); //第二次插入5，重复元素，不会插入  
    set<int>::reverse_iterator rit; //定义反向迭代器  
    //反向遍历集合中的所有元素  
    for(rit = s.rbegin(); rit != s.rend(); rit++)  
    {  
        cout << *rit << " ";  
    }  
    cout << endl;  
    return 0;  
}  
//运行结果：6 5 3 1  
```
##4.元素的删除
与插入元素的处理一样，集合具有高效的删除处理功能，并自动重新调整内部的红黑树的平衡。删除的对象可以是某个迭代器位置上的元素、等于某键值的元素、一个区间上的元素和清空集合。
```cpp
#include<iostream>  
#include<set>  
using namespace std;  
int main()  
{  
    set<int> s;  
    s.insert(5); //第一次插入5，可以插入  
    s.insert(1);  
    s.insert(6);  
    s.insert(3);  
    s.insert(5); //第二次插入5，重复元素，不会插入  
    s.erase(6); //删除键值为6的元素  
    set<int>::reverse_iterator rit; //定义反向迭代器  
    //反向遍历集合中的所有元素  
    for(rit = s.rbegin(); rit != s.rend(); rit++)  
    {  
        cout << *rit << " ";  
    }  
    cout << endl;   
    set<int>::iterator it;  
  
    it = s.begin();  
    for(int i = 0; i < 2; i++)  
        it = s.erase(it);   
    for(it = s.begin(); it != s.end(); it++)  
        cout << *it << " ";  
    cout << endl;  
  
    s.clear();  
    cout << s.size() << endl;  
  
    return 0;  
}  
/* 
运行结果： 
5 3 1 
5 
0     
*/  
```
##5.元素的检索
使用find()方法对集合进行检索，如果找到查找的的键值，则返回该键值的迭代器位置；否则，返回集合最后一个元素后面的一个位置，即end()。
```cpp
#include<iostream>  
#include<set>  
using namespace std;  
int main()  
{  
    set<int> s;  
    s.insert(5); //第一次插入5，可以插入  
    s.insert(1);  
    s.insert(6);  
    s.insert(3);  
    s.insert(5); //第二次插入5，重复元素，不会插入  
    set<int>::iterator it;  
    it = s.find(6); //查找键值为6的元素  
    if(it != s.end())  
        cout << *it << endl;  
    else  
        cout << "not find it" << endl;  
    it = s.find(20);  
    if(it != s.end())  
        cout << *it << endl;  
    else  
        cout << "not find it" << endl;  
    return 0;  
}  
/* 
运行结果： 
6 
not find it    
*/  
```
下面这种方法也能判断一个数是否在集合中：
```cpp
#include <cstdio>  
#include <set>  
using namespace std;  
int main() {  
    set <int> s;  
    int a;  
    for(int i = 0; i < 10; i++)  
        s.insert(i);  
    for(int i = 0; i < 5; i++) {  
        scanf("%d", &a);  
        if(!s.count(a)) //不存在  
            printf("does not exist\n");  
        else  
            printf("exist\n");  
    }  
    return 0;  
}  
```
##6.自定义比较函数
使用insert将元素插入到集合中去的时候，集合会根据设定的比较函数奖该元素放到该放的节点上去。在定义集合的时候，如果没有指定比较函数，那么采用默认的比较函数，即按键值从小到大的顺序插入元素。但在很多情况下，需要自己编写比较函数。
编写比较函数有两种方法。
(1)如果元素不是结构体，那么可以编写比较函数。下面的程序比较规则为按键值从大到小的顺序插入到集合中。
```cpp
#include<iostream>  
#include<set>  
using namespace std;  
struct mycomp  
{ //自定义比较函数，重载“（）”操作符  
    bool operator() (const int &a, const int &b)  
    {  
        if(a != b)  
            return a > b;  
        else  
            return a > b;  
    }  
};  
int main()  
{  
    set<int, mycomp> s; //采用比较函数mycomp  
    s.insert(5); //第一次插入5，可以插入  
    s.insert(1);  
    s.insert(6);  
    s.insert(3);  
    s.insert(5); //第二次插入5，重复元素，不会插入  
    set<int,mycomp>::iterator it;  
    for(it = s.begin(); it != s.end(); it++)  
        cout << *it << " ";  
    cout << endl;  
    return 0;  
}  
/* 
运行结果：6 5 3 1   
*/  
```
(2)如果元素是结构体，那么可以直接把比较函数写在结构体内。
```cpp
#include<iostream>  
#include<set>  
#include<string>  
using namespace std;  
struct Info  
{  
    string name;  
    double score;  
    bool operator < (const Info &a) const // 重载“<”操作符，自定义排序规则  
    {  
        //按score由大到小排序。如果要由小到大排序，使用“>”即可。  
        return a.score < score;  
    }  
};  
int main()  
{  
    set<Info> s;  
    Info info;  
  
    //插入三个元素  
    info.name = "Jack";  
    info.score = 80;  
    s.insert(info);  
    info.name = "Tom";  
    info.score = 99;  
    s.insert(info);  
    info.name = "Steaven";  
    info.score = 60;  
    s.insert(info);  
  
    set<Info>::iterator it;  
    for(it = s.begin(); it != s.end(); it++)  
        cout << (*it).name << " : " << (*it).score << endl;   
    return 0;  
}  
/* 
运行结果： 
Tom : 99 
Jack : 80 
Steaven : 60 
*/  
```
