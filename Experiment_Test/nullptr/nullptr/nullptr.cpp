// nullptr.cpp : �������̨Ӧ�ó������ڵ㡣
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
    cout << "��̬�ڴ��ַ" << &c << endl;
    cout << "��ʱ������ַ" << &a << endl;

    while (1)
    {

    }
    return 0;
}

