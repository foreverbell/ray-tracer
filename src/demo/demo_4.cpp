
#include "demo.hpp"

using namespace ray_tracer;

void demo_4::set_world() {
	cam = new camera_pinhole(point3D(0, 1, -10), point3D(0, 0, 0), vector3D(0, 1, 0.1), atan(2.0), atan(2.0), false);

//	surface_plane *splane = new surface_plane(point3D(0, -10, 0), vector3D(0, 1, 0));
//	splane->set_material(new material_matte());
//	splane->set_texture(new texture_checker(4.0, true));

	surface_mesh *sbunny = new surface_noffmesh("../resource/bunny.noff");
	sbunny->apply_transform(transform::scale(0.07, 0.07, 0.07));
	sbunny->apply_transform(transform::rotate(1, pi));
	sbunny->apply_transform(transform::translate(0, -3, 0));
	sbunny->set_material(new material_transparent(color_white / 1.3, color_white / 1.3, 1.0));
	sbunny->set_texture(new texture_solid(color_silver));

	light *l = new light_point(point3D(0, 2, -10), color_white);
	l->set_shadow(false);

	wld.set_ambient(color_white / 5);
	wld.set_sampler(new sampler_jittered(4));
	wld.set_camera(cam);
//	wld.set_fog(new fog(0.01, 1, color_white));
//	wld.add_surface(splane);
	wld.set_skybox(new skybox("../resource/sunset-skybox/front.png", "../resource/sunset-skybox/back.png", "../resource/sunset-skybox/left.png", "../resource/sunset-skybox/right.png", "../resource/sunset-skybox/top.png", "../resource/sunset-skybox/bottom.png"));
	wld.add_surface(sbunny);
	wld.add_light(l);
}
