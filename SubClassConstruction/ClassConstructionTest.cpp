#include <iostream>
#include <memory>

class BaseA
{
public:
	BaseA(int &value)
	{
		mvalue = value;
	}
	~BaseA(){}

protected:
	BaseA(){}
	int mvalue;
};

class ChildA : public BaseA
{
public:
	ChildA(const int &value)
	{
		mchildvalue = value;
	}
	~ChildA(){}

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



int main(int argc, char *argv[])
{
	ChildA ca(10);
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
	pTestC.reset();
	if (pTestC == pTestC2)
		std::cout << "same after all reset" << std::endl;
	std::cout << "use_count = " <<pTestC.use_count() << std::endl;
	std::cout << "use_count = " << pTestC2.use_count() << std::endl;
	return 0;
}