#include <iostream>

using namespace std;

void fn(int &n)
{
    n++;
}

void Swap(int &a,int &b)
{
    int k=a;
    a=b;
    b=k;
}
int main()
{
    int i=10;
    int j=5;
    //int &n=i;   //引用必须初始化且无法被拆解
    //n=100;

    Swap(i,j);
    cout << i << endl;
    cout << j << endl;

    return 0;
}
