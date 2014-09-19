
#include "demo.hpp"

using namespace ray_tracer;

void demo_7::set_world() {
	cam = new camera_pinhole(point3D(2, 2, 3), point3D(0, 0, 0), vector3D(1, -1, 0), atan(2.0), atan(2.0), true);

	surface_sphere *sp1 = new surface_sphere(point3D(-1, -1, -1), 2);
	surface_cube *sp2 = new surface_cube(point3D(1, 1, 1), 0.5);
	sp1->set_material(new material_matte());
	sp1->set_texture(new texture_solid(color_red));
	sp2->set_material(new material_phong(color_white, color_white, 100));
	sp2->set_texture(new texture_solid(color_blue));
//	surface *s = new surface_subtract(sp1, sp2);

	light *l = new light_point(point3D(5, 5, 5), color_white);
	l->set_shadow(true);

	// wld.set_ambient(color_white / 5);
	wld.set_sampler(new sampler_jittered(4));
	wld.set_camera(cam);
	wld.set_fog(new fog(0.002, 1, color_white));
	wld.add_surface(sp2);
	wld.add_light(l);
}
