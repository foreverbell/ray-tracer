#ifndef __SURFACE_FRACTAL_TERRAIN_HPP__
#define __SURFACE_FRACTAL_TERRAIN_HPP__

#include "surface.hpp"
#include "surface_mesh.hpp"
#include <vector>
#include <random>

namespace ray_tracer {
	class surface_fractal_terrain : public surface_mesh {
	public:
		surface_fractal_terrain(double, int, double, double, int); // sideLength, size, heightScale, h, seedValue
	private:
		void generate_heightmap(std::vector<std::vector<double> > &, int, double, double);
		void generate_mesh(const std::vector<std::vector<double> > &, int, double);
		double generate_random(double, double);
	private:
		std::default_random_engine rand_generator;
	};
}

#endif
