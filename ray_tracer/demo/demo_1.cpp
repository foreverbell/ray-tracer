
#include "demo.hpp"

using namespace ray_tracer;

void demo_1::set_world() {
	surface *s1, *s2, *s3, *s5;
	surface_quadratic *s4;
	surface_compound *sc;
	material_mirror *m1;
	material_mirror *m2;
	material_matte *m3;
	texture *t1, *t2, *t3, *t4;
	light *l1, *l2;

	// cam = new camera_fisheye(point3D(0, 0, 0), point3D(1, 0, 0), vector3D(0, 0, 1), PI / 2);
	// cam = new camera_thinlens(point3D(-10, 0, 0), point3D(1, 0, 0), vector3D(0, 0, 1), atan(2.0), atan(2.0), 35, 3.5, true);
	// cam = new camera_orthographic(point3D(-10, 0, 0), point3D(1, 0, 0), vector3D(0, 0, 1), 40, 40);
	cam = new camera_pinhole(point3D(-10, 0, 0), point3D(1, 0, 0), vector3D(0, 0, 1), atan(2.0), atan(2.0), true);
	// cam->rotate(PI / 4);

	s1 = new surface_sphere(point3D(15, -7, 0), 9);
	m1 = new material_mirror(color_azure);
	t1 = new texture_solid(color_azure);
	s1->set_material(m1);
	s1->set_texture(t1);
	s2 = new surface_sphere(point3D(30, 9, 0), 11);
	// m2 = new material_phong;
	// m2->set_specular_shininess(50);
	m2 = new material_mirror(colorRGB(0.8, 0.2, 0.8));
	t2 = new texture_solid(colorRGB(0.8, 0.2, 0.8));

	s2->set_material(m2);
	s2->set_texture(t2);

	s3 = new surface_plane(point3D(0, 0, -3), vector3D(0, 0, 1));
	m3 = new material_matte;
	s3->set_material(m3);
	t3 = new texture_checker;
	s3->set_texture(t3);

	s4 = new surface_quadratic();
	s4->coef_xx = 1, s4->coef_yy = 1, s4->coef_y = -5, s4->coef_const = -8;
	s4->set_range_z(-10, -2);
	s5 = new surface_disk(point3D(0, 2.5, -2), vector3D(0, 0, 1), 3.77491);
	sc = new surface_compound();
	sc->add_surface(s4);
	sc->add_surface(s5);
	t4 = new texture_solid(colorRGB(0.7, 0.7, 0.0));
	sc->set_material(m2);
	sc->set_texture(t4);

	surface_glteapot *s7 = new surface_glteapot();
	s7->apply_transformation(transformation_translate(-3, -3, 0));
	s7->set_material(new material_mirror(color_skyblue));
	s7->set_texture(new texture_solid(color_skyblue));

	surface_glteapot *s8 = new surface_glteapot();
	s8->apply_transformation(transformation_translate(3, 3, 0));
	s8->set_material(new material_mirror(color_palegreen));
	s8->set_texture(new texture_solid(color_palegreen));

	l1 = new light_area(point3D(-20, 0, 10), color_white / 1.8, 3, vector3D(20, 0, -10));
	// l1->set_spot(true, vector3D(30, 9, -30), PI / 3, 5);
	l1->set_attenuation(true, 1, 0.0001, 0.00005);
	l2 = new light_point(point3D(0, 0, 30), color_white / 5);
	l2->set_attenuation(true, 1, 0.0001, 0.00005);

	wld.set_ambient(color_white / 5);
	wld.set_sampler(new sampler_jittered(16));
	wld.set_camera(cam);
	wld.set_fog(new fog(0.01, 1, color_white));
	// wld.add_surface(s1);
	// wld.add_surface(s2);
	wld.add_surface(s3);
	// wld.add_surface(sc);
	wld.add_surface(s7);
	wld.add_surface(s8);
	wld.add_light(l1);
	wld.add_light(l2);
}