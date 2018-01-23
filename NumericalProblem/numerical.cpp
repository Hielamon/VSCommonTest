#include <iostream>

#include <numeric>

int main(int argc, char *argv[])
{
	float nanTest = std::numeric_limits<float>::quiet_NaN();
	float a = std::numeric_limits<float>::quiet_NaN();
	if (_isnanf(nanTest))
	{
		std::cout << "nanTest is " << nanTest << std::endl;
	}

	return 0;
}