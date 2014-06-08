
#include "demo.hpp"

using namespace ray_tracer;

void demo_2::set_world() {
	surface *s;
	material *m;
	texture *t;
	light *l;

	// cam = new camera_pinhole(point3D(0, 0, 0), point3D(20, 0, 0), vector3D(0, 0, 1), atan(2), atan(2), true);
	cam = new camera_orthographic(point3D(0, 0, 0), point3D(20, 0, 0), vector3D(0, 0, 1), 40, 40);

	s = new surface_sphere(point3D(20, 0, 0), 10);
	s->set_transform_center(point3D(20, 0, 0));
	s->apply_transform(transform_rotate(point3D(0, 0, 0), vector3D(0, 0, 1), PI));
	s->apply_transform(transform_rotate(point3D(0, 0, 0), vector3D(-10, 0, 0), -PI / 18));
	
	m = new material_matte(color_white);
	t = new texture_image(image_file_create("demo/earth_texture.bmp", image_type_bmp));
	s->set_material(m);
	s->set_texture(t);

	l = new light_point(point3D(-20, 0, 5), color_white);
	l->set_shadow(false);

	wld.set_ambient(color_white / 10);
	wld.set_camera(cam);
	wld.add_surface(s);
	wld.add_light(l);
}

bool demo_2::keybd(keybd_code code) {
	if (code == left) {
		cam->rotate(PI / 50);
		return true;
	} else if (code == right) {
		cam->rotate(-PI / 50);
		return true;
	}
	return false;
}