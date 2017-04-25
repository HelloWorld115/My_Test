// StaticTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>


class Father
{
public:
    static void setFather(int n) { m_n = n; };
    static void print(){ std::cout << m_n << std::endl; };

private:
    static int m_n;
};

class Child : public Father
{
public:
    static void hello() {
        setFather(14);
    }
};

class Child2 : public Father
{
public:
    static void hello2() { setFather(142); };
};

int Father::m_n = 0;

int _tmain(int argc, _TCHAR* argv[])
{
    using std::cout;
    using std::cin;
    using std::endl;

    cout << "请输入数字" << endl;
    char p[20];
    cin.getline(p, 19);
    Father::setFather(atof(p));
    Child::print();
    Child::hello();
    Father::print();
    Child2::hello2();
    Child::print();
    system("Pause");
    return 0;
}

