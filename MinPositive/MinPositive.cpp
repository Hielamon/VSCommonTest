#include <iostream>
#include <vector>
#include <string>

int main()
{
	char inchar = '\0';
	bool label[256] = { false };
	std::string result = "";
	std::string src;
	std::getline(std::cin, src);
	for (size_t i = 0; i < src.size(); i++)
	{
		inchar = src[i];
		if (!label[int(inchar)])
		{
			label[int(inchar)] = true;
			result += inchar;
		}
	}

	std::cout << result << std::endl;
	return 0;
}