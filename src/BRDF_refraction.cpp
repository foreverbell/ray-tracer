
#include "BRDF_refraction.hpp"
#include "vector3D.hpp"
#include "world.hpp"

namespace ray_tracer {

	BRDF_refraction::BRDF_refraction(const colorRGB &rho_, double eta_) : BRDF(rho_) { 
		eta = eta_;
	}

	colorRGB BRDF_refraction::sample_f(shade_context *context_ptr, const vector3D &win) const {
		shade_context info = *context_ptr;
		info.trace_depth = context_ptr->trace_depth - 1;
		
		vector3D normal = context_ptr->normal;
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

 		return rho * context_ptr->tracer_ptr->trace_ray(ray(context_ptr->hit_point, wout), &info);
	}
}
