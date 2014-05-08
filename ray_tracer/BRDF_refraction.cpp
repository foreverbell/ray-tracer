
#include "BRDF_refraction.hpp"
#include "vector3D.hpp"
#include "misc.hpp"
#include "world.hpp"

namespace ray_tracer {

	BRDF_refraction::BRDF_refraction(const colorRGB &rho_, double eta_) : BRDF(rho_) { 
		eta = eta_;
	}

	colorRGB BRDF_refraction::sample_f(hit_info *info_ptr, const vector3D &win) const {
		hit_info info = *info_ptr;
		info.trace_depth = info_ptr->trace_depth - 1;
		
		vector3D normal = info_ptr->normal;
		double cos_theta_i = normal * win;
		double _eta = eta;

		if (cos_theta_i < 0) {
			_eta = 1 / _eta;
			cos_theta_i = -cos_theta_i;
			normal = -normal;
		}

		double cos_theta2 = 1 - (1 - cos_theta_i * cos_theta_i) / _eta / _eta;

		if (cos_theta2 < 0) return color_black;
		cos_theta2 = sqrt(cos_theta2);
		vector3D wout = -win / _eta - normal * (cos_theta2 - cos_theta_i / _eta);

 		return rho * info_ptr->camera_ptr->render_scene(info_ptr->hit_point, wout, &info);
	}
}
