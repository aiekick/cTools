#include "Test_FileHelper.h"

int Test_FileHelper_run_test(const std::string vTestCode)
{
	if (vTestCode.find("FileHelper.1") != std::string::npos)
	{
		return 0;
	}

	return 1; // error
	return 0; // ok
}