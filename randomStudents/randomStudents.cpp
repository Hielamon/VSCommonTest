#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>

int main(int argc, char *argv[])
{
	std::cout << "什么情况" << std::endl;
	std::fstream fs("StudentsAssignmentTable.txt", std::ios::in);
	std::string labels[3] = { "学号",	 "姓名", "专业"};
	std::vector<std::string> numbers;
	std::vector<std::string> names;
	std::vector<std::string> majors;

	while (!fs.eof())
	{
		std::string tmpStr;
		fs >> tmpStr;
		numbers.push_back(tmpStr);

		fs >> tmpStr;
		names.push_back(tmpStr);

		fs >> tmpStr;
		majors.push_back(tmpStr);
	}

	fs.close();


	int total = numbers.size();
	int maxNum = 30;
	std::vector<bool> selected(total, false);


	srand(time(0));
	
	for (size_t i = 0; i < maxNum;)
	{
		int idx = rand() % total;
		if (!selected[idx])
		{

			std::cout << "ID: " << i + 1 << " ";
			std::cout << labels[0] << ": " << numbers[idx] << " ";
			std::cout << labels[1] << ": " << names[idx] << " ";
			std::cout << labels[2] << ": " << majors[idx] << std::endl;
			selected[idx] = true;

			i++;
			system("PAUSE");

		}
	}

	return 0;
}