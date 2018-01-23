#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

bool checkValid(string &str)
{
	stack<char> checkStack;
	for (size_t i = 0; i < str.size(); i++)
	{
		char curChar = str[i];
		if (curChar == '(')
		{
			checkStack.push(curChar);
		}
		else if(curChar == ')' && checkStack.size() > 0 &&
				checkStack.top() == '(')
		{
			checkStack.pop();
		}
		else
		{
			return false;
		}
	}

	return checkStack.size() == 0;
}

vector<string> getAllMatches(string &str)
{
	char preChar = '\0';
	for (size_t i = 0; i < str.size(); i++)
	{
		char curChar = str[i];
		if (curChar != preChar)
		{

		}
		preChar = curChar;
	}
	return vector<string>();
}

int main()
{
	string inputStr = "(())()";
	bool isValid = checkValid(inputStr);
	return 0;
}