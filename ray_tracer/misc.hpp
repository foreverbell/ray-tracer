#ifndef __MISC_HPP__
#define __MISC_HPP__

#include <cassert>
#include <cstdlib>
#include <cmath>

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

	inline double inverse_sqrt(double number) {
		return 1 / sqrt(number);
	}
}

#endif