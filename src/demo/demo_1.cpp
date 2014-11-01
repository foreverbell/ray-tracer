
#include "demo.hpp"

using namespace ray_tracer;

void demo_1::set_world() {
	surface *s1, *s2, *s3;
	light *l1, *l2;

	cam = new camera_pinhole(point3D(0, 0, 12), point3D(0, 0, 0), vector3D(0, 1, 0), atan(2.0), atan(2.0), true);

	s1 = new surface_sphere(point3D(15, -7, 0), 9);
	s1->set_material(new material_mirror());
	s1->set_texture(new texture_solid(color::azure));
	s2 = new surface_sphere(point3D(30, 9, 0), 11);
	s2->set_material(new material_mirror());
	s2->set_texture(new texture_solid(colorRGB(0.8, 0.2, 0.8)));

	s3 = new surface_plane(point3D(0, -3, 0), vector3D(0, 1, 0));
	s3->set_material(new material_matte());
	s3->set_texture(new texture_checker(4, true));

	surface_glteapot *s7 = new surface_glteapot();
	s7->apply_transform(transform::translate(-4, -3, -3));
	s7->set_material(new material_transparent(color::white / 1.2, color::white / 1.2, 0.8));
	s7->set_texture(new texture_solid(color::skyblue));

	surface_glteapot *s8 = new surface_glteapot();
	s8->apply_transform(transform::translate(3, -3, 3));
	s8->set_material(new material_transparent(color::white / 1.2, color::white / 1.2, 0.8));
	s8->set_texture(new texture_solid(color::palegreen));

	l1 = new light_area(point3D(0, 20, 20), color::white / 1.8, 3, vector3D(0, 20, 10));
	// l1->set_spot(true, vector3D(30, 9, -30), pi / 3, 5);
	l2 = new light_point(point3D(0, 40, 0), color::white / 3);

	wld.set_ambient(color::white / 8);
 	wld.set_sampler(new sampler_jittered(9));
	wld.set_camera(cam);
	wld.set_fog(new fog(0.01, 1, color::white));
	// wld.add_surface(s1);
	// wld.add_surface(s2);
	wld.add_surface(s3);
	wld.add_surface(s7);
	wld.add_surface(s8);
	wld.add_light(l1);
	wld.add_light(l2);
}
