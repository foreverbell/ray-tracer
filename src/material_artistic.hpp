#ifndef __MATERIAL_ARTISTIC_HPP__
#define __MATERIAL_ARTISTIC_HPP__

#include "material.hpp"
#include "BRDF.hpp"
#include "BRDF_artistic.hpp"
#include <memory>

namespace ray_tracer {

	class material_artistic : public material  {
	public:
		material_artistic();
		material_artistic(const colorRGB &, const colorRGB &);
		colorRGB material_shade(shade_context *, const vector3D &, const vector3D &) const;
	private:
		std::unique_ptr<BRDF_artistic> artistic_ptr;
	};
}

#endif