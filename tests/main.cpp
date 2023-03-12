#include "TestCode/TestCode.h"
#include <string>

int main(int argc, char** argv)
{
	if (argc > 1)
	{
		printf("Exec test : %s\n", argv[1]);

		return run_test(argv[1]);
	}
	
	// this code will be executed if not called by the tester

	return run_test("cTools.float.Plane.construtor.3_points");

	return 0;
}