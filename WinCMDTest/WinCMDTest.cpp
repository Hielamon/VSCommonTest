#include <iostream>
#include <fstream>
#include <direct.h>
#include <sstream>

int main(int argc, char *argv[])
{
	char dir[1024];
	_getcwd(dir, 1024);
	std::cout << "Current Path = " << dir << std::endl;
	std::stringstream ioStr;
	ioStr << "cd \/d " << dir << std::endl;

	std::string command;
	command = ioStr.str();
	//system(command.c_str());

	command = "..\\x64\\Debug\\SubClassConstruction.exe";
	system(command.c_str());
	return 0;
}