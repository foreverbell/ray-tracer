#ifndef __CONVEX_HPP__
#define __CONVEX_HPP__

#include <utility>
#include <tuple>
#include <map>
#include <vector>
#include "point3D.hpp"

namespace ray_tracer {

	typedef std::tuple<int, int, int> face_t;
	typedef std::tuple<int, int> edge_t;

	class convexhull {
	public:
		convexhull(std::vector<point3D> &);
		std::pair<std::vector<face_t>, std::vector<edge_t> > construct();
	private:
		bool remove(int, int, int);
		void walk(int, int);
		double mixed_product(const point3D &, const point3D &, const point3D &, const point3D &);
	private:
		std::vector<std::pair<face_t, bool> > faces;
		std::vector<point3D> &points;
		std::map<std::pair<int, int>, int> rface;
	};
}

#endif