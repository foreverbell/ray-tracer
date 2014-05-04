
#include "demo.hpp"

using namespace ray_tracer;

void demo_3::set_world() {
	surface_quadratic *s;
	material_matte *m;
	texture *t;
	light *l;

	cam = new camera_pinhole(point3D(-20, 0, 10), point3D(0, 0, 0), vector3D(0.5, 0, 1), atan(2), atan(2), false);
	// cam = new camera_orthographic(point3D(20, 0, 0), point3D(0, 0, 0), vector3D(0, 0, 1), 40, 40);

	s = new surface_quadratic();
	s->coef_xx = 0.5, s->coef_yy = 0.5, s->coef_zz = -0.1, s->coef_const = -1;
	s->set_range_z(-30, 18);
	m = new material_matte(color_azure);
	t = new texture_solid(color_azure);
	s->set_material(m);
	s->set_texture(t);

	l = new light_point(point3D(-20, 0, 0), color_white);
	l->set_shadow(false);

	wld.set_ambient(color_black);
	wld.set_camera(cam);
	wld.set_sampler(new sampler_jittered(16));
	wld.add_surface(s);
	wld.add_light(l);
}