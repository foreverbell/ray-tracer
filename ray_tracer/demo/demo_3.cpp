
#include "demo.hpp"

using namespace ray_tracer;

void demo_3::set_world() {
	camera *cam;
	surface *s;
	material_phong *m;
	texture *t;
	light *l;

	cam = new camera_pinhole(point3D(-20, 0, 0), point3D(1, 0, 0), vector3D(0, 0, 1), atan(2), atan(2), true);
	// cam = new camera_orthographic(point3D(0, 0, 0), point3D(1, 0, 0), vector3D(0, 0, 1), 40, 40);

	s = new surface_quadratic;
	m = new material_phong;
	m->set_specular_shininess(10);
	t = new texture_checker(color_white, colorRGB(0.2, 0.2, 0.2));
	s->set_material(m);
	s->set_texture(t);

	l = new light_point(point3D(-20, 0, 0), color_white);
	l->set_shadow(false);

	wld.set_ambient(color_white / 5);
	// wld.set_sampler(new sampler_jittered(25));
	wld.set_camera(cam);
	wld.add_surface(s);
	wld.add_light(l);
}