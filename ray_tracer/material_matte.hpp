#ifndef __MATERIAL_MATTE_HPP__
#define __MATERIAL_MATTE_HPP__

#include "material.hpp"
#include "BRDF.hpp"
#include "BRDF_lambertian.hpp"
#include <memory>

namespace ray_tracer {
	class material_matte : public material  {
	public:
		material_matte();
		material_matte(const colorRGB &);
		colorRGB material_shade(hit_info *, const colorRGB &, const vector3D &, const vector3D &, bool) const;
	private:
		std::unique_ptr<BRDF_lambertian> diffuse_ptr;
	};
}

#endif