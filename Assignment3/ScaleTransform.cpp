#include <iostream>
#include <string>
#include <cassert>

bool char2Int(const char &c, int &dst)
{
	if (c >= '0' && c <= '9')
	{
		dst = int(c) - 48;
	}
	else if(c >= 'a' && c <= 'z')
	{
		dst = int(c) - 97 + 10;
	}
	else if(c >= 'A' && c <= 'Z')
	{
		dst = int(c) - 65 + 36;
	}
	else
	{
		return false;
	}

	return true;
}

bool int2Char(const int &src, char &c)
{
	if (src >= 0 && src <= 9)
	{
		c = char(src + 48);
	}
	else if (src >= 10 && src <= 35)
	{
		c = char(src - 10 + 97);
	}
	else if (src >= 36 && src <= 61)
	{
		c = char(src -36 + 65);
	}
	else
	{
		return false;
	}

	return true;
}

int TransformToDecimal(const int& srcScale, const std::string& value)
{
	assert(srcScale >= 2 && srcScale <= 62);
	int result = 0;
	int curScale = 1;
	int posValue = 0;
	for (int i = value.length() - 1; i >= 0; i--)
	{
		if (!char2Int(value[i], posValue))
		{
			std::cerr << "Invalid Input" << std::endl;
			exit(-1);
		}

		result += (posValue * curScale);
		curScale *= srcScale;
	}

	return result;
}

std::string TransformFromDecimal(const int& dstScale, const int& value)
{
	std::string result;
	assert(dstScale >= 2 && dstScale <= 62);
	int remain = value;
	int curScale = 1;
	char posChar;
	while (remain > 0)
	{
		int residue = remain % dstScale;
		int2Char(residue, posChar);
		result = posChar + result;

		remain -= residue;
		remain /= dstScale;
	}

	return result;
}

void TranformScale(const int& srcScale, const int& dstScale,
				   const std::string& srcValue, std::string& dstValue)
{
	if (srcValue.length() == 0)
	{
		dstValue = "";
		return;
	}
	std::string srcValueTmp = srcValue;
	std::string sign = "";
	if (srcValue[0] == '-')
	{
		sign = "-";
		srcValueTmp.assign(srcValue.c_str() + 1, srcValue.c_str() + srcValue.length());
	}

	int decimal = TransformToDecimal(srcScale, srcValueTmp);
	dstValue = TransformFromDecimal(dstScale, decimal);

	dstValue = sign + dstValue;
}

int main(int argc, char *argv[])
{
	std::cout << "Input: srcScale dstScale srcValue" << std::endl;
	int srcScale = 8, dstScale = 16;
	std::string srcValue = "12345670", dstValue;
	while (std::cin >> srcScale && std::cin >> dstScale && std::cin >> srcValue)
	{
		TranformScale(srcScale, dstScale, srcValue, dstValue);
		std::cout << "Transform result is : " << dstValue << std::endl;
	}
	return 0;
}