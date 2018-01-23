#include <iostream>

#define MAIN_FILE
#include <commonMacro.h>

#include "Test.h"

int main(int argc, char *argv[])
{
	HL_INTERVAL_START;

	std::string a = "test";

	int n = 100;
#ifdef _OPENMP
#pragma omp parallel for
#endif // _OPENMP
	for (int i = 0; i < n; i++)
	{
		std::cout << "for index : " << i << std::endl;
	}

	HL_INTERVAL_END;

	TestFuc();

	return 0;
}