#include <iostream>

#include "winGlob.h"

int main(int argc, char *argv)
{
	std::vector<std::string> filelist;
	winGlob("image/*.jpg", filelist);
	for (auto &filename : filelist)
	{
		std::cout << filename << std::endl;
	}
	return 0;
}