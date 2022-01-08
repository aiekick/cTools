#include "TestCode.h"
#include "cTools/Test_cTools.h"
#include "FileHelper/Test_FileHelper.h"
#include "Logger/Test_Logger.h"

int run_test(const std::string& vTestCode)
{
	if (vTestCode.find("cTools.") != std::string::npos)
	{
		return Test_cTools_run_test(vTestCode);
	}

	if (vTestCode.find("FileHelper.") != std::string::npos)
	{
		return Test_FileHelper_run_test(vTestCode);
	}

	if (vTestCode.find("Logger.") != std::string::npos)
	{
		return Test_Logger_run_test(vTestCode);
	}

	return 1;
}

