#include "Test_cTools.h"
#include <cTools.h>

template <typename T>
inline bool is_equal(const T& vA, const T& vB)
{
	return false;
}

template <>
inline bool is_equal(const double& vA, const double& vB)
{
	return (IS_DOUBLE_EQUAL(vA, vB));
}

template <>
inline bool is_equal(const float& vA, const float& vB)
{
	return (IS_FLOAT_EQUAL(vA, vB));
}

// ok for double or float
template <typename T>
int Test_cTools_Vec2_run_test(const std::string vTestCode)
{
	ct::vec2<T> v((T)5.0, (T)2.0);

	if (vTestCode.find(".Vec2.[]") != std::string::npos)
	{
		if (is_equal(v[0], (T)5.0) &&
			is_equal(v[1], (T)2.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.post++") != std::string::npos)
	{
		auto vc = v++;
		if (is_equal(vc.x, (T)5.0) &&
			is_equal(vc.y, (T)2.0) &&
			is_equal(v.x, (T)6.0) &&
			is_equal(v.y, (T)3.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.post--") != std::string::npos)
	{
		auto vc = v--;
		if (is_equal(vc.x, (T)5.0) &&
			is_equal(vc.y, (T)2.0) &&
			is_equal(v.x, (T)4.0) &&
			is_equal(v.y, (T)1.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.pre++") != std::string::npos)
	{
		auto vc = ++v;
		if (is_equal(vc.x, (T)6.0) &&
			is_equal(vc.y, (T)3.0) &&
			is_equal(v.x, (T)6.0) &&
			is_equal(v.y, (T)3.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.pre--") != std::string::npos)
	{
		auto vc = --v;
		if (is_equal(vc.x, (T)4.0) &&
			is_equal(vc.y, (T)1.0) &&
			is_equal(v.x, (T)4.0) &&
			is_equal(v.y, (T)1.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.+=a") != std::string::npos)
	{
		v += (T)2.5f;
		if (is_equal(v.x, (T)7.5) &&
			is_equal(v.y, (T)4.5))
			return 0;
	}
	else if (vTestCode.find(".Vec2.+=Vec2") != std::string::npos)
	{
		v += ct::vec2<T>((T)2.0, (T)4.0);
		if (is_equal(v.x, (T)7.0) &&
			is_equal(v.y, (T)6.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.-=a") != std::string::npos)
	{
		v -= (T)2.5;
		if (is_equal(v.x, (T)2.5) &&
			is_equal(v.y, (T)-0.5))
			return 0;
	}
	else if (vTestCode.find(".Vec2.-=Vec2") != std::string::npos)
	{
		v -= ct::vec2<T>((T)2.0, (T)4.0);
		if (is_equal(v.x, (T)3.0) &&
			is_equal(v.y, (T)-2.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.==a") != std::string::npos)
	{
		v = (T)2.5;
		bool vb = (v == (T)2.5);
		if (vb == true)
			return 0;
	}
	else if (vTestCode.find(".Vec2.==Vec2") != std::string::npos)
	{
		bool vb = (v == ct::vec2<T>((T)5.0, (T)2.0));
		if (vb == true)
			return 0;
	}
	else if (vTestCode.find(".Vec2.!=a") != std::string::npos)
	{
		v = (T)2.5;
		bool vb = (v != (T)5.0);
		if (vb == true)
			return 0;
	}
	else if (vTestCode.find(".Vec2.!=Vec2") != std::string::npos)
	{
		bool vb =
			(v != ct::vec2<T>((T)6.0, (T)2.0)) &&
			(v != ct::vec2<T>((T)5.0, (T)3.0)) &&
			(v != ct::vec2<T>((T)6.0, (T)3.0));
		if (vb == true)
			return 0;
	}
	else if (vTestCode.find(".Vec2.*=a") != std::string::npos)
	{
		v *= (T)2.0;
		if (is_equal(v.x, (T)10.0) &&
			is_equal(v.y, (T)4.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.*=Vec2") != std::string::npos)
	{
		v *= ct::vec2<T>((T)2.0, (T)4.0);
		if (is_equal(v.x, (T)10.0) &&
			is_equal(v.y, (T)8.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2./=a") != std::string::npos)
	{
		v /= (T)2.0;
		if (is_equal(v.x, (T)2.5) &&
			is_equal(v.y, (T)1.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2./=Vec2") != std::string::npos)
	{
		v /= ct::vec2<T>((T)2.0, (T)4.0);
		if (is_equal(v.x, (T)2.5) &&
			is_equal(v.y, (T)0.5))
			return 0;
	}
	else if (vTestCode.find(".Vec2.lengthSquared") != std::string::npos)
	{
		v = ct::vec2<T>((T)5.0, (T)2.0);
		T len = v.lengthSquared();
		if (is_equal(len, (T)29.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.length") != std::string::npos)
	{
		T len = v.length();
		if (is_equal(len, (T)5.3851648071345040312507104915403))
			return 0;
	}
	else if (vTestCode.find(".Vec2.normalize") != std::string::npos)
	{
		T pre_len = v.length();
		v.normalize();
		T post_len = v.length();
		if ((!is_equal(pre_len, (T)1.0)) &&
			is_equal(post_len, (T)1.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.GetNormalized") != std::string::npos)
	{
		auto vn = v.GetNormalized();
		T len = vn.length();
		if (is_equal(len, (T)1.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.sum") != std::string::npos)
	{
		v = ct::vec2<T>((T)5.0, (T)-2.0);
		T len = v.sum();
		if (is_equal(len, (T)3.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.sumAbs") != std::string::npos)
	{
		v = ct::vec2<T>((T)5.0, (T)-2.0);
		T len = v.sumAbs();
		if (is_equal(len, (T)7.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.emptyAND") != std::string::npos)
	{
		v = ct::vec2<T>((T)0.0, (T)-2.0);
		bool vb = v.emptyAND();
		if (vb == false)
			return 0;
	}
	else if (vTestCode.find(".Vec2.emptyOR") != std::string::npos)
	{
		v = ct::vec2<T>((T)0.0, (T)-2.0);
		bool vb = v.emptyOR();
		if (vb == true)
			return 0;
	}
	else if (vTestCode.find(".Vec2.string") != std::string::npos)
	{
		v = ct::vec2<T>((T)5.35, (T)-2.8);
		auto str = v.string();
		auto str_coma = v.string(',');
		if (str == "5.35;-2.8" && 
			str_coma == "5.35,-2.8")
			return 0;
	}
	else if (vTestCode.find(".Vec2.ratioXY") != std::string::npos)
	{
		T pre_r = v.ratioXY();
		v.y = 0.0f;
		T post_r = v.ratioXY(); // return 0
		if (is_equal(pre_r, (T)2.5) &&
			is_equal(post_r, (T)0.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.ratioYX") != std::string::npos)
	{
		T pre_r = v.ratioYX();
		v.x = 0.0f;
		T post_r = v.ratioYX(); // return 0
		if (is_equal(pre_r, (T)0.4) &&
			is_equal(post_r, (T)0.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.mini") != std::string::npos)
	{
		T mini = v.mini();
		if (is_equal(mini, (T)2.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.maxi") != std::string::npos)
	{
		T maxi = v.maxi();
		if (is_equal(maxi, (T)5.0))
			return 0;
	}

	return 1; // error
}

// specialisation for bool
template <>
int Test_cTools_Vec2_run_test<bool>(const std::string vTestCode)
{
	ct::bvec2 v(true, false);

	if (vTestCode.find(".Vec2.[]") != std::string::npos)
	{
		if (v[0] == true &&
			v[1] == false)
			return 0;
	}
	else if (vTestCode.find(".Vec2.==a") != std::string::npos)
	{
		bool vb = (v == true);
		if (vb == false)
			return 0;
	}
	else if (vTestCode.find(".Vec2.==Vec2") != std::string::npos)
	{
		bool vb = (v == ct::bvec2(true, false));
		if (vb == true)
			return 0;
	}
	else if (vTestCode.find(".Vec2.!=a") != std::string::npos)
	{
		if (v != true)
			return 0;
	}
	else if (vTestCode.find(".Vec2.!=Vec2") != std::string::npos)
	{
		if ((v != ct::bvec2(false, true)) &&
			(v != ct::bvec2(true, true)) &&
			(v != ct::bvec2(false, false)))
			return 0;
	}
	else if (vTestCode.find(".Vec2.emptyAND") != std::string::npos)
	{
		bool vb = v.emptyAND();
		if (vb == false)
			return 0;
	}
	else if (vTestCode.find(".Vec2.emptyOR") != std::string::npos)
	{
		bool vb = v.emptyOR();
		if (vb == true)
			return 0;
	}
	else if (vTestCode.find(".Vec2.string") != std::string::npos)
	{
		auto str = v.string();
		auto str_coma = v.string(',');
		if (str == "1;0" &&
			str_coma == "1,0")
			return 0;
	}
	else if (vTestCode.find(".Vec2.mini") != std::string::npos)
	{
		bool mini = v.mini();
		if (mini == false)
			return 0;
	}
	else if (vTestCode.find(".Vec2.maxi") != std::string::npos)
	{
		bool maxi = v.maxi();
		if (maxi == true)
			return 0;
	}

	return 1; // error
}

int Test_cTools_run_test(const std::string vTestCode)
{
	if (vTestCode.find("cTools.double.") != std::string::npos)
	{
		return Test_cTools_Vec2_run_test<double>(vTestCode);
	}
	else if (vTestCode.find("cTools.float.") != std::string::npos)
	{
		return Test_cTools_Vec2_run_test<float>(vTestCode);
	}
	else if (vTestCode.find("cTools.bool.") != std::string::npos)
	{
		return Test_cTools_Vec2_run_test<bool>(vTestCode);
	}

	return 1; // error
}