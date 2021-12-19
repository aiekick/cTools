#include "Test_cTools.h"
#include <cTools.h>

int Test_cTools_Vec2_run_test(const std::string vTestCode)
{
	ct::fvec2 v(5.0f, 2.0f);

	if (vTestCode == "cTools.Vec2.[]")
	{
		if (IS_FLOAT_EQUAL(v[0], 5.0f) &&
			IS_FLOAT_EQUAL(v[1], 2.0f))
			return 0;
	}
	else if (vTestCode == "cTools.Vec2.post++")
	{
		auto vc = v++;
		if (IS_FLOAT_EQUAL(vc.x, 5.0f) &&
			IS_FLOAT_EQUAL(vc.y, 2.0f) &&
			IS_FLOAT_EQUAL(v.x, 6.0f) &&
			IS_FLOAT_EQUAL(v.y, 3.0f))
			return 0;
	}
	else if (vTestCode == "cTools.Vec2.post--")
	{
		auto vc = v--;
		if (IS_FLOAT_EQUAL(vc.x, 5.0f) &&
			IS_FLOAT_EQUAL(vc.y, 2.0f) &&
			IS_FLOAT_EQUAL(v.x, 4.0f) &&
			IS_FLOAT_EQUAL(v.y, 1.0f))
			return 0;
	}
	else if (vTestCode == "cTools.Vec2.pre++")
	{
		auto vc = ++v;
		if (IS_FLOAT_EQUAL(vc.x, 6.0f) &&
			IS_FLOAT_EQUAL(vc.y, 3.0f) &&
			IS_FLOAT_EQUAL(v.x, 6.0f) &&
			IS_FLOAT_EQUAL(v.y, 3.0f))
			return 0;
	}
	else if (vTestCode == "cTools.Vec2.pre--")
	{
		auto vc = --v;
		if (IS_FLOAT_EQUAL(vc.x, 4.0f) &&
			IS_FLOAT_EQUAL(vc.y, 1.0f) &&
			IS_FLOAT_EQUAL(v.x, 4.0f) &&
			IS_FLOAT_EQUAL(v.y, 1.0f))
			return 0;
	}
	else if (vTestCode == "cTools.Vec2.+=a")
	{
		v += 2.5f;
		if (IS_FLOAT_EQUAL(v.x, 7.5f) &&
			IS_FLOAT_EQUAL(v.y, 4.5f))
			return 0;
	}
	else if (vTestCode == "cTools.Vec2.+=Vec2")
	{
		v += ct::fvec2(2.0f, 4.0f);
		if (IS_FLOAT_EQUAL(v.x, 7.0f) &&
			IS_FLOAT_EQUAL(v.y, 6.0f))
			return 0;
	}
	else if (vTestCode == "cTools.Vec2.-=a")
	{
		v -= 2.5f;
		if (IS_FLOAT_EQUAL(v.x, 2.5f) &&
			IS_FLOAT_EQUAL(v.y, -0.5f))
			return 0;
	}
	else if (vTestCode == "cTools.Vec2.-=Vec2")
	{
		v -= ct::fvec2(2.0f, 4.0f);
		if (IS_FLOAT_EQUAL(v.x, 3.0f) &&
			IS_FLOAT_EQUAL(v.y, -2.0f))
			return 0;
	}
	else if (vTestCode == "cTools.Vec2.==a")
	{
		v = 2.5f;
		bool vb = (v == 2.5f);
		if (vb == true)
			return 0;
	}
	else if (vTestCode == "cTools.Vec2.==Vec2")
	{
		bool vb = (v == ct::fvec2(5.0f, 2.0f));
		if (vb == true)
			return 0;
	}
	else if (vTestCode == "cTools.Vec2.!=a")
	{
		v = 2.5f;
		bool vb = (v != 5.0f);
		if (vb == true)
			return 0;
	}
	else if (vTestCode == "cTools.Vec2.!=Vec2")
	{
		bool vb =
			(v != ct::fvec2(6.0f, 2.0f)) &&
			(v != ct::fvec2(5.0f, 3.0f)) &&
			(v != ct::fvec2(6.0f, 3.0f));
		if (vb == true)
			return 0;
	}
	else if (vTestCode == "cTools.Vec2.*=a")
	{
		v *= 2.0f;
		if (IS_FLOAT_EQUAL(v.x, 10.0f) &&
			IS_FLOAT_EQUAL(v.y, 4.0f))
			return 0;
	}
	else if (vTestCode == "cTools.Vec2.*=Vec2")
	{
		v *= ct::fvec2(2.0f, 4.0f);
		if (IS_FLOAT_EQUAL(v.x, 10.0f) &&
			IS_FLOAT_EQUAL(v.y, 8.0f))
			return 0;
	}
	else if (vTestCode == "cTools.Vec2./=a")
	{
		v /= 2.0f;
		if (IS_FLOAT_EQUAL(v.x, 2.5f) &&
			IS_FLOAT_EQUAL(v.y, 1.0f))
			return 0;
	}
	else if (vTestCode == "cTools.Vec2./=Vec2")
	{
		v /= ct::fvec2(2.0f, 4.0f);
		if (IS_FLOAT_EQUAL(v.x, 2.5f) &&
			IS_FLOAT_EQUAL(v.y, 0.5f))
			return 0;
	}
	else if (vTestCode == "cTools.Vec2.lengthSquared")
	{
		v = ct::fvec2(5.0f, 2.0f);
		float len = v.lengthSquared();
		if (IS_FLOAT_EQUAL(len, 29.0f))
			return 0;
	}
	else if (vTestCode == "cTools.Vec2.length")
	{
		float len = v.length();
		if (IS_FLOAT_EQUAL(len, 5.3851648071345040312507104915403f))
			return 0;
	}
	else if (vTestCode == "cTools.Vec2.normalize")
	{
		float pre_len = v.length();
		v.normalize();
		float post_len = v.length();
		if (IS_FLOAT_DIFFERENT(pre_len, 1.0f) &&
			IS_FLOAT_EQUAL(post_len, 1.0f))
			return 0;
	}
	else if (vTestCode == "cTools.Vec2.GetNormalized")
	{
		auto vn = v.GetNormalized();
		float len = vn.length();
		if (IS_FLOAT_EQUAL(len, 1.0f))
			return 0;
	}
	else if (vTestCode == "cTools.Vec2.sum")
	{
		v = ct::fvec2(5.0f, -2.0f);
		float len = v.sum();
		if (IS_FLOAT_EQUAL(len, 3.0f))
			return 0;
	}
	else if (vTestCode == "cTools.Vec2.sumAbs")
	{
		v = ct::fvec2(5.0f, -2.0f);
		float len = v.sumAbs();
		if (IS_FLOAT_EQUAL(len, 7.0f))
			return 0;
	}
	else if (vTestCode == "cTools.Vec2.emptyAND")
	{
		v = ct::fvec2(0.0f, -2.0f);
		bool vb = v.emptyAND();
		if (vb == false)
			return 0;
	}
	else if (vTestCode == "cTools.Vec2.emptyOR")
	{
		v = ct::fvec2(0.0f, -2.0f);
		bool vb = v.emptyOR();
		if (vb == true)
			return 0;
	}
	else if (vTestCode == "cTools.Vec2.string")
	{
		v = ct::fvec2(5.35f, -2.8f);
		auto str = v.string();
		auto str_coma = v.string(',');
		if (str == "5.35;-2.8" && 
			str_coma == "5.35,-2.8")
			return 0;
	}
	else if (vTestCode == "cTools.Vec2.ratioXY")
	{
		float pre_r = v.ratioXY();
		v.y = 0.0f;
		float post_r = v.ratioXY(); // return 0
		if (IS_FLOAT_EQUAL(pre_r, 2.5f) &&
			IS_FLOAT_EQUAL(post_r, 0.0f))
			return 0;
	}
	else if (vTestCode == "cTools.Vec2.ratioYX")
	{
		float pre_r = v.ratioYX();
		v.x = 0.0f;
		float post_r = v.ratioYX(); // return 0
		if (IS_FLOAT_EQUAL(pre_r, 0.4f) &&
			IS_FLOAT_EQUAL(post_r, 0.0f))
			return 0;
	}
	else if (vTestCode == "cTools.Vec2.mini")
	{
		float mini = v.mini();
		if (IS_FLOAT_EQUAL(mini, 2.0f))
			return 0;
	}
	else if (vTestCode == "cTools.Vec2.maxi")
	{
		float maxi = v.maxi();
		if (IS_FLOAT_EQUAL(maxi, 5.0f))
			return 0;
	}

	return 1; // error
}

int Test_cTools_run_test(const std::string vTestCode)
{
	if (vTestCode.find("cTools.") != std::string::npos)
	{
		return Test_cTools_Vec2_run_test(vTestCode);
	}

	return 1; // error
}