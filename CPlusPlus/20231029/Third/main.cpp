#include <iostream>

using namespace std;

int main()
{
    //auto i=1+3.4;   //这里叫初始化
    auto i="Hello"+3;   //函数的形参不能使用
    cout << i << endl;
    cout <<sizeof(i)<<endl;

    return 0;
}
