#ifndef __LIGHT_HPP__
#define __LIGHT_HPP__

#include "point3D.hpp"
#include "colorRGB.hpp"
#include "shade_context.hpp"
#include "ray.hpp"

namespace ray_tracer {
	class light {
	public:
		light();
		light(const point3D &, const colorRGB &);
		virtual ~light();
		virtual point3D get_light_origin(shade_context *) const;
		void set_position(const point3D &);
		void set_color(const colorRGB &);
		void set_shadow(bool);
		void set_spot(bool, const vector3D &, double, int);
		void set_attenuation(bool, double, double, double);
		bool under_shadow(shade_context *) const;
		virtual colorRGB light_shade(shade_context *) const;
		bool in_range(shade_context *) const;
	protected:
		point3D position;
		colorRGB color;
		// attributes
		bool cast_shadow, spot_enabled, attenuation_enabled;
		// spot
		vector3D spot_direction;
		double spot_cutoff, spot_cos_cutoff;
		int spot_exponent;
		// attenuation
		double attenuation_constant, attenuation_linear, attenuation_quadratic;
	};

	inline void light::set_position(const point3D &position_) {
		position = position_;
	}

	inline void light::set_color(const colorRGB &color_) {
		color = color_;
	}

	inline void light::set_shadow(bool shadow_) {
		cast_shadow = shadow_;
	}

	inline void light::set_spot(bool enabled_, const vector3D &direction_ = vector3D(0, 0, 1), double cutoff_ = pi / 2, int exponent_ = 1) {
		spot_enabled = enabled_;
		spot_direction = direction_.normalized();
		spot_cutoff = cutoff_;
		spot_cos_cutoff = cos(spot_cutoff);
		spot_exponent = exponent_;
	}

	inline void light::set_attenuation(bool enabled_, double constant_ = 1, double linear_ = 0, double quadratic_ = 0) {
		attenuation_enabled = enabled_;
		attenuation_constant = constant_;
		attenuation_linear = linear_;
		attenuation_quadratic = quadratic_;
	}
}

#endif