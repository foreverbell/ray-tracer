
#include "demo.hpp"

using namespace ray_tracer;

void demo_6::set_world() {
	cam = new camera_pinhole(point3D(-10, -10, 50), point3D(50, 50, 0), vector3D(1, 1, 2.4), atan(2.0), atan(2.0), true);

	surface_fractal_terrain *sterrain = new surface_fractal_terrain(100, 64, 100, 1, 123);
	sterrain->set_material(new material_matte());
	sterrain->set_texture(new texture_solid(color_green));

	light *l = new light_point(point3D(50, 50, 80), color_white);
	l->set_attenuation(true, 1, 0.0001, 0.00005);
	l->set_shadow(true);

	wld.set_ambient(color_white / 5);
	wld.set_sampler(new sampler_jittered(4));
	wld.set_camera(cam);
	wld.set_fog(new fog(0.005, 1, color_white));
	wld.add_surface(sterrain);
	wld.add_light(l);
}