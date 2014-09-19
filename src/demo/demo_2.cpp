
#include "demo.hpp"

using namespace ray_tracer;

void demo_2::set_world() {
	surface *s;
	material *m;
	texture *t;
	light *l;

	cam = new camera_pinhole(point3D(0, 0, -30), point3D(0, 0, 20), vector3D(0, 1, 0), atan(1), atan(1), true);
	// cam = new camera_orthographic(point3D(0, 0, 0), point3D(0, 0, 20), vector3D(0, 1, 0), 40, 40);

	s = new surface_sphere(point3D(0, 0, 20), 10);
	s->set_trancenter(point3D(0, 0, 20));
	s->apply_transform(transform_rotate(point3D(0, 0, 0), vector3D(1, 0, 0), -pi / 2));
	s->apply_transform(transform_reflect('x'));
	s->apply_transform(transform_rotate(point3D(0, 0, 0), vector3D(0, 1, 0), -pi / 1.8));
	//s->apply_transform(transform_rotate(point3D(0, 0, 0), vector3D(-10, 0, 0), -pi / 18));
	
	m = new material_matte(color_white);
	t = new texture_image("../resource/earth_texture.png");
	s->set_material(m);
	s->set_texture(t);

	l = new light_point(point3D(0, 5, -20), color_white);
	l->set_shadow(false);

	wld.set_ambient(color_white / 10);
	wld.set_skybox(new skybox("../resource/spheremapgalaxyasteroid.png"));
	wld.set_camera(cam);
	wld.add_surface(s);
	wld.add_light(l);
}

bool demo_2::keybd(keybd_code code) {
	if (code == keybd_code::left) {
		cam->rotate(pi / 100);
		return true;
	} else if (code == keybd_code::right) {
		cam->rotate(-pi / 100);
		return true;
	}
	return false;
}
