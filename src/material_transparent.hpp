#ifndef __MATERIAL_TRANSPARENT_HPP__
#define __MATERIAL_TRANSPARENT_HPP__

#include "material.hpp"
#include "BRDF.hpp"
#include "BRDF_reflection.hpp"
#include "BRDF_refraction.hpp"
#include <memory>

namespace ray_tracer {

	class material_transparent : public material  {
	public:
		material_transparent();
		material_transparent(const colorRGB &, const colorRGB &, double);
		colorRGB material_shade(shade_context *, const vector3D &, const vector3D &, bool) const;
	private:
		std::unique_ptr<BRDF_reflection> reflection_ptr;
		std::unique_ptr<BRDF_refraction> refraction_ptr;
	};
}

#endif