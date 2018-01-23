#include <iostream>

#include <numeric>

int main(int argc, char *argv[])
{
	float nanTest = std::numeric_limits<float>::quiet_NaN();
	float a = nanTest;
	if (_isnanf(a))
	{
		std::cout << "nanTest is " << nanTest << std::endl;
	}

	return 0;
}