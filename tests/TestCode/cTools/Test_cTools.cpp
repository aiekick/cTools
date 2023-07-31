#include "Test_cTools.h"
#include <ctools/ctools.h>

template <typename T>
inline bool is_equal(const T& vA, const T& vB)
{
	return (vA == vB);
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

///////////////////////////////////////////////////////////
/// VEC2 //////////////////////////////////////////////////
///////////////////////////////////////////////////////////

// ok for double or float
template <typename T>
int Test_cTools_Vec2_run_test(const std::string& vTestCode)
{
	ct::vec2<T> v((T)5.0, (T)2.0);

	if (vTestCode.find(".Vec2.[]") != std::string::npos)
	{
		if (is_equal(v[0], (T)5.0) &&
			is_equal(v[1], (T)2.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.Offset") != std::string::npos)
	{
		v = v.Offset((T)1.0, (T)2.0);
		if (is_equal(v.x, (T)6.0) &&
			is_equal(v.y, (T)4.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.Set") != std::string::npos)
	{
		v.Set((T)1.0, (T)2.0);
		if (is_equal(v.x, (T)1.0) &&
			is_equal(v.y, (T)2.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.-") != std::string::npos)
	{
		v = -v;
		if (is_equal(v.x, (T)-5.0) &&
			is_equal(v.y, (T)-2.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.post++") != std::string::npos)
	{
		const auto& vc = v++;
		if (is_equal(vc.x, (T)5.0) &&
			is_equal(vc.y, (T)2.0) &&
			is_equal(v.x, (T)6.0) &&
			is_equal(v.y, (T)3.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.post--") != std::string::npos)
	{
		const auto& vc = v--;
		if (is_equal(vc.x, (T)5.0) &&
			is_equal(vc.y, (T)2.0) &&
			is_equal(v.x, (T)4.0) &&
			is_equal(v.y, (T)1.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.pre++") != std::string::npos)
	{
		const auto& vc = ++v;
		if (is_equal(vc.x, (T)6.0) &&
			is_equal(vc.y, (T)3.0) &&
			is_equal(v.x, (T)6.0) &&
			is_equal(v.y, (T)3.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.pre--") != std::string::npos)
	{
		const auto& vc = --v;
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
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec2.==Vec2") != std::string::npos)
	{
		bool vb = (v == ct::vec2<T>((T)5.0, (T)2.0));
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec2.!=a") != std::string::npos)
	{
		v = (T)2.5;
		bool vb = (v != (T)5.0);
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec2.!=Vec2") != std::string::npos)
	{
		bool vb =
			(v != ct::vec2<T>((T)6.0, (T)2.0)) &&
			(v != ct::vec2<T>((T)5.0, (T)3.0)) &&
			(v != ct::vec2<T>((T)6.0, (T)3.0));
		if (vb)
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
		const auto& vn = v.GetNormalized();
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
		if (!vb)
			return 0;
	}
	else if (vTestCode.find(".Vec2.emptyOR") != std::string::npos)
	{
		v = ct::vec2<T>((T)0.0, (T)-2.0);
		bool vb = v.emptyOR();
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec2.string") != std::string::npos)
	{
		v = ct::vec2<T>((T)5.35, (T)-2.8);
		const auto& str = v.string();
		const auto& str_coma = v.string(',');
		if (str == "5.35;-2.8" && 
			str_coma == "5.35,-2.8")
			return 0;
	}
	else if (vTestCode.find(".Vec2.ratioXY") != std::string::npos)
	{
		T pre_r = v.template ratioXY<T>();
		v.y = (T)0.0;
		T post_r = v.template ratioXY<T>(); // return 0
		if (is_equal(pre_r, (T)2.5) &&
			is_equal(post_r, (T)0.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.ratioYX") != std::string::npos)
	{
		T pre_r = v.template ratioYX<T>();
		v.x = (T)0.0;
		T post_r = v.template ratioYX<T>(); // return 0
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
int Test_cTools_Vec2_run_test<bool>(const std::string& vTestCode)
{
	ct::bvec2 v(true, false);

	if (vTestCode.find(".Vec2.[]") != std::string::npos)
	{
		if (v[0] &&
			!v[1])
			return 0;
	}
	else if (vTestCode.find(".Vec2.Set") != std::string::npos)
	{
		v.Set(false, true);
		if (!v.x &&
			v.y)
			return 0;
	}
	else if (vTestCode.find(".Vec2.!") != std::string::npos)
	{
		v = !v;
		if (!v.x &&
			v.y)
			return 0;
	}
	else if (vTestCode.find(".Vec2.==a") != std::string::npos)
	{
		bool vb = (v==true);
		if (!vb)
			return 0;
	}
	else if (vTestCode.find(".Vec2.==Vec2") != std::string::npos)
	{
		bool vb = (v == ct::bvec2(true, false));
		if (vb)
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
		if (!vb)
			return 0;
	}
	else if (vTestCode.find(".Vec2.emptyOR") != std::string::npos)
	{
		bool vb = v.emptyOR();
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec2.string") != std::string::npos)
	{
		const auto& str = v.string();
		const auto& str_coma = v.string(',');
		if (str == "1;0" &&
			str_coma == "1,0")
			return 0;
	}
	else if (vTestCode.find(".Vec2.mini") != std::string::npos)
	{
		bool mini = v.mini();
		if (!mini)
			return 0;
	}
	else if (vTestCode.find(".Vec2.maxi") != std::string::npos)
	{
		bool maxi = v.maxi();
		if (maxi)
			return 0;
	}

	return 1; // error
}

// specialisation for signed integer
template <typename T>
int Test_cTools_signed_integer_Vec2_run_test(const std::string& vTestCode)
{
	ct::vec2<T> v((T)5.0, (T)2.0);

	if (vTestCode.find(".Vec2.[]") != std::string::npos)
	{
		if (is_equal(v[0], (T)5.0) &&
			is_equal(v[1], (T)2.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.Offset") != std::string::npos)
	{
		v = v.Offset((T)1.0, (T)2.0);
		if (is_equal(v.x, (T)6.0) &&
			is_equal(v.y, (T)4.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.Set") != std::string::npos)
	{
		v.Set((T)1.0, (T)2.0);
		if (is_equal(v.x, (T)1.0) &&
			is_equal(v.y, (T)2.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.-") != std::string::npos)
	{
		v = -v;
		if (is_equal(v.x, (T)-5.0) &&
			is_equal(v.y, (T)-2.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.post++") != std::string::npos)
	{
		const auto& vc = v++;
		if (is_equal(vc.x, (T)5.0) &&
			is_equal(vc.y, (T)2.0) &&
			is_equal(v.x, (T)6.0) &&
			is_equal(v.y, (T)3.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.post--") != std::string::npos)
	{
		const auto& vc = v--;
		if (is_equal(vc.x, (T)5.0) &&
			is_equal(vc.y, (T)2.0) &&
			is_equal(v.x, (T)4.0) &&
			is_equal(v.y, (T)1.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.pre++") != std::string::npos)
	{
		const auto& vc = ++v;
		if (is_equal(vc.x, (T)6.0) &&
			is_equal(vc.y, (T)3.0) &&
			is_equal(v.x, (T)6.0) &&
			is_equal(v.y, (T)3.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.pre--") != std::string::npos)
	{
		const auto& vc = --v;
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
		v -= (T)1.0;
		if (is_equal(v.x, (T)4.0) &&
			is_equal(v.y, (T)1.0))
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
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec2.==Vec2") != std::string::npos)
	{
		bool vb = (v == ct::vec2<T>((T)5.0, (T)2.0));
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec2.!=a") != std::string::npos)
	{
		v = (T)2.5;
		bool vb = (v != (T)5.0);
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec2.!=Vec2") != std::string::npos)
	{
		bool vb =
			(v != ct::vec2<T>((T)6.0, (T)2.0)) &&
			(v != ct::vec2<T>((T)5.0, (T)3.0)) &&
			(v != ct::vec2<T>((T)6.0, (T)3.0));
		if (vb)
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
		if (!vb)
			return 0;
	}
	else if (vTestCode.find(".Vec2.emptyOR") != std::string::npos)
	{
		v = ct::vec2<T>((T)0.0, (T)-2.0);
		bool vb = v.emptyOR();
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec2.string") != std::string::npos)
	{
		v = ct::vec2<T>((T)5.0, (T)-2.0);
		const auto& str = v.string();
		const auto& str_coma = v.string(',');
		if (str == "5;-2" &&
			str_coma == "5,-2")
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

// specialisation unsigned intergers
template <typename T>
int Test_cTools_unsigned_integer_Vec2_run_test(const std::string& vTestCode)
{
	ct::vec2<T> v((T)5.0, (T)2.0);

	if (vTestCode.find(".Vec2.[]") != std::string::npos)
	{
		if (is_equal(v[0], (T)5.0) &&
			is_equal(v[1], (T)2.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.Offset") != std::string::npos)
	{
		v = v.Offset((T)1.0, (T)2.0);
		if (is_equal(v.x, (T)6.0) &&
			is_equal(v.y, (T)4.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.Set") != std::string::npos)
	{
		v.Set((T)1.0, (T)2.0);
		if (is_equal(v.x, (T)1.0) &&
			is_equal(v.y, (T)2.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.post++") != std::string::npos)
	{
		const auto& vc = v++;
		if (is_equal(vc.x, (T)5.0) &&
			is_equal(vc.y, (T)2.0) &&
			is_equal(v.x, (T)6.0) &&
			is_equal(v.y, (T)3.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.post--") != std::string::npos)
	{
		const auto& vc = v--;
		if (is_equal(vc.x, (T)5.0) &&
			is_equal(vc.y, (T)2.0) &&
			is_equal(v.x, (T)4.0) &&
			is_equal(v.y, (T)1.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.pre++") != std::string::npos)
	{
		const auto& vc = ++v;
		if (is_equal(vc.x, (T)6.0) &&
			is_equal(vc.y, (T)3.0) &&
			is_equal(v.x, (T)6.0) &&
			is_equal(v.y, (T)3.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.pre--") != std::string::npos)
	{
		const auto& vc = --v;
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
		v -= (T)1.0;
		if (is_equal(v.x, (T)4.0) &&
			is_equal(v.y, (T)1.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.-=Vec2") != std::string::npos)
	{
		v -= ct::vec2<T>((T)2.0, (T)1.0);
		if (is_equal(v.x, (T)3.0) &&
			is_equal(v.y, (T)1.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.==a") != std::string::npos)
	{
		v = (T)2.5;
		bool vb = (v == (T)2.5);
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec2.==Vec2") != std::string::npos)
	{
		bool vb = (v == ct::vec2<T>((T)5.0, (T)2.0));
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec2.!=a") != std::string::npos)
	{
		v = (T)2.5;
		bool vb = (v != (T)5.0);
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec2.!=Vec2") != std::string::npos)
	{
		bool vb =
			(v != ct::vec2<T>((T)6.0, (T)2.0)) &&
			(v != ct::vec2<T>((T)5.0, (T)3.0)) &&
			(v != ct::vec2<T>((T)6.0, (T)3.0));
		if (vb)
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
	else if (vTestCode.find(".Vec2.sum") != std::string::npos)
	{
		// ca c'est marrant -2 en unsigned renvoi limit -2 avec MSVC
		// et la somme est bonne car limit - 2 + 5 en usingned vaut 3 comme en signed :)
		// en gcc -2 renvoi 0 donc ca fail avec gcc
		v = ct::vec2<T>((T)5.0, (T)2.0);
		T len = v.sum();
		if (is_equal(len, (T)7.0))
			return 0;
	}
	else if (vTestCode.find(".Vec2.emptyAND") != std::string::npos)
	{
		v = ct::vec2<T>((T)0.0, (T)2.0);
		bool vb = v.emptyAND();
		if (!vb)
			return 0;
	}
	else if (vTestCode.find(".Vec2.emptyOR") != std::string::npos)
	{
		v = ct::vec2<T>((T)0.0, (T)2.0);
		bool vb = v.emptyOR();
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec2.string") != std::string::npos)
	{
		v = ct::vec2<T>((T)5.0, (T)2.0);
		const auto& str = v.string();
		const auto& str_coma = v.string(',');
		if (str == "5;2" &&
			str_coma == "5,2")
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

///////////////////////////////////////////////////////////
/// VEC3 //////////////////////////////////////////////////
///////////////////////////////////////////////////////////

// ok for double or float
template <typename T>
int Test_cTools_Vec3_run_test(const std::string& vTestCode)
{
	ct::vec3<T> v((T)5.0, (T)2.0, (T)6.5);

	if (vTestCode.find(".Vec3.[]") != std::string::npos)
	{
		if (is_equal(v[0], (T)5.0) &&
			is_equal(v[1], (T)2.0) &&
			is_equal(v[2], (T)6.5))
			return 0;
	}
	else if (vTestCode.find(".Vec3.Offset") != std::string::npos)
	{
		v = v.Offset((T)1.0, (T)2.0, (T)3.0);
		if (is_equal(v.x, (T)6.0) &&
			is_equal(v.y, (T)4.0) &&
			is_equal(v.z, (T)9.5))
			return 0;
	}
	else if (vTestCode.find(".Vec3.Set") != std::string::npos)
	{
		v.Set((T)1.0, (T)2.0, (T)3.0);
		if (is_equal(v.x, (T)1.0) &&
			is_equal(v.y, (T)2.0) &&
			is_equal(v.z, (T)3.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.-") != std::string::npos)
	{
		v = -v;
		if (is_equal(v.x, (T)-5.0) &&
			is_equal(v.y, (T)-2.0) &&
			is_equal(v.z, (T)-6.5))
			return 0;
	}
	else if (vTestCode.find(".Vec3.xy") != std::string::npos)
	{
		const auto& v2 = v.xy();
		if (is_equal(v2.x, (T)5.0) &&
			is_equal(v2.y, (T)2.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.xz") != std::string::npos)
	{
		const auto& v2 = v.xz();
		if (is_equal(v2.x, (T)5.0) &&
			is_equal(v2.y, (T)6.5))
			return 0;
	}
	else if (vTestCode.find(".Vec3.yz") != std::string::npos)
	{
		const auto& v2 = v.yz();
		if (is_equal(v2.x, (T)2.0) &&
			is_equal(v2.y, (T)6.5))
			return 0;
	}
	else if (vTestCode.find(".Vec3.yzx") != std::string::npos)
	{
		const auto& v3 = v.yzx();
		if (is_equal(v3.x, (T)2.0) &&
			is_equal(v3.y, (T)6.5) &&
			is_equal(v3.z, (T)5.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.post++") != std::string::npos)
	{
		const auto& vc = v++;
		if (is_equal(vc.x, (T)5.0) &&
			is_equal(vc.y, (T)2.0) &&
			is_equal(vc.z, (T)6.5) &&
			is_equal(v.x, (T)6.0) &&
			is_equal(v.y, (T)3.0) &&
			is_equal(v.z, (T)7.5))
			return 0;
	}
	else if (vTestCode.find(".Vec3.post--") != std::string::npos)
	{
		const auto& vc = v--;
		if (is_equal(vc.x, (T)5.0) &&
			is_equal(vc.y, (T)2.0) &&
			is_equal(vc.z, (T)6.5) &&
			is_equal(v.x, (T)4.0) &&
			is_equal(v.y, (T)1.0) &&
			is_equal(v.z, (T)5.5))
			return 0;
	}
	else if (vTestCode.find(".Vec3.pre++") != std::string::npos)
	{
		const auto& vc = ++v;
		if (is_equal(vc.x, (T)6.0) &&
			is_equal(vc.y, (T)3.0) &&
			is_equal(vc.z, (T)7.5) &&
			is_equal(v.x, (T)6.0) &&
			is_equal(v.y, (T)3.0) &&
			is_equal(v.z, (T)7.5))
			return 0;
	}
	else if (vTestCode.find(".Vec3.pre--") != std::string::npos)
	{
		const auto& vc = --v;
		if (is_equal(vc.x, (T)4.0) &&
			is_equal(vc.y, (T)1.0) &&
			is_equal(vc.z, (T)5.5) &&
			is_equal(v.x, (T)4.0) &&
			is_equal(v.y, (T)1.0) &&
			is_equal(v.z, (T)5.5))
			return 0;
	}
	else if (vTestCode.find(".Vec3.+=a") != std::string::npos)
	{
		v += (T)2.5f;
		if (is_equal(v.x, (T)7.5) &&
			is_equal(v.y, (T)4.5) &&
			is_equal(v.z, (T)9.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.+=Vec3") != std::string::npos)
	{
		v += ct::vec3<T>((T)2.0, (T)4.0, (T)2.0);
		if (is_equal(v.x, (T)7.0) &&
			is_equal(v.y, (T)6.0) &&
			is_equal(v.z, (T)8.5))
			return 0;
	}
	else if (vTestCode.find(".Vec3.-=a") != std::string::npos)
	{
		v -= (T)2.5;
		if (is_equal(v.x, (T)2.5) &&
			is_equal(v.y, (T)-0.5) &&
			is_equal(v.z, (T)4.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.-=Vec3") != std::string::npos)
	{
		v -= ct::vec3<T>((T)2.0, (T)4.0, (T)1.0);
		if (is_equal(v.x, (T)3.0) &&
			is_equal(v.y, (T)-2.0) &&
			is_equal(v.z, (T)5.5))
			return 0;
	}
	else if (vTestCode.find(".Vec3.==a") != std::string::npos)
	{
		v = (T)2.5;
		bool vb = (v == (T)2.5);
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec3.==Vec3") != std::string::npos)
	{
		bool vb = (v == ct::vec3<T>((T)5.0, (T)2.0, (T)6.5));
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec3.!=a") != std::string::npos)
	{
		v = (T)2.5;
		bool vb = (v != (T)5.0);
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec3.!=Vec3") != std::string::npos)
	{
		bool vb =
			(v != ct::vec3<T>((T)6.0, (T)2.0, (T)6.5)) &&
			(v != ct::vec3<T>((T)5.0, (T)3.0, (T)6.5)) &&
			(v != ct::vec3<T>((T)6.0, (T)3.0, (T)6.5)) &&
			(v != ct::vec3<T>((T)2.0, (T)1.0, (T)6.5));
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec3.*=a") != std::string::npos)
	{
		v *= (T)2.0;
		if (is_equal(v.x, (T)10.0) &&
			is_equal(v.y, (T)4.0) &&
			is_equal(v.z, (T)13.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.*=Vec3") != std::string::npos)
	{
		v *= ct::vec3<T>((T)2.0, (T)4.0, (T)2.0);
		if (is_equal(v.x, (T)10.0) &&
			is_equal(v.y, (T)8.0) &&
			is_equal(v.z, (T)13.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3./=a") != std::string::npos)
	{
		v /= (T)2.0;
		if (is_equal(v.x, (T)2.5) &&
			is_equal(v.y, (T)1.0) &&
			is_equal(v.z, (T)3.25))
			return 0;
	}
	else if (vTestCode.find(".Vec3./=Vec3") != std::string::npos)
	{
		v /= ct::vec3<T>((T)2.0, (T)4.0, (T)2.0);
		if (is_equal(v.x, (T)2.5) &&
			is_equal(v.y, (T)0.5) &&
			is_equal(v.z, (T)3.25))
			return 0;
	}
	else if (vTestCode.find(".Vec3.lengthSquared") != std::string::npos)
	{
		T len = v.lengthSquared();
		if (is_equal(len, (T)71.25))
			return 0;
	}
	else if (vTestCode.find(".Vec3.length") != std::string::npos)
	{
		T len = v.length();
		if (is_equal(len, (T)8.4409715080670660915584447047611))
			return 0;
	}
	else if (vTestCode.find(".Vec3.normalize") != std::string::npos)
	{
		T pre_len = v.length();
		v.normalize();
		T post_len = v.length();
		if ((!is_equal(pre_len, (T)1.0)) &&
			is_equal(post_len, (T)1.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.GetNormalized") != std::string::npos)
	{
		const auto& vn = v.GetNormalized();
		T len = vn.length();
		if (is_equal(len, (T)1.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.sum") != std::string::npos)
	{
		v = ct::vec3<T>((T)5.0, (T)-2.0, (T)3.0);
		T len = v.sum();
		if (is_equal(len, (T)6.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.sumAbs") != std::string::npos)
	{
		v = ct::vec3<T>((T)5.0, (T)-2.0, (T)3.0);
		T len = v.sumAbs();
		if (is_equal(len, (T)10.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.emptyAND") != std::string::npos)
	{
		v = ct::vec3<T>((T)0.0, (T)-2.0, (T)3.0);
		bool vb = v.emptyAND();
		if (!vb)
			return 0;
	}
	else if (vTestCode.find(".Vec3.emptyOR") != std::string::npos)
	{
		v = ct::vec3<T>((T)3.0, (T)-2.0, (T)0.0);
		bool vb = v.emptyOR();
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec3.string") != std::string::npos)
	{
		v = ct::vec3<T>((T)5.35, (T)-2.8, (T)3.8);
		const auto& str = v.string();
		const auto& str_coma = v.string(',');
		if (str == "5.35;-2.8;3.8" &&
			str_coma == "5.35,-2.8,3.8")
			return 0;
	}
	else if (vTestCode.find(".Vec3.mini") != std::string::npos)
	{
		T mini = v.mini();
		if (is_equal(mini, (T)2.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.maxi") != std::string::npos)
	{
		T maxi = v.maxi();
		if (is_equal(maxi, (T)6.5))
			return 0;
	}

	return 1; // error
}

// specialisation for bool
template <>
int Test_cTools_Vec3_run_test<bool>(const std::string& vTestCode)
{
	ct::bvec3 v(true, false, true);

	if (vTestCode.find(".Vec3.[]") != std::string::npos)
	{
		if (v[0] &&
			!v[1] &&
			v[2])
			return 0;
	}
	else if (vTestCode.find(".Vec3.Set") != std::string::npos)
	{
		v.Set(true, true, false);
		if (v.x &&
			v.y &&
			!v.z)
			return 0;
	}
	else if (vTestCode.find(".Vec3.!") != std::string::npos)
	{
		v = !v;
		if (!v.x &&
			v.y &&
			!v.z)
			return 0;
	}
	else if (vTestCode.find(".Vec3.xy") != std::string::npos)
	{
		const auto& v2 = v.xy();
		if (v2.x &&
			!v2.y)
			return 0;
	}
	else if (vTestCode.find(".Vec3.xz") != std::string::npos)
	{
		const auto& v2 = v.xz();
		if (v2.x &&
			v2.y)
			return 0;
	}
	else if (vTestCode.find(".Vec3.yz") != std::string::npos)
	{
		const auto& v2 = v.yz();
		if (!v2.x &&
			v2.y)
			return 0;
	}
	else if (vTestCode.find(".Vec3.yzx") != std::string::npos)
	{
		const auto& v3 = v.yzx();
		if (v3.x &&
			!v3.y &&
			v3.z)
			return 0;
	}
	else if (vTestCode.find(".Vec3.==a") != std::string::npos)
	{
		bool vb = (v==true);
		if (!vb)
			return 0;
	}
	else if (vTestCode.find(".Vec3.==Vec3") != std::string::npos)
	{
		bool vb = (v == ct::bvec3(true, false, true));
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec3.!=a") != std::string::npos)
	{
		if (v != true)
			return 0;
	}
	else if (vTestCode.find(".Vec3.!=Vec3") != std::string::npos)
	{
		if ((v != ct::bvec3(false, true, true)) &&
			(v != ct::bvec3(true, true, true)) &&
			(v != ct::bvec3(false, false, true)))
			return 0;
	}
	else if (vTestCode.find(".Vec3.emptyAND") != std::string::npos)
	{
		bool vb = v.emptyAND();
		if (!vb)
			return 0;
	}
	else if (vTestCode.find(".Vec3.emptyOR") != std::string::npos)
	{
		bool vb = v.emptyOR();
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec3.string") != std::string::npos)
	{
		const auto& str = v.string();
		const auto& str_coma = v.string(',');
		if (str == "1;0;1" &&
			str_coma == "1,0,1")
			return 0;
	}
	else if (vTestCode.find(".Vec3.mini") != std::string::npos)
	{
		bool mini = v.mini();
		if (!mini)
			return 0;
	}
	else if (vTestCode.find(".Vec3.maxi") != std::string::npos)
	{
		bool maxi = v.maxi();
		if (maxi)
			return 0;
	}

	return 1; // error
}

// specialisation for signed integer
template <typename T>
int Test_cTools_signed_integer_Vec3_run_test(const std::string& vTestCode)
{
	ct::vec3<T> v((T)5.0, (T)2.0, (T)6.0);

	if (vTestCode.find(".Vec3.[]") != std::string::npos)
	{
		if (is_equal(v[0], (T)5.0) &&
			is_equal(v[1], (T)2.0) &&
			is_equal(v[2], (T)6.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.Offset") != std::string::npos)
	{
		v = v.Offset((T)1.0, (T)2.0, (T)3.0);
		if (is_equal(v.x, (T)6.0) &&
			is_equal(v.y, (T)4.0) &&
			is_equal(v.z, (T)9.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.Set") != std::string::npos)
	{
		v.Set((T)1.0, (T)2.0, (T)3.0);
		if (is_equal(v.x, (T)1.0) &&
			is_equal(v.y, (T)2.0) &&
			is_equal(v.z, (T)3.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.-") != std::string::npos)
	{
		v = -v;
		if (is_equal(v.x, (T)-5.0) &&
			is_equal(v.y, (T)-2.0) &&
			is_equal(v.z, (T)-6.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.xy") != std::string::npos)
	{
		const auto& v2 = v.xy();
		if (is_equal(v2.x, (T)5.0) &&
			is_equal(v2.y, (T)2.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.xz") != std::string::npos)
	{
		const auto& v2 = v.xz();
		if (is_equal(v2.x, (T)5.0) &&
			is_equal(v2.y, (T)6.5))
			return 0;
	}
	else if (vTestCode.find(".Vec3.yz") != std::string::npos)
	{
		const auto& v2 = v.yz();
		if (is_equal(v2.x, (T)2.0) &&
			is_equal(v2.y, (T)6.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.yzx") != std::string::npos)
	{
		const auto& v3 = v.yzx();
		if (is_equal(v3.x, (T)2.0) &&
			is_equal(v3.y, (T)6.0) &&
			is_equal(v3.z, (T)5.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.post++") != std::string::npos)
	{
		const auto& vc = v++;
		if (is_equal(vc.x, (T)5.0) &&
			is_equal(vc.y, (T)2.0) &&
			is_equal(vc.z, (T)6.0) &&
			is_equal(v.x, (T)6.0) &&
			is_equal(v.y, (T)3.0) &&
			is_equal(v.z, (T)7.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.post--") != std::string::npos)
	{
		const auto& vc = v--;
		if (is_equal(vc.x, (T)5.0) &&
			is_equal(vc.y, (T)2.0) &&
			is_equal(vc.z, (T)6.0) &&
			is_equal(v.x, (T)4.0) &&
			is_equal(v.y, (T)1.0) &&
			is_equal(v.z, (T)5.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.pre++") != std::string::npos)
	{
		const auto& vc = ++v;
		if (is_equal(vc.x, (T)6.0) &&
			is_equal(vc.y, (T)3.0) &&
			is_equal(vc.z, (T)7.0) &&
			is_equal(v.x, (T)6.0) &&
			is_equal(v.y, (T)3.0) &&
			is_equal(v.z, (T)7.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.pre--") != std::string::npos)
	{
		const auto& vc = --v;
		if (is_equal(vc.x, (T)4.0) &&
			is_equal(vc.y, (T)1.0) &&
			is_equal(vc.z, (T)5.0) &&
			is_equal(v.x, (T)4.0) &&
			is_equal(v.y, (T)1.0) &&
			is_equal(v.z, (T)5.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.+=a") != std::string::npos)
	{
		v += (T)2.0f;
		if (is_equal(v.x, (T)7.0) &&
			is_equal(v.y, (T)4.0) &&
			is_equal(v.z, (T)8.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.+=Vec3") != std::string::npos)
	{
		v += ct::vec3<T>((T)2.0, (T)4.0, (T)2.0);
		if (is_equal(v.x, (T)7.0) &&
			is_equal(v.y, (T)6.0) &&
			is_equal(v.z, (T)8.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.-=a") != std::string::npos)
	{
		v -= (T)2.0;
		if (is_equal(v.x, (T)2.0) &&
			is_equal(v.y, (T)0.0) &&
			is_equal(v.z, (T)4.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.-=Vec3") != std::string::npos)
	{
		v -= ct::vec3<T>((T)2.0, (T)4.0, (T)1.0);
		if (is_equal(v.x, (T)3.0) &&
			is_equal(v.y, (T)-2.0) &&
			is_equal(v.z, (T)5.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.==a") != std::string::npos)
	{
		v = (T)2.0;
		bool vb = (v == (T)2.0);
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec3.==Vec3") != std::string::npos)
	{
		bool vb = (v == ct::vec3<T>((T)5.0, (T)2.0, (T)6.0));
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec3.!=a") != std::string::npos)
	{
		v = (T)2.5;
		bool vb = (v != (T)5.0);
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec3.!=Vec3") != std::string::npos)
	{
		bool vb =
			(v != ct::vec3<T>((T)6.0, (T)2.0, (T)6.0)) &&
			(v != ct::vec3<T>((T)5.0, (T)3.0, (T)6.0)) &&
			(v != ct::vec3<T>((T)6.0, (T)3.0, (T)6.0)) &&
			(v != ct::vec3<T>((T)2.0, (T)1.0, (T)6.0));
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec3.*=a") != std::string::npos)
	{
		v *= (T)2.0;
		if (is_equal(v.x, (T)10.0) &&
			is_equal(v.y, (T)4.0) &&
			is_equal(v.z, (T)12.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.*=Vec3") != std::string::npos)
	{
		v *= ct::vec3<T>((T)2.0, (T)4.0, (T)2.0);
		if (is_equal(v.x, (T)10.0) &&
			is_equal(v.y, (T)8.0) &&
			is_equal(v.z, (T)12.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3./=a") != std::string::npos)
	{
		v /= (T)2.0;
		if (is_equal(v.x, (T)2.0) &&
			is_equal(v.y, (T)1.0) &&
			is_equal(v.z, (T)3.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3./=Vec3") != std::string::npos)
	{
		v /= ct::vec3<T>((T)2.0, (T)4.0, (T)2.0);
		if (is_equal(v.x, (T)2.0) &&
			is_equal(v.y, (T)0.0) &&
			is_equal(v.z, (T)3.0))
			return 0;
	}
	/*
	else if (vTestCode.find(".Vec3.lengthSquared") != std::string::npos)
	{
		T len = v.lengthSquared();
		if (is_equal(len, (T)71.25))
			return 0;
	}
	else if (vTestCode.find(".Vec3.length") != std::string::npos)
	{
		T len = v.length();
		if (is_equal(len, (T)8.4409715080670660915584447047611))
			return 0;
	}
	else if (vTestCode.find(".Vec3.normalize") != std::string::npos)
	{
		T pre_len = v.length();
		v.normalize();
		T post_len = v.length();
		if ((!is_equal(pre_len, (T)1.0)) &&
			is_equal(post_len, (T)1.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.GetNormalized") != std::string::npos)
	{
		const auto& vn = v.GetNormalized();
		T len = vn.length();
		if (is_equal(len, (T)1.0))
			return 0;
	}
	*/
	else if (vTestCode.find(".Vec3.sum") != std::string::npos)
	{
		v = ct::vec3<T>((T)5.0, (T)-2.0, (T)3.0);
		T len = v.sum();
		if (is_equal(len, (T)6.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.sumAbs") != std::string::npos)
	{
		v = ct::vec3<T>((T)5.0, (T)-2.0, (T)3.0);
		T len = v.sumAbs();
		if (is_equal(len, (T)10.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.emptyAND") != std::string::npos)
	{
		v = ct::vec3<T>((T)0.0, (T)-2.0, (T)3.0);
		bool vb = v.emptyAND();
		if (!vb)
			return 0;
	}
	else if (vTestCode.find(".Vec3.emptyOR") != std::string::npos)
	{
		v = ct::vec3<T>((T)3.0, (T)-2.0, (T)0.0);
		bool vb = v.emptyOR();
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec3.string") != std::string::npos)
	{
		v = ct::vec3<T>((T)5.0, (T)-2.0, (T)3.0);
		const auto& str = v.string();
		const auto& str_coma = v.string(',');
		if (str == "5;-2;3" &&
			str_coma == "5,-2,3")
			return 0;
	}
	else if (vTestCode.find(".Vec3.mini") != std::string::npos)
	{
		T mini = v.mini();
		if (is_equal(mini, (T)2.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.maxi") != std::string::npos)
	{
		T maxi = v.maxi();
		if (is_equal(maxi, (T)6.0))
			return 0;
	}

	return 1; // error
}

// specialisation unsigned intergers
template <typename T>
int Test_cTools_unsigned_integer_Vec3_run_test(const std::string& vTestCode)
{
	ct::vec3<T> v((T)5.0, (T)2.0, (T)6.0);

	if (vTestCode.find(".Vec3.[]") != std::string::npos)
	{
		if (is_equal(v[0], (T)5.0) &&
			is_equal(v[1], (T)2.0) &&
			is_equal(v[2], (T)6.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.Offset") != std::string::npos)
	{
		v = v.Offset((T)1.0, (T)2.0, (T)3.0);
		if (is_equal(v.x, (T)6.0) &&
			is_equal(v.y, (T)4.0) &&
			is_equal(v.z, (T)9.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.Set") != std::string::npos)
	{
		v.Set((T)1.0, (T)2.0, (T)3.0);
		if (is_equal(v.x, (T)1.0) &&
			is_equal(v.y, (T)2.0) &&
			is_equal(v.z, (T)3.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.xy") != std::string::npos)
	{
		const auto& v2 = v.xy();
		if (is_equal(v2.x, (T)5.0) &&
			is_equal(v2.y, (T)2.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.xz") != std::string::npos)
	{
		const auto& v2 = v.xz();
		if (is_equal(v2.x, (T)5.0) &&
			is_equal(v2.y, (T)6.5))
			return 0;
	}
	else if (vTestCode.find(".Vec3.yz") != std::string::npos)
	{
		const auto& v2 = v.yz();
		if (is_equal(v2.x, (T)2.0) &&
			is_equal(v2.y, (T)6.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.yzx") != std::string::npos)
	{
		const auto& v3 = v.yzx();
		if (is_equal(v3.x, (T)2.0) &&
			is_equal(v3.y, (T)6.0) &&
			is_equal(v3.z, (T)5.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.post++") != std::string::npos)
	{
		const auto& vc = v++;
		if (is_equal(vc.x, (T)5.0) &&
			is_equal(vc.y, (T)2.0) &&
			is_equal(vc.z, (T)6.0) &&
			is_equal(v.x, (T)6.0) &&
			is_equal(v.y, (T)3.0) &&
			is_equal(v.z, (T)7.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.post--") != std::string::npos)
	{
		const auto& vc = v--;
		if (is_equal(vc.x, (T)5.0) &&
			is_equal(vc.y, (T)2.0) &&
			is_equal(vc.z, (T)6.0) &&
			is_equal(v.x, (T)4.0) &&
			is_equal(v.y, (T)1.0) &&
			is_equal(v.z, (T)5.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.pre++") != std::string::npos)
	{
		const auto& vc = ++v;
		if (is_equal(vc.x, (T)6.0) &&
			is_equal(vc.y, (T)3.0) &&
			is_equal(vc.z, (T)7.0) &&
			is_equal(v.x, (T)6.0) &&
			is_equal(v.y, (T)3.0) &&
			is_equal(v.z, (T)7.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.pre--") != std::string::npos)
	{
		const auto& vc = --v;
		if (is_equal(vc.x, (T)4.0) &&
			is_equal(vc.y, (T)1.0) &&
			is_equal(vc.z, (T)5.0) &&
			is_equal(v.x, (T)4.0) &&
			is_equal(v.y, (T)1.0) &&
			is_equal(v.z, (T)5.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.+=a") != std::string::npos)
	{
		v += (T)2.0f;
		if (is_equal(v.x, (T)7.0) &&
			is_equal(v.y, (T)4.0) &&
			is_equal(v.z, (T)8.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.+=Vec3") != std::string::npos)
	{
		v += ct::vec3<T>((T)2.0, (T)4.0, (T)2.0);
		if (is_equal(v.x, (T)7.0) &&
			is_equal(v.y, (T)6.0) &&
			is_equal(v.z, (T)8.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.-=a") != std::string::npos)
	{
		v -= (T)2.0;
		if (is_equal(v.x, (T)3.0) &&
			is_equal(v.y, (T)0.0) &&
			is_equal(v.z, (T)4.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.-=Vec3") != std::string::npos)
	{
		v -= ct::vec3<T>((T)2.0, (T)2.0, (T)1.0);
		if (is_equal(v.x, (T)3.0) &&
			is_equal(v.y, (T)0.0) &&
			is_equal(v.z, (T)5.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.==a") != std::string::npos)
	{
		v = (T)2.0;
		bool vb = (v == (T)2.0);
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec3.==Vec3") != std::string::npos)
	{
		bool vb = (v == ct::vec3<T>((T)5.0, (T)2.0, (T)6.0));
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec3.!=a") != std::string::npos)
	{
		v = (T)2.5;
		bool vb = (v != (T)5.0);
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec3.!=Vec3") != std::string::npos)
	{
		bool vb =
			(v != ct::vec3<T>((T)6.0, (T)2.0, (T)6.0)) &&
			(v != ct::vec3<T>((T)5.0, (T)3.0, (T)6.0)) &&
			(v != ct::vec3<T>((T)6.0, (T)3.0, (T)6.0)) &&
			(v != ct::vec3<T>((T)2.0, (T)1.0, (T)6.0));
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec3.*=a") != std::string::npos)
	{
		v *= (T)2.0;
		if (is_equal(v.x, (T)10.0) &&
			is_equal(v.y, (T)4.0) &&
			is_equal(v.z, (T)12.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.*=Vec3") != std::string::npos)
	{
		v *= ct::vec3<T>((T)2.0, (T)4.0, (T)2.0);
		if (is_equal(v.x, (T)10.0) &&
			is_equal(v.y, (T)8.0) &&
			is_equal(v.z, (T)12.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3./=a") != std::string::npos)
	{
		v /= (T)2.0;
		if (is_equal(v.x, (T)2.0) &&
			is_equal(v.y, (T)1.0) &&
			is_equal(v.z, (T)3.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3./=Vec3") != std::string::npos)
	{
		v /= ct::vec3<T>((T)2.0, (T)4.0, (T)2.0);
		if (is_equal(v.x, (T)2.0) &&
			is_equal(v.y, (T)0.0) &&
			is_equal(v.z, (T)3.0))
			return 0;
	}
	/*
	else if (vTestCode.find(".Vec3.lengthSquared") != std::string::npos)
	{
		T len = v.lengthSquared();
		if (is_equal(len, (T)71.25))
			return 0;
	}
	else if (vTestCode.find(".Vec3.length") != std::string::npos)
	{
		T len = v.length();
		if (is_equal(len, (T)8.4409715080670660915584447047611))
			return 0;
	}
	else if (vTestCode.find(".Vec3.normalize") != std::string::npos)
	{
		T pre_len = v.length();
		v.normalize();
		T post_len = v.length();
		if ((!is_equal(pre_len, (T)1.0)) &&
			is_equal(post_len, (T)1.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.GetNormalized") != std::string::npos)
	{
		const auto& vn = v.GetNormalized();
		T len = vn.length();
		if (is_equal(len, (T)1.0))
			return 0;
	}
	*/
	else if (vTestCode.find(".Vec3.sum") != std::string::npos)
	{
		v = ct::vec3<T>((T)5.0, (T)2.0, (T)3.0);
		T len = v.sum();
		if (is_equal(len, (T)10.0))
			return 0;
	}
	/*
	else if (vTestCode.find(".Vec3.sumAbs") != std::string::npos)
	{
		v = ct::vec3<T>((T)5.0, (T)-2.0, (T)3.0);
		T len = v.sumAbs();
		if (is_equal(len, (T)10.0))
			return 0;
	}
	*/
	else if (vTestCode.find(".Vec3.emptyAND") != std::string::npos)
	{
		v = ct::vec3<T>((T)0.0, (T)-2.0, (T)3.0);
		bool vb = v.emptyAND();
		if (!vb)
			return 0;
	}
	else if (vTestCode.find(".Vec3.emptyOR") != std::string::npos)
	{
		v = ct::vec3<T>((T)3.0, (T)-2.0, (T)0.0);
		bool vb = v.emptyOR();
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec3.string") != std::string::npos)
	{
		v = ct::vec3<T>((T)5.0, (T)2.0, (T)3.0);
		const auto& str = v.string();
		const auto& str_coma = v.string(',');
		if (str == "5;2;3" &&
			str_coma == "5,2,3")
			return 0;
	}
	else if (vTestCode.find(".Vec3.mini") != std::string::npos)
	{
		T mini = v.mini();
		if (is_equal(mini, (T)2.0))
			return 0;
	}
	else if (vTestCode.find(".Vec3.maxi") != std::string::npos)
	{
		T maxi = v.maxi();
		if (is_equal(maxi, (T)6.0))
			return 0;
	}

	return 1; // error
}

///////////////////////////////////////////////////////////
/// VEC4 //////////////////////////////////////////////////
///////////////////////////////////////////////////////////

// ok for double or float
template <typename T>
int Test_cTools_Vec4_run_test(const std::string& vTestCode)
{
	ct::vec4<T> v((T)5.0, (T)2.0, (T)4.5, (T)6.5);

	if (vTestCode.find(".Vec4.[]") != std::string::npos)
	{
		if (is_equal(v[0], (T)5.0) &&
			is_equal(v[1], (T)2.0) &&
			is_equal(v[2], (T)4.5) &&
			is_equal(v[3], (T)6.5))
			return 0;
	}
	else if (vTestCode.find(".Vec4.Offset") != std::string::npos)
	{
		v = v.Offset((T)1.0, (T)2.0, (T)3.0, (T)2.0);
		if (is_equal(v.x, (T)6.0) &&
			is_equal(v.y, (T)4.0) &&
			is_equal(v.z, (T)7.5) &&
			is_equal(v.w, (T)8.5))
			return 0;
	}
	else if (vTestCode.find(".Vec4.Set") != std::string::npos)
	{
		v.Set((T)1.0, (T)2.0, (T)3.0, (T)2.0);
		if (is_equal(v.x, (T)1.0) &&
			is_equal(v.y, (T)2.0) &&
			is_equal(v.z, (T)3.0) &&
			is_equal(v.w, (T)2.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.-") != std::string::npos)
	{
		v = -v;
		if (is_equal(v.x, (T)-5.0) &&
			is_equal(v.y, (T)-2.0) &&
			is_equal(v.z, (T)-4.5) &&
			is_equal(v.w, (T)-6.5))
			return 0;
	}
	else if (vTestCode.find(".Vec4.xy") != std::string::npos)
	{
		const auto& v2 = v.xy();
		if (is_equal(v2.x, (T)5.0) &&
			is_equal(v2.y, (T)2.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.xyz") != std::string::npos)
	{
		const auto& v3 = v.xyz();
		if (is_equal(v3.x, (T)5.0) &&
			is_equal(v3.y, (T)2.0) &&
			is_equal(v3.z, (T)4.5))
			return 0;
	}
	else if (vTestCode.find(".Vec4.zw") != std::string::npos)
	{
		const auto& v2 = v.zw();
		if (is_equal(v2.x, (T)4.5) &&
			is_equal(v2.y, (T)6.5))
			return 0;
	}
	else if (vTestCode.find(".Vec4.SizeLBRT") != std::string::npos)
	{
		const auto& v2 = v.SizeLBRT();
		if (is_equal(v2.x, (T)-0.5) &&
			is_equal(v2.y, (T)4.5))
			return 0;
	}
	else if (vTestCode.find(".Vec4.pos") != std::string::npos)
	{
		const auto& v2 = v.pos();
		if (is_equal(v2.x, (T)5.0) &&
			is_equal(v2.y, (T)2.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.size") != std::string::npos)
	{
		const auto& v2 = v.size();
		if (is_equal(v2.x, (T)4.5) &&
			is_equal(v2.y, (T)6.5))
			return 0;
	}
	else if (vTestCode.find(".Vec4.post++") != std::string::npos)
	{
		const auto& vc = v++;
		if (is_equal(vc.x, (T)5.0) &&
			is_equal(vc.y, (T)2.0) &&
			is_equal(vc.z, (T)4.5) &&
			is_equal(vc.w, (T)6.5) &&
			is_equal(v.x, (T)6.0) &&
			is_equal(v.y, (T)3.0) &&
			is_equal(v.z, (T)5.5) &&
			is_equal(v.w, (T)7.5))
			return 0;
	}
	else if (vTestCode.find(".Vec4.post--") != std::string::npos)
	{
		const auto& vc = v--;
		if (is_equal(vc.x, (T)5.0) &&
			is_equal(vc.y, (T)2.0) &&
			is_equal(vc.z, (T)4.5) &&
			is_equal(vc.w, (T)6.5) &&
			is_equal(v.x, (T)4.0) &&
			is_equal(v.y, (T)1.0) &&
			is_equal(v.z, (T)3.5) &&
			is_equal(v.w, (T)5.5))
			return 0;
	}
	else if (vTestCode.find(".Vec4.pre++") != std::string::npos)
	{
		const auto& vc = ++v;
		if (is_equal(vc.x, (T)6.0) &&
			is_equal(vc.y, (T)3.0) &&
			is_equal(vc.z, (T)5.5) &&
			is_equal(vc.w, (T)7.5) &&
			is_equal(v.x, (T)6.0) &&
			is_equal(v.y, (T)3.0) &&
			is_equal(v.z, (T)5.5) &&
			is_equal(v.w, (T)7.5))
			return 0;
	}
	else if (vTestCode.find(".Vec4.pre--") != std::string::npos)
	{
		const auto& vc = --v;
		if (is_equal(vc.x, (T)4.0) &&
			is_equal(vc.y, (T)1.0) &&
			is_equal(vc.z, (T)3.5) &&
			is_equal(vc.w, (T)5.5) &&
			is_equal(v.x, (T)4.0) &&
			is_equal(v.y, (T)1.0) &&
			is_equal(v.z, (T)3.5) &&
			is_equal(v.w, (T)5.5))
			return 0;
	}
	else if (vTestCode.find(".Vec4.+=a") != std::string::npos)
	{
		v += (T)2.5f;
		if (is_equal(v.x, (T)7.5) &&
			is_equal(v.y, (T)4.5) &&
			is_equal(v.z, (T)7.0) &&
			is_equal(v.w, (T)9.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.+=Vec4") != std::string::npos)
	{
		v += ct::vec4<T>((T)2.0, (T)4.0, (T)2.0, (T)4.0);
		if (is_equal(v.x, (T)7.0) &&
			is_equal(v.y, (T)6.0) &&
			is_equal(v.z, (T)6.5) &&
			is_equal(v.w, (T)10.5))
			return 0;
	}
	else if (vTestCode.find(".Vec4.-=a") != std::string::npos)
	{
		v -= (T)2.5;
		if (is_equal(v.x, (T)2.5) &&
			is_equal(v.y, (T)-0.5) &&
			is_equal(v.z, (T)4.0) &&
			is_equal(v.w, (T)4.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.-=Vec4") != std::string::npos)
	{
		v -= ct::vec4<T>((T)2.0, (T)4.0, (T)1.0, (T)2.0);
		if (is_equal(v.x, (T)3.0) &&
			is_equal(v.y, (T)-2.0) &&
			is_equal(v.z, (T)5.5) &&
			is_equal(v.w, (T)5.5))
			return 0;
	}
	else if (vTestCode.find(".Vec4.==a") != std::string::npos)
	{
		v = (T)2.5;
		bool vb = (v == (T)2.5);
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec4.==Vec4") != std::string::npos)
	{
		bool vb = (v == ct::vec4<T>((T)5.0, (T)2.0, (T)4.5, (T)6.5));
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec4.!=a") != std::string::npos)
	{
		v = (T)2.5;
		bool vb = (v != (T)5.0);
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec4.!=Vec4") != std::string::npos)
	{
		bool vb =
			(v != ct::vec4<T>((T)6.0, (T)2.0, (T)6.5, (T)2.5)) &&
			(v != ct::vec4<T>((T)5.0, (T)3.0, (T)6.5, (T)2.5)) &&
			(v != ct::vec4<T>((T)6.0, (T)3.0, (T)6.5, (T)2.5)) &&
			(v != ct::vec4<T>((T)2.0, (T)1.0, (T)6.5, (T)2.5));
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec4.*=a") != std::string::npos)
	{
		v *= (T)2.0;
		if (is_equal(v.x, (T)10.0) &&
			is_equal(v.y, (T)4.0) &&
			is_equal(v.z, (T)9.0) &&
			is_equal(v.w, (T)13.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.*=Vec4") != std::string::npos)
	{
		v *= ct::vec4<T>((T)2.0, (T)4.0, (T)2.0, (T)3.0);
		if (is_equal(v.x, (T)10.0) &&
			is_equal(v.y, (T)8.0) &&
			is_equal(v.z, (T)9.0) &&
			is_equal(v.w, (T)19.5))
			return 0;
	}
	else if (vTestCode.find(".Vec4./=a") != std::string::npos)
	{
		v /= (T)2.0;
		if (is_equal(v.x, (T)2.5) &&
			is_equal(v.y, (T)1.0) &&
			is_equal(v.z, (T)2.25) &&
			is_equal(v.w, (T)3.25))
			return 0;
	}
	else if (vTestCode.find(".Vec4./=Vec4") != std::string::npos)
	{
		v /= ct::vec4<T>((T)2.0, (T)4.0, (T)2.0, (T)2.0);
		if (is_equal(v.x, (T)2.5) &&
			is_equal(v.y, (T)0.5) &&
			is_equal(v.z, (T)2.25) &&
			is_equal(v.w, (T)3.25))
			return 0;
	}
	else if (vTestCode.find(".Vec4.lengthSquared") != std::string::npos)
	{
		T len = v.lengthSquared();
		if (is_equal(len, (T)91.5))
			return 0;
	}
	else if (vTestCode.find(".Vec4.length") != std::string::npos)
	{
		T len = v.length();
		if (is_equal(len, (T)9.5655632348544954877912543765086))
			return 0;
	}
	else if (vTestCode.find(".Vec4.normalize") != std::string::npos)
	{
		T pre_len = v.length();
		v.normalize();
		T post_len = v.length();
		if ((!is_equal(pre_len, (T)1.0)) &&
			is_equal(post_len, (T)1.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.GetNormalized") != std::string::npos)
	{
		const auto& vn = v.GetNormalized();
		T len = vn.length();
		if (is_equal(len, (T)1.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.sum") != std::string::npos)
	{
		v = ct::vec4<T>((T)5.0, (T)-2.0, (T)3.0, (T)5.0);
		T len = v.sum();
		if (is_equal(len, (T)11.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.sumAbs") != std::string::npos)
	{
		v = ct::vec4<T>((T)5.0, (T)-2.0, (T)3.0, (T)5.0);
		T len = v.sumAbs();
		if (is_equal(len, (T)15.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.emptyAND") != std::string::npos)
	{
		v = ct::vec4<T>((T)5.0, (T)-2.0, (T)3.0, (T)0.0);
		bool vb = v.emptyAND();
		if (!vb)
			return 0;
	}
	else if (vTestCode.find(".Vec4.emptyOR") != std::string::npos)
	{
		v = ct::vec4<T>((T)3.0, (T)-2.0, (T)5.0, (T)0.0);
		bool vb = v.emptyOR();
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec4.string") != std::string::npos)
	{
		v = ct::vec4<T>((T)5.35, (T)-2.8, (T)3.8, (T)2.9);
		const auto& str = v.string();
		const auto& str_coma = v.string(',');
		if (str == "5.35;-2.8;3.8;2.9" &&
			str_coma == "5.35,-2.8,3.8,2.9")
			return 0;
	}
	else if (vTestCode.find(".Vec4.mini") != std::string::npos)
	{
		T mini = v.mini();
		if (is_equal(mini, (T)2.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.maxi") != std::string::npos)
	{
		T maxi = v.maxi();
		if (is_equal(maxi, (T)6.5))
			return 0;
	}

	return 1; // error
}

// specialisation for bool
template <>
int Test_cTools_Vec4_run_test<bool>(const std::string& vTestCode)
{
	ct::bvec4 v(true, false, true, false);

	if (vTestCode.find(".Vec4.[]") != std::string::npos)
	{
		if (v[0] &&
			!v[1] &&
			v[2] &&
			!v[3])
			return 0;
	}
	else if (vTestCode.find(".Vec4.Set") != std::string::npos)
	{
		v.Set(true, true, false, true);
		if (v.x &&
			v.y &&
			!v.z &&
			v.w)
			return 0;
	}
	else if (vTestCode.find(".Vec4.!") != std::string::npos)
	{
		v = !v;
		if (!v.x &&
			v.y &&
			!v.z &&
			v.w)
			return 0;
	}
	else if (vTestCode.find(".Vec4.xy") != std::string::npos)
	{
		const auto& v2 = v.xy();
		if (v2.x &&
			!v2.y)
			return 0;
	}
	else if (vTestCode.find(".Vec4.xyz") != std::string::npos)
	{
		const auto& v3 = v.xyz();
		if (v3.x &&
			!v3.y &&
			v3.z)
			return 0;
	}
	else if (vTestCode.find(".Vec4.zw") != std::string::npos)
	{
		const auto& v2 = v.zw();
		if (v2.x &&
			!v2.y)
			return 0;
	}
	else if (vTestCode.find(".Vec4.==a") != std::string::npos)
	{
		bool vb = (v==true);
		if (!vb)
			return 0;
	}
	else if (vTestCode.find(".Vec4.==Vec4") != std::string::npos)
	{
		bool vb = (v == ct::bvec4(true, false, true, false));
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec4.!=a") != std::string::npos)
	{
		if (v != true)
			return 0;
	}
	else if (vTestCode.find(".Vec4.!=Vec4") != std::string::npos)
	{
		if ((v != ct::bvec4(false, true, true, false)) &&
			(v != ct::bvec4(true, true, true, false)) &&
			(v != ct::bvec4(false, false, true, false)))
			return 0;
	}
	else if (vTestCode.find(".Vec4.emptyAND") != std::string::npos)
	{
		bool vb = v.emptyAND();
		if (!vb)
			return 0;
	}
	else if (vTestCode.find(".Vec4.emptyOR") != std::string::npos)
	{
		bool vb = v.emptyOR();
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec4.string") != std::string::npos)
	{
		const auto& str = v.string();
		const auto& str_coma = v.string(',');
		if (str == "1;0;1;0" &&
			str_coma == "1,0,1,0")
			return 0;
	}
	else if (vTestCode.find(".Vec4.mini") != std::string::npos)
	{
		bool mini = v.mini();
		if (!mini)
			return 0;
	}
	else if (vTestCode.find(".Vec4.maxi") != std::string::npos)
	{
		bool maxi = v.maxi();
		if (maxi)
			return 0;
	}

	return 1; // error
}

// specialisation for signed integer
template <typename T>
int Test_cTools_signed_integer_Vec4_run_test(const std::string& vTestCode)
{
	ct::vec4<T> v((T)5.0, (T)2.0, (T)4.0, (T)6.0);

	if (vTestCode.find(".Vec4.[]") != std::string::npos)
	{
		if (is_equal(v[0], (T)5.0) &&
			is_equal(v[1], (T)2.0) &&
			is_equal(v[2], (T)4.0) &&
			is_equal(v[3], (T)6.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.Offset") != std::string::npos)
	{
		v = v.Offset((T)1.0, (T)2.0, (T)3.0, (T)2.0);
		if (is_equal(v.x, (T)6.0) &&
			is_equal(v.y, (T)4.0) &&
			is_equal(v.z, (T)7.0) &&
			is_equal(v.w, (T)8.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.Set") != std::string::npos)
	{
		v.Set((T)1.0, (T)2.0, (T)3.0, (T)2.0);
		if (is_equal(v.x, (T)1.0) &&
			is_equal(v.y, (T)2.0) &&
			is_equal(v.z, (T)3.0) &&
			is_equal(v.w, (T)2.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.-") != std::string::npos)
	{
		v = -v;
		if (is_equal(v.x, (T)-5.0) &&
			is_equal(v.y, (T)-2.0) &&
			is_equal(v.z, (T)-4.0) &&
			is_equal(v.w, (T)-6.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.xy") != std::string::npos)
	{
		const auto& v2 = v.xy();
		if (is_equal(v2.x, (T)5.0) &&
			is_equal(v2.y, (T)2.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.xyz") != std::string::npos)
	{
		const auto& v3 = v.xyz();
		if (is_equal(v3.x, (T)5.0) &&
			is_equal(v3.y, (T)2.0) &&
			is_equal(v3.z, (T)4.5))
			return 0;
	}
	else if (vTestCode.find(".Vec4.zw") != std::string::npos)
	{
		const auto& v2 = v.zw();
		if (is_equal(v2.x, (T)4.5) &&
			is_equal(v2.y, (T)6.5))
			return 0;
	}
	else if (vTestCode.find(".Vec4.SizeLBRT") != std::string::npos)
	{
		const auto& v2 = v.SizeLBRT();
		if (is_equal(v2.x, (T)-1.0) &&
			is_equal(v2.y, (T)4.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.pos") != std::string::npos)
	{
		const auto& v2 = v.pos();
		if (is_equal(v2.x, (T)5.0) &&
			is_equal(v2.y, (T)2.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.size") != std::string::npos)
	{
		const auto& v2 = v.size();
		if (is_equal(v2.x, (T)4.0) &&
			is_equal(v2.y, (T)6.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.post++") != std::string::npos)
	{
		const auto& vc = v++;
		if (is_equal(vc.x, (T)5.0) &&
			is_equal(vc.y, (T)2.0) &&
			is_equal(vc.z, (T)4.0) &&
			is_equal(vc.w, (T)6.0) &&
			is_equal(v.x, (T)6.0) &&
			is_equal(v.y, (T)3.0) &&
			is_equal(v.z, (T)5.0) &&
			is_equal(v.w, (T)7.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.post--") != std::string::npos)
	{
		const auto& vc = v--;
		if (is_equal(vc.x, (T)5.0) &&
			is_equal(vc.y, (T)2.0) &&
			is_equal(vc.z, (T)4.0) &&
			is_equal(vc.w, (T)6.0) &&
			is_equal(v.x, (T)4.0) &&
			is_equal(v.y, (T)1.0) &&
			is_equal(v.z, (T)3.0) &&
			is_equal(v.w, (T)5.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.pre++") != std::string::npos)
	{
		const auto& vc = ++v;
		if (is_equal(vc.x, (T)6.0) &&
			is_equal(vc.y, (T)3.0) &&
			is_equal(vc.z, (T)5.0) &&
			is_equal(vc.w, (T)7.0) &&
			is_equal(v.x, (T)6.0) &&
			is_equal(v.y, (T)3.0) &&
			is_equal(v.z, (T)5.0) &&
			is_equal(v.w, (T)7.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.pre--") != std::string::npos)
	{
		const auto& vc = --v;
		if (is_equal(vc.x, (T)4.0) &&
			is_equal(vc.y, (T)1.0) &&
			is_equal(vc.z, (T)3.0) &&
			is_equal(vc.w, (T)5.0) &&
			is_equal(v.x, (T)4.0) &&
			is_equal(v.y, (T)1.0) &&
			is_equal(v.z, (T)3.0) &&
			is_equal(v.w, (T)5.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.+=a") != std::string::npos)
	{
		v += (T)2.0;
		if (is_equal(v.x, (T)7.0) &&
			is_equal(v.y, (T)4.0) &&
			is_equal(v.z, (T)6.0) &&
			is_equal(v.w, (T)8.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.+=Vec4") != std::string::npos)
	{
		v += ct::vec4<T>((T)2.0, (T)4.0, (T)2.0, (T)4.0);
		if (is_equal(v.x, (T)7.0) &&
			is_equal(v.y, (T)6.0) &&
			is_equal(v.z, (T)6.0) &&
			is_equal(v.w, (T)10.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.-=a") != std::string::npos)
	{
		v -= (T)2.0;
		if (is_equal(v.x, (T)2.0) &&
			is_equal(v.y, (T)-0.0) &&
			is_equal(v.z, (T)4.0) &&
			is_equal(v.w, (T)4.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.-=Vec4") != std::string::npos)
	{
		v -= ct::vec4<T>((T)2.0, (T)4.0, (T)1.0, (T)2.0);
		if (is_equal(v.x, (T)3.0) &&
			is_equal(v.y, (T)-2.0) &&
			is_equal(v.z, (T)5.0) &&
			is_equal(v.w, (T)5.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.==a") != std::string::npos)
	{
		v = (T)2.0;
		bool vb = (v == (T)2.0);
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec4.==Vec4") != std::string::npos)
	{
		bool vb = (v == ct::vec4<T>((T)5.0, (T)2.0, (T)4.0, (T)6.0));
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec4.!=a") != std::string::npos)
	{
		v = (T)2.0;
		bool vb = (v != (T)5.0);
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec4.!=Vec4") != std::string::npos)
	{
		bool vb =
			(v != ct::vec4<T>((T)6.0, (T)2.0, (T)6.0, (T)2.0)) &&
			(v != ct::vec4<T>((T)5.0, (T)3.0, (T)6.0, (T)2.0)) &&
			(v != ct::vec4<T>((T)6.0, (T)3.0, (T)6.0, (T)2.0)) &&
			(v != ct::vec4<T>((T)2.0, (T)1.0, (T)6.0, (T)2.0));
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec4.*=a") != std::string::npos)
	{
		v *= (T)2.0;
		if (is_equal(v.x, (T)10.0) &&
			is_equal(v.y, (T)4.0) &&
			is_equal(v.z, (T)8.0) &&
			is_equal(v.w, (T)12.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.*=Vec4") != std::string::npos)
	{
		v *= ct::vec4<T>((T)2.0, (T)4.0, (T)2.0, (T)3.0);
		if (is_equal(v.x, (T)10.0) &&
			is_equal(v.y, (T)8.0) &&
			is_equal(v.z, (T)8.0) &&
			is_equal(v.w, (T)18.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4./=a") != std::string::npos)
	{
		v /= (T)2.0;
		if (is_equal(v.x, (T)2.0) &&
			is_equal(v.y, (T)1.0) &&
			is_equal(v.z, (T)2.0) &&
			is_equal(v.w, (T)3.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4./=Vec4") != std::string::npos)
	{
		v /= ct::vec4<T>((T)2.0, (T)4.0, (T)2.0, (T)2.0);
		if (is_equal(v.x, (T)2.0) &&
			is_equal(v.y, (T)0.0) &&
			is_equal(v.z, (T)2.0) &&
			is_equal(v.w, (T)3.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.sum") != std::string::npos)
	{
		v = ct::vec4<T>((T)5.0, (T)-2.0, (T)3.0, (T)5.0);
		T len = v.sum();
		if (is_equal(len, (T)11.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.sumAbs") != std::string::npos)
	{
		v = ct::vec4<T>((T)5.0, (T)-2.0, (T)3.0, (T)5.0);
		T len = v.sumAbs();
		if (is_equal(len, (T)15.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.emptyAND") != std::string::npos)
	{
		v = ct::vec4<T>((T)5.0, (T)-2.0, (T)3.0, (T)0.0);
		bool vb = v.emptyAND();
		if (!vb)
			return 0;
	}
	else if (vTestCode.find(".Vec4.emptyOR") != std::string::npos)
	{
		v = ct::vec4<T>((T)3.0, (T)-2.0, (T)5.0, (T)0.0);
		bool vb = v.emptyOR();
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec4.string") != std::string::npos)
	{
		v = ct::vec4<T>((T)5.0, (T)-2.0, (T)3.0, (T)2.0);
		const auto& str = v.string();
		const auto& str_coma = v.string(',');
		if (str == "5;-2;3;2" &&
			str_coma == "5,-2,3,2")
			return 0;
	}
	else if (vTestCode.find(".Vec4.mini") != std::string::npos)
	{
		T mini = v.mini();
		if (is_equal(mini, (T)2.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.maxi") != std::string::npos)
	{
		T maxi = v.maxi();
		if (is_equal(maxi, (T)6.0))
			return 0;
	}

	return 1; // error
}

// specialisation unsigned intergers
template <typename T>
int Test_cTools_unsigned_integer_Vec4_run_test(const std::string& vTestCode)
{
	ct::vec4<T> v((T)5.0, (T)2.0, (T)4.0, (T)6.0);

	if (vTestCode.find(".Vec4.[]") != std::string::npos)
	{
		if (is_equal(v[0], (T)5.0) &&
			is_equal(v[1], (T)2.0) &&
			is_equal(v[2], (T)4.0) &&
			is_equal(v[3], (T)6.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.Offset") != std::string::npos)
	{
		v = v.Offset((T)1.0, (T)2.0, (T)3.0, (T)2.0);
		if (is_equal(v.x, (T)6.0) &&
			is_equal(v.y, (T)4.0) &&
			is_equal(v.z, (T)7.0) &&
			is_equal(v.w, (T)8.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.Set") != std::string::npos)
	{
		v.Set((T)1.0, (T)2.0, (T)3.0, (T)2.0);
		if (is_equal(v.x, (T)1.0) &&
			is_equal(v.y, (T)2.0) &&
			is_equal(v.z, (T)3.0) &&
			is_equal(v.w, (T)2.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.xy") != std::string::npos)
	{
		const auto& v2 = v.xy();
		if (is_equal(v2.x, (T)5.0) &&
			is_equal(v2.y, (T)2.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.zw") != std::string::npos)
	{
		const auto& v2 = v.zw();
		if (is_equal(v2.x, (T)4.5) &&
			is_equal(v2.y, (T)6.5))
			return 0;
	}
	else if (vTestCode.find(".Vec4.SizeLBRT") != std::string::npos)
	{
		v.z = (T)6.0;
		const auto& v2 = v.SizeLBRT();
		if (is_equal(v2.x, (T)1.0) &&
			is_equal(v2.y, (T)4.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.pos") != std::string::npos)
	{
		const auto& v2 = v.pos();
		if (is_equal(v2.x, (T)5.0) &&
			is_equal(v2.y, (T)2.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.size") != std::string::npos)
	{
		const auto& v2 = v.size();
		if (is_equal(v2.x, (T)4.0) &&
			is_equal(v2.y, (T)6.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.post++") != std::string::npos)
	{
		const auto& vc = v++;
		if (is_equal(vc.x, (T)5.0) &&
			is_equal(vc.y, (T)2.0) &&
			is_equal(vc.z, (T)4.0) &&
			is_equal(vc.w, (T)6.0) &&
			is_equal(v.x, (T)6.0) &&
			is_equal(v.y, (T)3.0) &&
			is_equal(v.z, (T)5.0) &&
			is_equal(v.w, (T)7.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.post--") != std::string::npos)
	{
		const auto& vc = v--;
		if (is_equal(vc.x, (T)5.0) &&
			is_equal(vc.y, (T)2.0) &&
			is_equal(vc.z, (T)4.0) &&
			is_equal(vc.w, (T)6.0) &&
			is_equal(v.x, (T)4.0) &&
			is_equal(v.y, (T)1.0) &&
			is_equal(v.z, (T)3.0) &&
			is_equal(v.w, (T)5.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.pre++") != std::string::npos)
	{
		const auto& vc = ++v;
		if (is_equal(vc.x, (T)6.0) &&
			is_equal(vc.y, (T)3.0) &&
			is_equal(vc.z, (T)5.0) &&
			is_equal(vc.w, (T)7.0) &&
			is_equal(v.x, (T)6.0) &&
			is_equal(v.y, (T)3.0) &&
			is_equal(v.z, (T)5.0) &&
			is_equal(v.w, (T)7.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.pre--") != std::string::npos)
	{
		const auto& vc = --v;
		if (is_equal(vc.x, (T)4.0) &&
			is_equal(vc.y, (T)1.0) &&
			is_equal(vc.z, (T)3.0) &&
			is_equal(vc.w, (T)5.0) &&
			is_equal(v.x, (T)4.0) &&
			is_equal(v.y, (T)1.0) &&
			is_equal(v.z, (T)3.0) &&
			is_equal(v.w, (T)5.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.+=a") != std::string::npos)
	{
		v += (T)2.0;
		if (is_equal(v.x, (T)7.0) &&
			is_equal(v.y, (T)4.0) &&
			is_equal(v.z, (T)6.0) &&
			is_equal(v.w, (T)8.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.+=Vec4") != std::string::npos)
	{
		v += ct::vec4<T>((T)2.0, (T)4.0, (T)2.0, (T)4.0);
		if (is_equal(v.x, (T)7.0) &&
			is_equal(v.y, (T)6.0) &&
			is_equal(v.z, (T)6.0) &&
			is_equal(v.w, (T)10.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.-=a") != std::string::npos)
	{
		v -= (T)2.0;
		if (is_equal(v.x, (T)3.0) &&
			is_equal(v.y, (T)0.0) &&
			is_equal(v.z, (T)2.0) &&
			is_equal(v.w, (T)4.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.-=Vec4") != std::string::npos)
	{
		v -= ct::vec4<T>((T)2.0, (T)2.0, (T)1.0, (T)2.0);
		if (is_equal(v.x, (T)3.0) &&
			is_equal(v.y, (T)0.0) &&
			is_equal(v.z, (T)3.0) &&
			is_equal(v.w, (T)4.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.==a") != std::string::npos)
	{
		v = (T)2.0;
		bool vb = (v == (T)2.0);
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec4.==Vec4") != std::string::npos)
	{
		bool vb = (v == ct::vec4<T>((T)5.0, (T)2.0, (T)4.0, (T)6.0));
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec4.!=a") != std::string::npos)
	{
		v = (T)2.0;
		bool vb = (v != (T)5.0);
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec4.!=Vec4") != std::string::npos)
	{
		bool vb =
			(v != ct::vec4<T>((T)6.0, (T)2.0, (T)6.0, (T)2.0)) &&
			(v != ct::vec4<T>((T)5.0, (T)3.0, (T)6.0, (T)2.0)) &&
			(v != ct::vec4<T>((T)6.0, (T)3.0, (T)6.0, (T)2.0)) &&
			(v != ct::vec4<T>((T)2.0, (T)1.0, (T)6.0, (T)2.0));
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec4.*=a") != std::string::npos)
	{
		v *= (T)2.0;
		if (is_equal(v.x, (T)10.0) &&
			is_equal(v.y, (T)4.0) &&
			is_equal(v.z, (T)8.0) &&
			is_equal(v.w, (T)12.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.*=Vec4") != std::string::npos)
	{
		v *= ct::vec4<T>((T)2.0, (T)4.0, (T)2.0, (T)3.0);
		if (is_equal(v.x, (T)10.0) &&
			is_equal(v.y, (T)8.0) &&
			is_equal(v.z, (T)8.0) &&
			is_equal(v.w, (T)18.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4./=a") != std::string::npos)
	{
		v /= (T)2.0;
		if (is_equal(v.x, (T)2.0) &&
			is_equal(v.y, (T)1.0) &&
			is_equal(v.z, (T)2.0) &&
			is_equal(v.w, (T)3.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4./=Vec4") != std::string::npos)
	{
		v /= ct::vec4<T>((T)2.0, (T)4.0, (T)2.0, (T)2.0);
		if (is_equal(v.x, (T)2.0) &&
			is_equal(v.y, (T)0.0) &&
			is_equal(v.z, (T)2.0) &&
			is_equal(v.w, (T)3.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.sum") != std::string::npos)
	{
		v = ct::vec4<T>((T)5.0, (T)2.0, (T)3.0, (T)5.0);
		T len = v.sum();
		if (is_equal(len, (T)15.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.emptyAND") != std::string::npos)
	{
		v = ct::vec4<T>((T)5.0, (T)-2.0, (T)3.0, (T)0.0);
		bool vb = v.emptyAND();
		if (!vb)
			return 0;
	}
	else if (vTestCode.find(".Vec4.emptyOR") != std::string::npos)
	{
		v = ct::vec4<T>((T)3.0, (T)-2.0, (T)5.0, (T)0.0);
		bool vb = v.emptyOR();
		if (vb)
			return 0;
	}
	else if (vTestCode.find(".Vec4.string") != std::string::npos)
	{
		v = ct::vec4<T>((T)5.0, (T)2.0, (T)3.0, (T)2.0);
		const auto& str = v.string();
		const auto& str_coma = v.string(',');
		if (str == "5;2;3;2" &&
			str_coma == "5,2,3,2")
			return 0;
	}
	else if (vTestCode.find(".Vec4.mini") != std::string::npos)
	{
		T mini = v.mini();
		if (is_equal(mini, (T)2.0))
			return 0;
	}
	else if (vTestCode.find(".Vec4.maxi") != std::string::npos)
	{
		T maxi = v.maxi();
		if (is_equal(maxi, (T)6.0))
			return 0;
	}

	return 1; // error
}

///////////////////////////////////////////////////////////
//// PLANE ////////////////////////////////////////////////
///////////////////////////////////////////////////////////

// specialisation unsigned intergers
template <typename T>
int Test_cTools_float_double_Plane_run_test(const std::string& vTestCode)
{
	ct::plane<T> a(ct::vec3<T>((T)5.0, (T)0.0, (T)0.0));
	ct::plane<T> b(ct::vec3<T>((T)0.0, (T)5.0, (T)0.0));
	ct::plane<T> c(ct::vec3<T>((T)0.0, (T)0.0, (T)5.0));
	ct::vec3<T> good_result = ct::vec3<T>((T)5.0, (T)5.0, (T)5.0);
	ct::vec3<T> res;

	if (vTestCode.find(".Plane.get_plane_intersection") != std::string::npos)
	{
		if (ct::get_plane_intersection(a, b, c, res))
		{
			return (res != good_result);
		}
	}
	else if (vTestCode.find(".Plane.is_on_plane") != std::string::npos)
	{
		return 
			!ct::is_on_plane(a, good_result) && 
			!ct::is_on_plane(b, good_result) && 
			!ct::is_on_plane(c, good_result);
	}
	else if (vTestCode.find(".Plane.construtor.point") != std::string::npos)
	{
		ct::vec3<T> p = ct::vec3<T>((T)5, (T)0, (T)0);
		ct::plane<T> pln(p);
		if (pln.n == ct::vec3<T>((T)1, (T)0, (T)0) && pln.d == (T)5)
			return 0;
	}
	else if (vTestCode.find(".Plane.construtor.point_and_normal") != std::string::npos)
	{
		ct::vec3<T> p = ct::vec3<T>((T)5, (T)0, (T)0);
		ct::vec3<T> n = ct::vec3<T>((T)1, (T)0, (T)0);
		ct::plane<T> pln(p, n);
		if (pln.n == ct::vec3<T>((T)1, (T)0, (T)0) && pln.d == (T)5)
			return 0;
	}
	else if (vTestCode.find(".Plane.construtor.3_points") != std::string::npos)
	{
		ct::vec3<T> p0 = ct::vec3<T>((T)0, (T)5, (T)0);
		ct::vec3<T> p1 = ct::vec3<T>((T)5, (T)5, (T)0);
		ct::vec3<T> p2 = ct::vec3<T>((T)0, (T)5, (T)5);
		ct::plane<T> pln(p0, p1, p2);
		if (pln.n == ct::vec3<T>((T)0, (T)1, (T)0) && pln.d == (T)5)
			return 0;
	}

	return 1; // error
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

int Test_cTools_run_test(const std::string& vTestCode)
{
	// Vec2

	if (vTestCode.find("cTools.double.Vec2.") != std::string::npos)
	{
		return Test_cTools_Vec2_run_test<double>(vTestCode);
	}
	else if (vTestCode.find("cTools.float.Vec2.") != std::string::npos)
	{
		return Test_cTools_Vec2_run_test<float>(vTestCode);
	}
	else if (vTestCode.find("cTools.bool.Vec2.") != std::string::npos)
	{
		return Test_cTools_Vec2_run_test<bool>(vTestCode);
	}
	else if (vTestCode.find("cTools.int.Vec2.") != std::string::npos)
	{
		return Test_cTools_signed_integer_Vec2_run_test<int32_t>(vTestCode);
	}
	else if (vTestCode.find("cTools.uint.Vec2.") != std::string::npos)
	{
		return Test_cTools_unsigned_integer_Vec2_run_test<uint32_t>(vTestCode);
	}

	// Vec3

	else if (vTestCode.find("cTools.double.Vec3.") != std::string::npos)
	{
		return Test_cTools_Vec3_run_test<double>(vTestCode);
	}
	else if (vTestCode.find("cTools.float.Vec3.") != std::string::npos)
	{
		return Test_cTools_Vec3_run_test<float>(vTestCode);
	}
	else if (vTestCode.find("cTools.bool.Vec3.") != std::string::npos)
	{
		return Test_cTools_Vec3_run_test<bool>(vTestCode);
	}
	else if (vTestCode.find("cTools.int.Vec3.") != std::string::npos)
	{
		return Test_cTools_signed_integer_Vec3_run_test<int32_t>(vTestCode);
	}
	else if (vTestCode.find("cTools.uint.Vec3.") != std::string::npos)
	{
		return Test_cTools_unsigned_integer_Vec3_run_test<uint32_t>(vTestCode);
	}

	// Vec4

	else if (vTestCode.find("cTools.double.Vec4.") != std::string::npos)
	{
		return Test_cTools_Vec4_run_test<double>(vTestCode);
	}
	else if (vTestCode.find("cTools.float.Vec4.") != std::string::npos)
	{
		return Test_cTools_Vec4_run_test<float>(vTestCode);
	}
	else if (vTestCode.find("cTools.bool.Vec4.") != std::string::npos)
	{
		return Test_cTools_Vec4_run_test<bool>(vTestCode);
	}
	else if (vTestCode.find("cTools.int.Vec4.") != std::string::npos)
	{
		return Test_cTools_signed_integer_Vec4_run_test<int32_t>(vTestCode);
	}
	else if (vTestCode.find("cTools.uint.Vec4.") != std::string::npos)
	{
		return Test_cTools_unsigned_integer_Vec4_run_test<uint32_t>(vTestCode);
	}

	// Plane

	else if (vTestCode.find("cTools.double.Plane.") != std::string::npos)
	{
		return Test_cTools_float_double_Plane_run_test<double>(vTestCode);
	}
	else if (vTestCode.find("cTools.float.Plane.") != std::string::npos)
	{
		return Test_cTools_float_double_Plane_run_test<float>(vTestCode);
	}

	return 1; // error
}