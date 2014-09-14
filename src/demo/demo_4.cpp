
#include "demo.hpp"

using namespace ray_tracer;

void demo_4::set_world() {
	cam = new camera_pinhole(point3D(0, 2, -10), point3D(0, 0, 0), vector3D(0, 1, 0.2), atan(2.0), atan(2.0), true);

//	surface_plane *splane = new surface_plane(point3D(0, -10, 0), vector3D(0, 1, 0));
//	splane->set_material(new material_matte());
//	splane->set_texture(new texture_checker());

	surface_mesh *sbunny = new surface_noffmesh("../resource/bunny.noff");
	sbunny->apply_transform(transform_scale(0.07, 0.07, 0.07));
	sbunny->apply_transform(transform_rotate('y', pi));
	sbunny->apply_transform(transform_translate(0, -3, 0));
	sbunny->set_material(new material_transparent(color_white / 2, color_white / 2, 1.0));
	sbunny->set_texture(new texture_solid(color_silver));

	light *l = new light_point(point3D(0, 10, -20), color_white);
	l->set_shadow(false);

	wld.set_ambient(color_white / 5);
	wld.set_sampler(new sampler_jittered(4));
	wld.set_camera(cam);
//	wld.set_fog(new fog(0.01, 1, color_white));
//	wld.add_surface(splane);
	wld.set_skybox(new skybox("../resource/sunset-skybox/front.bmp", "../resource/sunset-skybox/back.bmp", "../resource/sunset-skybox/left.bmp", "../resource/sunset-skybox/right.bmp", "../resource/sunset-skybox/top.bmp", "../resource/sunset-skybox/bottom.bmp"));
	wld.add_surface(sbunny);
	wld.add_light(l);
}
