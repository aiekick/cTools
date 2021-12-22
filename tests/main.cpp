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

	run_test("cTools.double.Vec4.length");
	run_test("cTools.uint.Vec3.*=a");
	run_test("cTools.uint.Vec3.*=Vec3");
	run_test("cTools.uint.Vec3.string");

	return 0;
}