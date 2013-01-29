#ifndef __SURFACE_CONVEXHULL_HPP__
#define __SURFACE_CONVEXHULL_HPP__

#include "surface.hpp"
#include "surface_triangle.hpp"
#include "surface_tricompound.hpp"
#include "convexhull.hpp"
#include <vector>

namespace ray_tracer {
	class surface_convexhull : public surface_tricompound {
	public:
		surface_convexhull(const std::vector<point3D> &);
	protected:
		surface_convexhull();
		void construct(const std::vector<point3D> &);
	private:
		std::vector<point3D> points;
	};
}

#endif
