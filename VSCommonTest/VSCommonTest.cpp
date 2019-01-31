#include "../MyDynamicLib/MyDynamicLib.h"
#include "../MyStaticLib/MyMathFuncs.h"

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <OpencvCommon.h>
#include <map>

REGISTER;

#define Warn(...) {                        \
  printf(__VA_ARGS__ );           \
}

template<int t>
inline void testInlineFunc()
{

}

namespace cv
{
	inline bool operator<(const cv::Rect &A, const cv::Rect &B)
	{
		if (A.x < B.x) return true;
		if (A.x == B.x) {
			if (A.y < B.y) return true;
			if (A.y == B.y) {
				if (A.width < B.width) return true;
				if (A.width == B.width)
					if (A.height < B.height) return true;
			}
		}
		return false;
	}
}

enum TestEnum{RIGHT};
enum PixelSelectorStatus { PIXSEL_VOID = 0, PIXSEL_1, PIXSEL_2, PIXSEL_3 };

class TestClass
{
public:
	TestClass() : a{1, 2}
	{
		std::cout << "The constructor of TestClass" << std::endl;
	}
	~TestClass() {}

	void printA()
	{
		std::cout << "a[0] = " << a[0] << ", a[1] = " << a[1] << std::endl;
	}

private:
	int a[2];
};


int main(int *argc, char *argv[])
{
	/*for (size_t i = 0; i < 128; i++)
	{
		int cID = i;
		char cChar = cID;
		uchar cUChar = cChar;
		std::cout << "char ID = " << cID << "; cChar = " << cChar
			<< "; cUChar = " << cUChar << std::endl;
	}*/

	double testFloat = 1.00000000000651;
	if (testFloat == 1.000000000)
	{
		std::cout << testFloat << std::endl;
	}

	char * p1 = new char[10];
	char * p2 = new char[10];

	for (size_t i = 0; i < 9; i++)
	{
		p1[i] = 'a' + i;
		p2[i] = 'f' + i;
	}

	p1[9] = '\0';
	p2[9] = '\0';

	std::shared_ptr<char> testcPointer3;
	{
		std::shared_ptr<char> testcPointer1(p1,
										   [&](char *data)
		{
			std::cout << data << " delete 1" << std::endl;
			delete data;
		});

		std::shared_ptr<char> testcPointer2(p2,
											[&](char *data)
		{
			std::cout << data << " delete 2" << std::endl;
			delete data;
		});

		testcPointer3 = testcPointer2;
	}

	//testcPointer3.reset();

	std::cout << MathFuncs::MyMathFuncs::Add(1, 2) << std::endl;
	std::cout << add(3.0, 4.0) << std::endl;
	std::cout << mul(3, 4) << std::endl;
	std::cout << MyMathTemp<int>::sub(3, 5) << std::endl;
	std::cout << MyMathTemp2<double>::div(3, 5) << std::endl;
	MyMathTemp2<double> mymath;
	std::cout << mymath.div2(4, 5) << std::endl;
	MyMathTemp2<double>::TestInlierClass::printForTest();
	printf("Hello world\n");
	Warn("Hello world\n");

	char *testString = NULL;
	{
		char *testC = (char *)malloc(sizeof(char) * 100);
		testC[0] = 'H';
		testC[1] = 'e';
		testC[2] = '\0';
		testString = testC;
		std::string testS = testC;

		free(testC);

		std::cout << testS << std::endl;

	}

	std::cout << testString << std::endl;

	std::vector<int> testVec = { 0,1,2,5 };
	std::cout << sizeof(testVec) << std::endl;
	testVec.push_back(9);
	std::cout << sizeof(testVec[0])*testVec.size() << std::endl;
	std::cout << testVec.capacity() << std::endl;

	std::vector<std::shared_ptr<std::string>> mcodes;

	mcodes.resize(3);

	for (size_t i = 0; i < 2; i++)
	{
		mcodes[i] = std::make_shared<std::string>();
		std::string &testString = *mcodes[i];
		testString = "Hello nimei";
	}

	for (size_t i = 0; i < 3; i++)
	{
		if (mcodes[i] == nullptr)
		{
			std::cout << i << "th shared_ptr is NULL" << std::endl;
		}
		else
		{
			std::cout << i << "th shared_ptr is " << *mcodes[i] << std::endl;

		}
	}

	std::shared_ptr<std::vector<int>> sharedPtrVec = std::make_shared<std::vector<int>>();

	sharedPtrVec->push_back(24);
	sharedPtrVec->push_back(25);
	sharedPtrVec->push_back(26);

	std::cout << (*sharedPtrVec)[0] << std::endl;
	std::cout << (*sharedPtrVec)[1] << std::endl;
	std::cout << (*sharedPtrVec)[2] << std::endl;

	char *testPointer = NULL;

	delete testPointer;

	TestTemplateExport<int> testTemp(-1);

	std::cout << "pow test: " << pow(-1.4425, 1.0 / 3) << std::endl;
	std::cout << "acos test: " << acos(-1) << std::endl;
	std::cout << "atan2 test: " << atan2( 1.0, -1.0) << std::endl;

	std::ofstream fs;

	for (size_t i = 0; i < 100; i++)
	{
		std::cout << RandomInRange(0, 3) << std::endl;
	}

	cv::Vec3d test3V(1.09, 0.0, 0.0);
	cv::Point3d testPt;
	testPt = test3V;

	double a = 0.1;
	std::cout << "log(a) = " << log(a) << std::endl;
	std::cout << "exp(log(a)) = " << exp(log(a)) << std::endl;
	std::cout << "norm(test3V) = " << cv::norm(test3V/*, cv::NORM_L2SQR*/) << std::endl;

	char testArr[1024];
	testArr[0] = '1';
	testArr[1] = '2';
	testArr[2] = 0;
	testArr[3] = '3';
	testArr[4] = '4';
	testArr[5] = 0;

	std::string s1 = testArr;
	std::string s2 = testArr + 3;

	std::cout << "int size = " << sizeof(int) << " bytes" << std::endl;
	std::cout << "float size = " << sizeof(float) << " bytes" << std::endl;

	std::string testStr = "Hello World\\";
	testStr.replace(1, 2, "NIMA");
	std::string path = testStr.substr(0, testStr.find_last_of("/\\"));
	std::string emptyStr = "sdfa";
	emptyStr = "";
	if (emptyStr.empty())
	{
		std::cout << "EmptyStr is equal to \"\"" << std::endl;
	}

	uchar v = '\0';
	v++;
	int vcount = v;

	testStr = "123 123 12";
	std::stringstream ioStr;
	ioStr << testStr;
	std::vector<int> vInts;
	int intValue = 0;
	while (ioStr >> intValue)
	{
		vInts.push_back(intValue);
	}
	//ioStr.clear();
	ioStr << "12 23";
	while (ioStr >> intValue)
	{
		vInts.push_back(intValue);
	}

	{
		std::fstream fs2("test.txt", std::ios::out);
		fs2 << 12 << " " << 23 << std::endl;
		fs2 << 56 << " " << 78 << std::endl;
		fs2.close();
	}
	

	std::fstream fs2("test.txt", std::ios::in);
	int c, d;
	fs2 >> c >> d;
	std::string line;
	std::getline(fs2, line);
	std::getline(fs2, line);

	std::map<cv::Rect, int> testMap;
	cv::Rect rect(0, 0, 1, 1);
	testMap.find(rect);

	double dtest = 0.99999;
	int itest = std::round(dtest);
	std::cout << "itest = " << itest << std::endl;

	cv::Mat arrowTest(100, 100, CV_8UC3, cv::Scalar(255, 255, 255));

	cv::arrowedLine(arrowTest, cv::Point(50, 50), cv::Point(50 + 1, 50 + 1), cv::Scalar(0, 0, 255), 1, cv::LineTypes::LINE_AA, 0, 0.1);

	size_t ts = sizeof(PixelSelectorStatus);

	TestClass tc;
	tc.printA();

	return 0;
}