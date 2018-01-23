#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> GetMaxSubSequence(const vector<int> &seq)
{
	vector<int> vIntegral = seq;
	int len = seq.size();
	
	for (size_t i = 1, j = 0; i < len; i++, j++)
	{
		vIntegral[i] += vIntegral[j];
	}
	int maxValue = vIntegral[0];
	int maxI = 0;
	int maxJ = 1;
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len; j++)
		{
			int seqValue = vIntegral[j] - (i == 0 ? 0 : vIntegral[i - 1]);
			if (seqValue > maxValue)
			{
				maxValue = seqValue;
				maxI = i;
				maxJ = j;
			}
		}
	}

	return vector<int>(seq.begin() + maxI, seq.begin() + maxJ + 1);
}

int main()
{
	vector<int> inputSeq = {-23, 17, -7, 11, -2, 1, -34};
	vector<int> result = GetMaxSubSequence(inputSeq);
	return 0;
}