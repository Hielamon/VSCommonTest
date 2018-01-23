#include <iostream>
#include <memory>

class BaseA
{
public:
	BaseA()
	{
		std::cout << "Construction BaseA !" << std::endl;
	}
	~BaseA(){}

	virtual void VirtualFucMain()
	{
		VirtualFucBranch();
	}

	virtual void VirtualFucBranch()
	{
		std::cout << "This is the VirtualFucBranch of BaseA" << std::endl;
	}

	virtual void VirtualFuc() = 0;

private:

};

class ChildA : public BaseA
{
public:
	ChildA()
	{
		std::cout << "Construction ChildA !" << std::endl;
		VirtualFucMain();
	}
	~ChildA() {}

	virtual void VirtualFuc()
	{
		std::cout << "This is the VirtualFuc of ChildA" << std::endl;
	}

	virtual void VirtualFucBranch()
	{
		std::cout << "This is the VirtualFucBranch of ChildA" << std::endl;
	}

private:

};

void test(std::shared_ptr<BaseA> &ba)
{
	ba->VirtualFuc();
}



int main(int argc, char *argv[])
{
	ChildA *pA = new ChildA();
	std::shared_ptr<ChildA> pchildA = std::make_shared<ChildA>();
	pchildA->VirtualFucMain();
	std::shared_ptr<BaseA> pbaseA = std::static_pointer_cast<BaseA>(pchildA);
	pbaseA->VirtualFucMain();
	test(pbaseA);
	return 0;
}