#include <memory>
#include <iostream>
#include <vector>

class ClassC
{
public:
	ClassC() { std::cout << "This is the constructor of class C" << std::endl; }
	~ClassC() { std::cout << "This is the destructor of class C" << std::endl; }

private:
};

class ClassB;


class ClassA
{
public:
	ClassA() { std::cout << "This is the constructor of class A" << std::endl; }
	~ClassA() { std::cout << "This is the destructor of class A" << std::endl; }

	std::shared_ptr<ClassB> mpB;
private:

};


class ClassB
{
public:
	ClassB() { std::cout << "This is the constructor of class B" << std::endl; }
	~ClassB() 
	{ 
		if(mpB.use_count() != 0) mpB.reset();
		std::cout << "This is the destructor of class B" << std::endl; 
	}
	std::shared_ptr<ClassA> mpA;
	std::shared_ptr<ClassB> mpB;

private:

};

int main(int argc, char *argv[])
{

	std::shared_ptr<ClassA> pA = std::make_shared<ClassA>();
	std::shared_ptr<ClassB> pB = std::make_shared<ClassB>();
	std::shared_ptr<ClassC> pC = std::make_shared<ClassC>();
	//pB->mpA = pA;
	pB->mpB = pB;
	//pA->mpB = pB;
	//pB->mpB.reset();

	std::shared_ptr<ClassA> pNULL = NULL;
	std::cout << "pNULL use_count = " << pNULL.use_count() << std::endl;

	return 0;
}