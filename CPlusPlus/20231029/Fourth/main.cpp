#include <iostream>

using namespace std;

int main()
{
    //int a[]={1,2,3,4,5,6};
    //for(int i:a)    //base range for,i是复制品，a是容器
    //{
    //    cout<<i<<endl;
    //}

    float a[]={1,2,3,4,5,6};
    for(auto i:a)    //base range for,i是复制品，a是容器
    {
        cout<<i<<endl;
    }

    return 0;
}
