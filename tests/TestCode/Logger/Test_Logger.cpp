#include "Test_Logger.h"

int Test_Logger_run_test(const std::string vTestCode)
{
	if (vTestCode.find("Logger.1") != std::string::npos)
	{
		return 0;
	}

	return 1; // error
	return 0; // ok
}