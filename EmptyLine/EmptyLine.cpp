#include <fstream>
#include <iostream>
#include <string>

int main()
{
	std::fstream fs("test.txt", std::ios::in);

	std::string line;
	while (1)
	{
		if (!std::getline(fs, line))
			break;
		if (line.empty())
		{
			std::cout << "Empty Line" << std::endl;
		}
		else
		{
			std::cout << line << std::endl;
		}
	}
	return 0;
}