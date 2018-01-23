#pragma once

#include "TestCircleReference.h"
#include <iostream>

#ifdef MYDYNAMICLIB_EXPORTS
#define MYDLL_API __declspec(dllexport)
#else
#define MYDLL_API __declspec(dllimport)
#endif // !MYDYNAMICLIB_EXPORTS

template <class T>
T add(T a, T b);

template <class T>
class MyMathTemp
{
public:
	static T sub(T a, T b);
	//static T div(T a, T b);
	
};

template <class T>
class MYDLL_API MyMathTemp2
{
public:
	static T div(T a, T b);
	inline T div2(T a, T b);
	class TestInlierClass
	{
	public:
		static void printForTest();
	};
};



MYDLL_API double mul(double a, double b);

template
class MYDLL_API MyMathTemp<int>;

template
class MYDLL_API MyMathTemp2<double>::TestInlierClass;

template MYDLL_API double add<double>(double, double);

//#define REGISTER \
//class InstanceClass \
//{ \
//public: \
//	MyMathTemp2<double> doubleInstance; \
//}

#define REGISTER \
void InstanceFuc() \
{ \
	MyMathTemp2<double> doubleInstance; \
	doubleInstance.div(1 , 5); \
	doubleInstance.div2(1 , 5); \
}

template <class T>
class TestTemplateExport
{
public:
	TestTemplateExport(T a);
	~TestTemplateExport();

private:
};

template <class T>
TestTemplateExport<T>::TestTemplateExport(T a)
{
	std::cout << "TestTemplateExport T=" << a << std::endl;
}

template <class T>
TestTemplateExport<T>::~TestTemplateExport()
{
	std::cout << "~TestTemplateExport" << std::endl;
}






