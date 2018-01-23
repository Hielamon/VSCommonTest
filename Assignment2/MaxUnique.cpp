#include <iostream>
#include <vector>
#include <algorithm>

unsigned int GetMaxUnique(unsigned int &srcValue)
{
	bool appearNum[10];
	bool orderNum[10][10];

	for (size_t i = 0; i < 10; i++)
	{
		appearNum[i] = false;
		for (size_t j = 0; j < 10; j++)
		{
			orderNum[i][j] = false;
		}
	}

	unsigned int remain = srcValue;
	while (remain)
	{
		unsigned int residue = remain % 10;
		appearNum[residue] = true;
		remain -= residue;
		remain /= 10;

		for (size_t i = 0; i < 10; i++)
		{
			if (appearNum[i])
			{
				orderNum[residue][i] = true;
			}
		}
	}

	std::vector<int> appearVec;
	for (size_t i = 0; i < 10; i++)
	{
		if (appearNum[i]) { appearVec.push_back(i); }
	}
	std::sort(appearVec.begin(), appearVec.end());
	std::vector<bool> extractedNum(appearVec.size(), false);


	unsigned int result = 0;

	unsigned int curScale = 1;

	for (size_t k = 0; k < appearVec.size(); k++)
	{
		for (size_t i = 0; i < appearVec.size(); i++)
		{
			if (!extractedNum[i])
			{
				bool valid = true;
				for (size_t j = 0; j < appearVec.size(); j++)
				{
					if (!extractedNum[j])
					{
						valid &= orderNum[appearVec[j]][appearVec[i]];
					}
				}

				if (valid)
				{
					result += (appearVec[i] * curScale);
					extractedNum[i] = true;
					break;
				}
			}
		}
		curScale *= 10;
	}

	return result;
}

int main(int argc, char *argv[])
{
	std::cout << "Input: srcValue" << std::endl;
	unsigned int srcValue = 432123321;
	while (std::cin>>srcValue)
	{
		std::cout << "Max unique result = " << GetMaxUnique(srcValue) << std::endl;;
	}
	return 0;
}