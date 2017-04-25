// nullptr.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
using namespace std;
static int c = 0;

int main()
{
  
    int a = 6;

    c += 1;
    a += 1;

    Sleep(5000);
    cout << "静态内存地址" << &c << endl;
    cout << "临时变量地址" << &a << endl;

    while (1)
    {

    }
    return 0;
}

