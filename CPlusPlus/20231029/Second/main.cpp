#include <iostream>

using namespace std;

enum Week
{
  //Sun,Mon,Tue,Wes,Thu,Fri,Sat
    Sun=3,Mon,Tue,Wes,Thu,Fri,Sat
};

int main()
{
    //enum Week w;
    Week w;
    //w=Mon;
    //cout<<w<<endl;
    //cout<<sizeof(w)<<endl;

    //int i;
    //i=Wes;
    //cout<<i<<endl;

    //w=(Week)18;
    w=static_cast<Week>(18);//static_cast表示函数模板静态转换,Week表示数据类型
    cout<<static_cast<int>(123.213)<<endl;
    //const_cast  dynamic_cast  reinterpret_cast;一般用来转换指针

    cout<<w<<endl;


    return 0;
}
