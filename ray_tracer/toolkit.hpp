#ifndef __TOOLKIT_HPP__
#define __TOOLKIT_HPP__

#include <cmath>
#include <cfloat>
#include <vector>
#include <cassert>

namespace ray_tracer {

	const double PI = acos(-1.0);
	const double E = exp(1.0);
	const double EPSILON = 1e-8;

	#define DBLCMP(_x_) ((_x_) < -EPSILON ? -1 : ((_x_) > EPSILON ? 1 : 0))

	inline double pow(double base, int power) {
		if (power <= 0) {
			return 1;
		} else {
			double result = 1;

			while (power > 0 && result > EPSILON) {
				if (power & 1) result *= base;
				power >>= 1;
				base *= base;
			}
			return result;
		}
	}

	/* private marcos. */
	#define __ROOT_RANGE__ 1e10

	/* private functions. */
	inline double __root_cal__(const std::vector<double> &coef, double x) {
		double e = 1, s = 0;

		for (int i = 0; i < (int) coef.size(); ++i) {
			s += coef[i] * e;
			e *= x;
		}

		return s;
	}

	/* private functions. */
	inline double __root_find__(const std::vector<double> &coef, double l, double r) {
		int sl = DBLCMP(__root_cal__(coef, l)), sr = DBLCMP(__root_cal__(coef, r));

		if (sl == 0) return l;
		if (sr == 0) return r;
		if (sl * sr > 0) return __ROOT_RANGE__;

		for (int tt = 0; tt < 64 && r - l > EPSILON; ++tt) {
			double mid = l / 2 + r / 2;
			int smid = DBLCMP(__root_cal__(coef, mid));
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

		while (n > 1 && DBLCMP(coef[n]) == 0) {
			n -= 1;
		}

		if (n == 1) {
			if (DBLCMP(coef[1]) != 0) ret.push_back(-coef[0] / coef[1]);
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
		droot.insert(droot.begin(), -__ROOT_RANGE__);
		droot.push_back(__ROOT_RANGE__);

		for (int i = 0; i + 1 < (int) droot.size(); ++i) {
			double tmp = __root_find__(coef, droot[i], droot[i + 1]);
			if (fabs(tmp) < __ROOT_RANGE__) ret.push_back(tmp);
		}

		return ret;
	}
}

#endif
