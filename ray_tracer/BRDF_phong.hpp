#ifndef __BRDF_BLINN_PHONG_HPP__
#define __BRDF_BLINN_PHONG_HPP__

#include "BRDF.hpp"

namespace ray_tracer {
	class BRDF_phong : public BRDF {
	public:
		BRDF_phong(const colorRGB &);
		colorRGB f(hit_info *, const vector3D &, const vector3D &) const;
		void set_shininess(const int &);	
	private:
		int shininess;
	};

	inline void BRDF_phong::set_shininess(const int &shininess_) {
		shininess = shininess_;
	}
}

#endif