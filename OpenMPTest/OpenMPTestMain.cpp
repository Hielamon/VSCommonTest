#include <iostream>
#include <vector>

#define MAIN_FILE
#include <commonMacro.h>

#include "Test.h"

int main(int argc, char *argv[])
{
	HL_INTERVAL_START;

	std::string a = "test";

	int n = 1000000;
	std::vector<double> result(n, 0.0);
//#ifdef _OPENMP
#pragma omp parallel for num_threads(n)
//#endif // _OPENMP
	for (int i = 0; i < n; i++)
	{
		//std::cout << "for index : " << i << std::endl;
		result[i] += (i*i + i*i);
		result[i] = result[i] * i / (i + 1);
	}

	std::cout << "result[0] =  : " << result[0] << std::endl;

	HL_INTERVAL_END;

	TestFuc();

	return 0;
}