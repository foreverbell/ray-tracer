
#include "demo.hpp"

using namespace ray_tracer;

void demo_4::set_world() {
	cam = new camera_pinhole(point3D(-10, 0, 2), point3D(0, 0, 0), vector3D(0.2, 0, 1), atan(2.0), atan(2.0), true);

	surface_plane *splane = new surface_plane(point3D(10, 0, -10), vector3D(0, 0, 1));
	splane->set_material(new material_matte());
	splane->set_texture(new texture_checker());

	surface_plymesh *sbunny = new surface_plymesh("demo/stanford_bunny.ply");
	sbunny->apply_transformation(transformation_scale(65, 65, 65));
	sbunny->apply_transformation(transformation_rotate('x', -PI / 2));
	sbunny->apply_transformation(transformation_rotate('z', PI / 2));
	sbunny->apply_transformation(transformation_reflect('y'));
	sbunny->apply_transformation(transformation_translate(0, 2, -8));
	sbunny->set_material(new material_matte());
	sbunny->set_texture(new texture_solid(colorRGB(0.2, 0.6, 0.8)));

	light *l = new light_point(point3D(-20, 0, 10), color_white);
	l->set_spot(true, vector3D(30, 9, -30), PI / 3, 5);
	l->set_attenuation(true, 1, 0.0001, 0.00005);

	wld.set_ambient(color_white / 5);
	wld.set_sampler(new sampler_jittered(4));
	wld.set_camera(cam);
	wld.set_fog(new fog(0.01, 1, color_white));
	wld.add_surface(splane);
	wld.add_surface(sbunny);
	wld.add_light(l);
}