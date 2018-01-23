#include "MyDynamicLib.h"
#include <iostream>

REGISTER;

template <class T>
T add(T a, T b)
{
	return a + b;
}

double mul(double a, double b)
{
	return a*b;
}

template <class T>
T MyMathTemp<T>::sub(T a, T b)
{
	return a - b;
}

//template <class T>
//T MyMathTemp<T>::div(T a, T b)
//{
//	InstanceClass impl;
//	return (T)(impl.doubleInstance.div(a,b));
//}

template <class T>
T MyMathTemp2<T>::div(T a, T b)
{
	return a / b;
}

template <class T>
inline T MyMathTemp2<T>::div2(T a, T b)
{
	return a / b;
}

template <class T>
void MyMathTemp2<T>::TestInlierClass::printForTest()
{
	std::cout << "This is a inserted class function" << std::endl;
}

//template<> MYDLL_API double add<double>(double, double);
