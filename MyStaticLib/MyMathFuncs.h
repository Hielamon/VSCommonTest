#pragma once

#ifdef TEST_EXPORT
#define TEST_API __declspec(dllexport)
#else
#define TEST_API 
#endif //TEST_EXPORT
namespace MathFuncs
{
	 class MyMathFuncs
	{
	public:
		// Returns a + b
		static double Add(double a, double b);

		// Returns a - b
		static double Subtract(double a, double b);

		// Returns a * b
		static double Multiply(double a, double b);

		// Returns a / b
		static double Divide(double a, double b);
	};
}