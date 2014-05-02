#ifndef __MATERIAL_PHONG_HPP__
#define __MATERIAL_PHONG_HPP__

#include "material.hpp"
#include "BRDF.hpp"
#include "BRDF_lambertian.hpp"
#include "BRDF_phong.hpp"
#include <memory>

namespace ray_tracer {
	class material_phong : public material  {
	public:
		material_phong();
		material_phong(const colorRGB &, const colorRGB &, int);
		colorRGB material_shade(hit_info *, const colorRGB &, const vector3D &, const vector3D &) const;
		void set_specular_shininess(const int &);
	private:
		std::unique_ptr<BRDF_lambertian> diffuse_ptr;
		std::unique_ptr<BRDF_phong> specular_ptr;
	};

	inline void material_phong::set_specular_shininess(const int &shininess_) {
		specular_ptr->set_shininess(shininess_);
	}
}

#endif