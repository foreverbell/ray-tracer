#ifndef __MISC_HPP__
#define __MISC_HPP__

#include <cstdlib>
#include <cmath>

namespace ray_tracer {

	const double pi = acos(-1.0);
	const double e = exp(1.0);
	const double epsilon = 1e-6;
	const double huge_double = 10e10;
	#define dblcmp(_x_) ((_x_) < -epsilon ? -1 : ((_x_) > (epsilon ? 1 : 0)))
	
	inline double pow(double base, int power) {
		if (power <= 0) {
			return 1;
		} else {
			double result = 1;

			while (power > 0 && result > epsilon) {
				if (power & 1) result *= base;
				power >>= 1;
				base *= base;
			}
			return result;
		}
	}

// #define __INV_SQRT_FAST__
// #define __INV_SQRT_FAST2__

#ifdef __INV_SQRT_FAST__
	// Fast version, but have relative float error
	// This code is copyed from Quake III Q_rsqrt
	inline double inv_sqrt(double dnumber) {
		float number = (float)dnumber;
		int i;
		float x2, yy;
		const float threehalfs = 1.5f;
		
		x2 = number * 0.5f;
		yy = number;
		i = * (int *) &yy;  // evil floating point bit level hacking
		i = 0x5f3759df - (i >> 1); // what the fuck?
		yy = * (float *) &i;
		yy = yy * (threehalfs - (x2 * yy * yy)); // 1st iteration
#ifdef __INV_SQRT_FAST2__
		yy = yy * (threehalfs - (x2 * yy * yy)); // 2nd iteration, this can be removed
#endif
		return (double)yy;
	}
#else
	inline double inv_sqrt(double number) {
		return 1 / sqrt(number);
	}
#endif
}

#endif