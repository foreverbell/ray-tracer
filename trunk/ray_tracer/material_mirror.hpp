#ifndef __MATERIAL_MIRROR_HPP__
#define __MATERIAL_MIRROR_HPP__

#include "material.hpp"
#include "BRDF.hpp"
#include "BRDF_reflection.hpp"
#include "BRDF_lambertian.hpp"
#include <memory>

namespace ray_tracer {
	class material_mirror : public material  {
	public:
		material_mirror();
		material_mirror(const colorRGB &);
		colorRGB material_shade(hitInfo *, const colorRGB &, const vector3D &, const vector3D &) const;
	private:
		std::unique_ptr<BRDF_reflection> reflection_ptr;
		std::unique_ptr<BRDF_lambertian> diffuse_ptr;
	};
}

#endif