#include <iostream>
#include <vector>
#include <string>

int main()
{
	char inchar;
	bool label[512] = { false };
	std::string result = "";
	while (std::cin >> inchar)
	{
		if (!label[int(inchar) + 128])
		{
			label[int(inchar) + 128] = true;
			result += inchar;
		}
	}

	std::cout << result << std::endl;
	return 0;
}