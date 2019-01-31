#include <ppl.h>
#include <iostream>
#include <commonMacro.h>
#include <map>
#include <vector>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_access.hpp>
#include <glm/gtx/string_cast.hpp>

using namespace concurrency;

int main()
{
	int outNum = 10000, innerNum = 10;
	std::vector<glm::mat4> vM(outNum, glm::mat4());

	std::vector<glm::mat4> vresult(outNum);
	glm::mat4 result;

	HL_INTERVAL_START;
	for (size_t i = 0; i < vM.size(); i ++)
	{
		for (size_t j = 0; j < innerNum; j++)
		{
			vresult[i] += vM[i] * vM[i];
		}
	}
	HL_INTERVAL_ENDSTR("Origin");


	HL_INTERVAL_START;
	parallel_for(size_t(0), vM.size(), [&](size_t i)
	{
		for (size_t j = 0; j < innerNum; j++)
		{
			vresult[i] += vM[i] * vM[i];
		}
	});
	HL_INTERVAL_ENDSTR("PPL");

	std::cout << vresult[0][0][0] << std::endl;

	std::map<int, glm::mat4> mIDToMat;
	std::map<int, glm::mat4> mIDToMatTmp;
	std::map<int, bool> mIDToVisible;
	
	HL_INTERVAL_START;
	for (size_t i = 0; i < outNum; i++)
	{
		mIDToMat[i] = glm::mat4(float(i));
		mIDToMatTmp[i] = glm::mat4(1.0f);
		mIDToVisible[i] = false;
	}
	HL_INTERVAL_ENDSTR("Create map");

	HL_INTERVAL_START;
	std::for_each(mIDToMat.begin(), mIDToMat.end(), [&](/*const */std::pair<const int, glm::mat4>& pair)
	{
		for (size_t j = 0; j < innerNum; j++)
		{
			mIDToMatTmp[pair.first] = pair.second * glm::mat4(1.0f);
			mIDToVisible[pair.first] = pair.first % 2 == 0;
		}
		//std::cout << mIDToVisible[pair.first] << " ";
	});
	//std::cout << std::endl;
	HL_INTERVAL_ENDSTR("Origin");


	HL_INTERVAL_START;
	parallel_for_each(mIDToMat.begin(), mIDToMat.end(), [&](/*const */std::pair<const int, glm::mat4>& pair)
	{
		for (size_t j = 0; j < innerNum; j++)
		{
			mIDToMatTmp[pair.first] = pair.second * glm::mat4(1.0f);
			mIDToVisible[pair.first] = pair.first % 2 == 0;
		}
		//std::cout << mIDToVisible[pair.first] << " ";
	});
	std::cout << std::endl;
	HL_INTERVAL_ENDSTR("PPL");

	/*std::for_each(mIDToVisible.begin(), mIDToVisible.end(), [&](const std::pair<const int, bool>& pair)
	{
		std::cout << pair.second << " ";
	});
	std::cout << std::endl;*/

	return 0;
}