#include <iostream>

#include <numeric>
#include <commonMacro.h>

int main(int argc, char *argv[])
{
	float nanTest = std::numeric_limits<float>::quiet_NaN();
	float a = nanTest;
	if (_isnanf(a))
	{
		std::cout << "nanTest is " << nanTest << std::endl;
	}

	float b = 1.99, c = 2.0;
	int d = b / c;

	int count = 10000000;
	float result = 0;

	HL_INTERVAL_START;
	for (size_t i = 0; i < count; i++)
	{
		//for (size_t j = 0; j < count; j++)
		{
			result += sin(float(i));
		}
	}
	HL_INTERVAL_ENDSTR("sin function");

	HL_INTERVAL_START;
	for (size_t i = 0; i < count; i++)
	{
		//for (size_t j = 0; j < count; j++)
		{
			result += (result*i);
		}
	}
	HL_INTERVAL_ENDSTR("multi function");


	return 0;
}