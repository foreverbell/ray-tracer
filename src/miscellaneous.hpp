#ifndef __MISCELLANEOUS_HPP__
#define __MISCELLANEOUS_HPP__

#include <cmath>
#include <cfloat>
#include <vector>
#include <cassert>
#include <utility>

namespace ray_tracer {

	const double pi = acos(-1.0);
	const double epsilon = 1e-8;
	const double __root_range = 1e10;

	using fname_ptr_t = const char *;

	/* utility functions. */
	inline int dblsgn(double x) {
		return (x < -epsilon) ? (-1) : (x > epsilon); 
	}

	inline int isqrt(int x) {
		return (int) sqrt((double) x + epsilon);
	}

	template<typename T1, typename T2>
	inline bool compare_by_first(const std::pair<T1, T2> &a, const std::pair<T1, T2> &b) {
		return a.first < b.first;
	}

	template<typename T1, typename T2>
	inline bool compare_by_second(const std::pair<T1, T2> &a, const std::pair<T1, T2> &b) {
		return a.second < b.second;
	}

	template<typename T>
	inline T clamp(const T &x, const T &low, const T &high) {
		if (x < low) {
			return low;
		} else if (x > high) {
			return high;
		}
		return x;
	}

	inline double __root_cal(const std::vector<double> &coef, double x) {
		double e = 1, s = 0;

		for (int i = 0; i < (int) coef.size(); ++i) {
			s += coef[i] * e;
			e *= x;
		}

		return s;
	}

	inline double __root_find(const std::vector<double> &coef, double l, double r) {
		int sl = dblsgn(__root_cal(coef, l)), sr = dblsgn(__root_cal(coef, r));

		if (sl == 0) return l;
		if (sr == 0) return r;
		if (sl * sr > 0) return __root_range;

		for (int tt = 0; tt < 64 && r - l > epsilon; ++tt) {
			double mid = l / 2 + r / 2;
			int smid = dblsgn(__root_cal(coef, mid));
			if (smid == 0) return mid;
			if (sl * smid < 0) r = mid;
			else l = mid;
		}

		return l / 2 + r / 2;
	}

	/* Solve equation c[0] + c[1]*x + c[2]*x^2 + ... + c[n]*x^n = 0. */
	inline std::vector<double> equation_solve(const std::vector<double> &coef, int n) {
		std::vector<double> ret; 

		assert((int) coef.size() == n + 1);

		while (n > 1 && dblsgn(coef[n]) == 0) {
			n -= 1;
		}

		if (n == 1) {
			if (dblsgn(coef[1]) != 0) ret.push_back(-coef[0] / coef[1]);
			return ret;
		}

		if (n == 2) {
			double a = coef[2], b = coef[1], c = coef[0];
			double delta = b * b - 4 * a * c;

			if (delta > 0) {
				delta = sqrt(delta);
				ret.push_back((-b - delta) / 2 / a);
				ret.push_back((-b + delta) / 2 / a);

				if (a < 0) std::swap(ret[0], ret[1]); // keep order
			}
			return ret;
		}

		std::vector<double> dcoef(n);
		for (int i = 0; i < n; ++i) dcoef[i] = coef[i + 1] * (i + 1);

		std::vector<double> droot = equation_solve(dcoef, n - 1);
		droot.insert(droot.begin(), -__root_range);
		droot.push_back(__root_range);

		for (int i = 0; i + 1 < (int) droot.size(); ++i) {
			double tmp = __root_find(coef, droot[i], droot[i + 1]);
			if (fabs(tmp) < __root_range) ret.push_back(tmp);
		}

		return ret;
	}
}

#endif
