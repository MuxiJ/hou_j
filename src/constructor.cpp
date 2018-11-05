#include <ros/ros.h>
#include <iostream>
#include <string>
using namespace std;

class Complex
{
public:
    //Complex()=default;
    Complex(double r = 0, double i = 0) :re(r),im(i)
    {
        cout << "调用非默认构造 constructor，此时re、im为： " << *this << endl;
    }
    double real()const { return re; }
    double imag()const { return im; }
    Complex& setReal(const double& r)
    {
        re = r;
        cout << "setReal，此时re、im为：" << *this << endl;
        return *this;
    }
    Complex(const Complex& c) :re(c.real()), im(c.imag())
    {
        cout << "调用拷贝构造 copy constructor，此时re、im为： " << *this << endl;
    }
    Complex& operator=(const Complex& r)
    {
        re = r.real();
        im = r.imag();
        cout << "调用拷贝赋值运算符 copy assignment operator=，此时re、im为： " << *this << endl;
        return *this;
    }

private:
    double re, im;

//左值可以是右值，右值不能是左值，必加const否则不能接受临时对象（右值）
    friend ostream& operator<<(ostream& output, const Complex& c)
    {
        return output << "（重载<<的输出）" << c.real() << " + " << c.imag() << "j";
    }
};

inline Complex operator+(const Complex& c1, const Complex& c2)
{
    cout << "调用(非成员)重载运算符(重载加法) overload +，此时re、im为： " 
    << Complex( c1.real() + c2.real(), c1.imag() + c2.imag() ) << endl;
    return Complex( c1.real() + c2.real(), c1.imag() + c2.imag() );
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "constructor");

    cout << "---c1:---" << endl;
    Complex c1; cout << c1 << endl;//调用构造函数(非默认)

    cout << "\n---c2:---" << endl;
    Complex c2(2,2); cout << c2 << endl;//用临时对象(1，2)初始化构造函数的形参给c2

    cout << "\n---c3:---" << endl;
    Complex c3(4); cout << c3 << endl;//默认实参填补了0

    cout << "\n---c33:---" << endl;
    Complex c33( Complex(9) ); cout << c33 << endl;

    cout << "\n---c4:---" << endl;
    Complex c4( Complex( c1 + c2 ) ); cout << c4 << endl;

    cout << "\n---c5:---" << endl;
    Complex c5(c2); cout << c5 << endl;

    cout << "\n---c6:---" << endl;
    Complex c6 = c2; cout << c6 << endl;//此=不是调用拷贝赋值运算符

    cout << "\n---c7:---" << endl;
    Complex c7; c7 = c2; cout << c7 << endl;//拷贝赋值运算符

    cout << "\n---c2 + c2 + c2:---" << endl;
    c2 + c2 + c2; cout << c2 << endl;
    
    cout << "\n---c8:---" << endl;
    Complex c8 = c2 + c1; cout << c8 << endl;//此=不是调用拷贝赋值运算符operator=

    cout << "\n---c9:---" << endl;
    Complex c9; c9 = c2 + c1; cout << c9 << endl;//此=调用拷贝赋值运算符

    cout << "\n---c10:---" << endl;
    Complex c10 = Complex(2,3); cout << c10 << endl;

    cout << "\n---c11:---" << endl;
    Complex c11(); cout << c11 << endl;//定义函数。函数指针

    cout << "\n---c12:---" << endl;
    Complex c12;
    cout << c12.setReal(c2.real()).real() << "\n" <<endl;
    cout << c12.setReal(8).real() << "\n" << endl;
    cout << c12.setReal(8) << "\n" << endl;//c8已有成员数据re、im为0、0，调用setReal将re置8，打印调用setReal的对象c8(打印被重载为打印其实虚部)，返回c8
    cout << ( c12 = c12.setReal(8) )<<endl;
    return 0;
}