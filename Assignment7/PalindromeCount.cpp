#include <iostream>

int getResult(int64_t in)
{
	int64_t tmp = in;
	int preNum = 0;
	for (; preNum < 64; preNum++)
	{
		if (tmp < 0) break;
		tmp = tmp << 1;
	}

	int lastNum = 64 - preNum;
	int remain = lastNum % 2 == 0 ? (lastNum - 2) / 2 : (lastNum - 1) / 2;
	if (remain == 0)
	{
		return 0;
	}
	else
	{
		int remainNum = pow(2, remain);
		int otherNum = 0;
		int64_t t = 1 & in;
		if (t == 1)
		{
			int64_t subIn = in;
			
			int64_t t2 = (1 << (63 - preNum)) - 1;
			subIn = subIn & t2;
			subIn = subIn >> 1;
			otherNum = getResult(subIn);
		}
		return otherNum + remain;
	}
}

int main()
{
	int64_t a = 11;

	while (std::cin>>a)
	{
		std::cout << getResult(a) << std::endl;
	}

	return 0;
}