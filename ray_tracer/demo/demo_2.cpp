
#include "demo.hpp"

using namespace ray_tracer;

void demo_2::set_world() {
	camera *cam;
	surface *s;
	material *m;
	texture *t;
	light *l;

	cam = new camera_pinhole(point3D(0, 0, 0), point3D(20, 0, 0), vector3D(0, 0, 1), atan(2), atan(2), true);
	// cam = new camera_orthographic(point3D(0, 0, 0), point3D(20, 0, 0), vector3D(0, 0, 1), 40, 40);
	cam->rotate(PI / 4);

	s = new surface_sphere(point3D(20, 0, 0), 10);
	m = new material_matte(color_white);
	t = new texture_image(image_file_create("earth.bmp", image_type_bmp), new texture_mapping_sphere());
	s->set_material(m);
	s->set_texture(t);

	l = new light_point(point3D(0, 0, 0), color_white);
	l->set_shadow(false);

	wld.set_ambient(color_black);
	wld.set_sampler(new sampler_jittered(25));
	wld.set_camera(cam);
	wld.add_surface(s);
	wld.add_light(l);
}
