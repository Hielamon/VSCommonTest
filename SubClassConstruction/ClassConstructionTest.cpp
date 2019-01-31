#include <iostream>
#include <memory>
#undef MACROTEST
#define MACROTEST 3
#define MACROTEST 4
//#undef MACROTEST

class BaseA
{
public:
	BaseA(const int &value)
	{
		mvalue = value;
		setup();
		std::cout << "The constructor of BaseA is called" << std::endl;
	}
	~BaseA(){}
	int mvalue;

	virtual void setup()
	{
		std::cout << "The setup func in BaseA" << std::endl;
	}


protected:
	BaseA(){}
};

class ChildA : public BaseA
{
public:
	ChildA(const int &value)
		: BaseA(value)
	{
		mchildvalue = value;
		setup();
	}
	~ChildA(){}

	int mvalue;

	virtual void setup()
	{
		std::cout << "The setup func in ChildA" << std::endl;
	}

private:
	int mchildvalue;
	
};

class TestClass
{
public:
	TestClass(int a) {}
	~TestClass() 
	{
		std::cout << "Free TestClass" << std::endl;
	}
};

class SubTestClass : public TestClass
{
public:
	SubTestClass(int a) : TestClass(a) {}
	~SubTestClass() 
	{
		std::cout << "Free SubTestClass" << std::endl;
	}

private:

};

class CBase1
{
public:
	CBase1() {}
	~CBase1() {}

	/*virtual void funA()
	{
		std::cout << "The funA in CBase1" << std::endl;
	}*/
	int a;
};

class CBase2 : public CBase1
{
public:
	CBase2() {}
	~CBase2() {}

	virtual void funA()
	{
		std::cout << "The funA in CBase2" << std::endl;
	}

};

class CBase3 : public CBase2, CBase1
{
public:
	CBase3() {}
	~CBase3() {}
	
	virtual void funA()
	{
		std::cout << "The funA in CBase3" << std::endl;
	}
};

class B;
class A
{
public:
	A(B *b_) { b = b_; }
	~A() {}

	void test()
	{
		//b->setN();
	}

	B *b;
};

class B
{
public:
	B() {}
	~B() {}

	void setN()
	{
		n = 0;
	}
	
	int n;
private:
};



int main(int argc, char *argv[])
{
	ChildA ca(10);
	ca.mvalue = 1;
	int a = -1;
	int b = a % 2;
	std::cout << "-1 % 2 = " << b << std::endl;
	std::cout << "sizeof(int) = " << sizeof(int) << std::endl;

	std::shared_ptr<TestClass> pTestC = std::make_shared<SubTestClass>(1);
	std::shared_ptr<TestClass> pTestC2;

	pTestC2 = pTestC;

	if (pTestC == pTestC2)
		std::cout << "same before reset" << std::endl;
	std::cout << "use_count = " << pTestC.use_count() << std::endl;
	pTestC2.reset();
	if (pTestC == pTestC2)
		std::cout << "same after reset" << std::endl;

	std::cout << "The value of pTestC = " << pTestC << std::endl;
	pTestC.reset();
	if (pTestC == pTestC2)
		std::cout << "same after all reset" << std::endl;
	std::cout << "use_count = " <<pTestC.use_count() << std::endl;
	std::cout << "use_count = " << pTestC2.use_count() << std::endl;

	std::cout << "The value of pTestC = " << pTestC << std::endl;

	CBase3 cbase3;
	cbase3.funA();

	std::cout << "MACROTEST = " << MACROTEST << std::endl;

	return 0;
}