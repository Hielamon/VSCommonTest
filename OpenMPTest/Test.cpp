//#define HL_INTERVAL
#include <commonMacro.h>

void TestFuc()
{
	HL_INTERVAL_START

	int n = 1000;
	int a = 0;
	for (size_t i = 0; i < n; i++)
	{
		a += i;
	}

	HL_INTERVAL_END
}