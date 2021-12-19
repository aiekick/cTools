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

	run_test("cTools.double.Vec2.!=Vec2");
	run_test("cTools.float.Vec2.!=Vec2");
	run_test("cTools.bool.Vec2.!=a");
	run_test("cTools.bool.Vec2.!=Vec2");

	return 0;
}