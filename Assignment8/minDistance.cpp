#include <iostream>
#include <vector>


int main(int argc, char *argv[])
{
	std::vector<int> testArr;
	testArr[0] = 1;
	int n, m;
	std::cin >> n >> m;
	std::vector<int> vNo(m);
	std::vector<bool> vLabel(n, false);
	
	int min = 1e10, max = -1;
	for (size_t i = 0; i < m; i++)
	{
		std::cin >> vNo[i];
		vLabel[vNo[i] - 1] = true;
		if (vNo[i] > max) max = vNo[i];
		if (vNo[i] < min) min = vNo[i];
	}

	int minDistance = 1e10, minIdx = max < n ? (max + 1) : n;
	int medianMinIdx = min;
	bool inMedian = false;
	for (int i = min; i < max; i++)
	{
		if (!vLabel[i])
		{
			minIdx = i + 1;
			inMedian = true;
			break;
		}
	}

	if (!inMedian && min > 1)
	{
		minIdx = min - 1;
	}

	std::cout << minIdx;
	return 0;
}