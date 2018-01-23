#include <iostream>
#include <random>
#include <chrono>
#include <string>

int main()
{
	const int nrolls = 10000;  // number of experiments
	const int nstars = 100;    // maximum number of stars to distribute
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::normal_distribution<double> distribution(5.0, 2.0);

	int p[10] = {};

	for (int i = 0; i<nrolls; ++i) {
		double number = distribution(generator);
		if ((number >= 0.0) && (number<10.0)) ++p[int(number)];
	}

	std::cout << "normal_distribution (5.0,2.0):" << std::endl;

	for (int i = 0; i<10; ++i) {
		std::cout << i << "-" << (i + 1) << ": ";
		std::cout << std::string(p[i] * nstars / nrolls, '*') << std::endl;
	}

	return 0;
}