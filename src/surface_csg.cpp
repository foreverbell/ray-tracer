
#include "ray.hpp"
#include "surface_csg.hpp"
#include <algorithm>

namespace ray_tracer {
	
	template<int a, int sgn2>
	inline std::pair<intersection_context, int> __surface_csg_abstract::boolean_intersect(const ray &emission_ray) const {
		std::vector<intersection_context> is1, is2;
		int in1, in2, who;

		is1 = s1->intersecta(emission_ray);
		is2 = s2->intersecta(emission_ray);
		in1 = is1.size() & 1;
		in2 = is2.size() & 1;

		for (std::vector<intersection_context>::iterator it1 = is1.begin(), it2 = is2.begin(); it1 != is1.end() || it2 != is2.end(); ) {
			if (it1 == is1.end()) {
				who = 2;
			} else if (it2 == is2.end()) {
				who = 1;
			} else if (it1->t < it2->t) {
				who = 1;
			} else {
				who = 2;
			}

			int &in = (who == 1 ? in1 : in2);
			std::vector<intersection_context>::iterator &it = (who == 1 ? it1 : it2);
			
			in ^= 1;

			if (in1 + in2 * sgn2 == a) {
				if (it->surface_ptr == nullptr) {
					return std::make_pair(intersection_context(it->t, who == 1 ? s1 : s2, it->flag), who);
				} else {
					return std::make_pair(*it, who);
				}
			} else {
				++it;
			}
		}

		return std::make_pair(null_intersect, 1);
	}

	surface_and::surface_and(const surface *a, const surface *b) : __surface_csg_abstract(a, b) { }
	surface_or::surface_or(const surface *a, const surface *b) : __surface_csg_abstract(a, b) { }
	surface_subtract::surface_subtract(const surface *a, const surface *b) : __surface_csg_abstract(a, b) { }

	intersection_context surface_and::intersect(const ray &emission_ray) const {
		return boolean_intersect<2, 1>(emission_ray).first;
	}

	intersection_context surface_or::intersect(const ray &emission_ray) const {
		return boolean_intersect<1, 1>(emission_ray).first;
	}

	intersection_context surface_subtract::intersect(const ray &emission_ray) const {
		auto context = boolean_intersect<1, -1>(emission_ray);
		
		if (context.second == 2) {
			context.first.flag |= surface_flag_revert_normal;
		}
		
		return context.first;
	}
}
