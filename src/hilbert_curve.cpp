
#include <vector>
#include <algorithm>
#include <utility>
#include "hilbert_curve.hpp"

namespace ray_tracer {

	hilbert_curve::point_container_t hilbert_curve::aftrans(int order, int dir, hilbert_curve::point_container_t pt, int dx, int dy) {
		int n = 1 << order, m = pt.size();
		point_container_t result;

		result.resize(m);
		for (int i = 0; i < m; ++i) {
			if (dir == 0) {
				result[i] = std::make_pair(pt[i].second, n - pt[i].first + 1);
			} else if (dir == 1 || dir == 2) {
				result[i] = pt[i];
			} else {
				result[i] = std::make_pair(pt[i].second, pt[i].first);
			}
			result[i].first += dx;
			result[i].second += dy;
		}
		if (dir == 0) {
			reverse(result.begin(), result.end());
		}
		return result;
	}

	hilbert_curve::point_container_t hilbert_curve::hilbert(int order) {
		point_container_t result;
		if (order == 1) {
			result.resize(4);
			result[0] = std::make_pair(2, 1);
			result[1] = std::make_pair(1, 1);
			result[2] = std::make_pair(1, 2);
			result[3] = std::make_pair(2, 2);
		} else {
			point_container_t rec = hilbert(order - 1), tmp;
			int n = 1 << (order - 1);
			int meta_n = rec.size();

			result.resize(meta_n * 4);

			tmp = aftrans(order - 1, 0, rec, n, 0);
			std::copy(tmp.begin(), tmp.end(), result.begin());

			tmp = aftrans(order - 1, 1, rec, 0, 0);
			std::copy(tmp.begin(), tmp.end(), result.begin() + meta_n);

			tmp = aftrans(order - 1, 2, rec, 0, n);
			std::copy(tmp.begin(), tmp.end(), result.begin() + meta_n * 2);

			tmp = aftrans(order - 1, 3, rec, n, n);
			std::copy(tmp.begin(), tmp.end(), result.begin() + meta_n * 3);
		}
		return result;
	}

	void hilbert_curve::init(int order) {
		curve = hilbert(order);
		iter = 0;
	}

	bool hilbert_curve::next(int &x, int &y) {
		if (eof()) {
			return false;
		}

		x = curve[iter].first;
		y = curve[iter].second;

		iter += 1;
		return true;
	}

	bool hilbert_curve::eof() const {
		return iter >= (int) curve.size();
	}
}
