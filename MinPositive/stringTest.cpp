#include <iostream>
#include <vector>
#include <string>

int main()
{
	char inchar;
	bool label[256] = { false };
	std::string result = "";
	while (std::cin >> inchar)
	{
		if (!label[int(inchar)])
		{
			label[int(inchar)] = true;
			result += inchar;
		}
	}

	std::cout << result << std::endl;
	return 0;
}