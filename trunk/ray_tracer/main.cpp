
#include <thread>
#include <Windows.h>
#include <SDL.h>
#include "rtlib.hpp"

using namespace ray_tracer;

const int width = 350, height = 350, max_thread_count = 4;

void render_callback(int x, int y, const colorRGB &color, void *pixel_ptr) {
	char *p = (char *)pixel_ptr;

	p += (y * width + x) << 2;
	*p++ = static_cast<uint8_t>(color.b * 255);
	*p++ = static_cast<uint8_t>(color.g * 255);
	*p++ = static_cast<uint8_t>(color.r * 255);
}

void render(world &world, SDL_Surface *screen) {
	if (SDL_MUSTLOCK(screen)) {
		if (SDL_LockSurface(screen) < 0) {
			printf("Couldn't lock the screen: %s.\n", SDL_GetError());
			return;
		}
	}
	world.render_begin(width, height, render_callback, screen->pixels);
	std::thread thr[max_thread_count];
	for (int i = 0; i < max_thread_count; i += 1) {
		thr[i] = std::thread([&]{ world.render_scene(); });
	}
	for (int i = 0; i < max_thread_count; i += 1) {
		thr[i].join();
	}
	if (SDL_MUSTLOCK(screen)) {
		SDL_UnlockSurface(screen);
	}
	SDL_UpdateRect(screen, 0, 0, width, height);
	SDL_SaveBMP(screen, "D:\\a.bmp");
}

/*
bool in_sierpinski(int depth, const point2D &v1, const point2D &v2, const point2D &v3, const point2D &v0) {
	if (dblcmp((v2 - v1) ^ (v0 - v1)) < 0) return false;
	if (dblcmp((v3 - v2) ^ (v0 - v2)) < 0) return false;
	if (dblcmp((v1 - v3) ^ (v0 - v3)) < 0) return false;
	if (depth == 0) return true;
	point2D v4 = (v1 + v2) / 2, v5 = (v2 + v3) / 2, v6 = (v3 + v1) / 2;
	if (in_sierpinski(depth - 1, v1, v4, v6, v0)) return true;
	if (in_sierpinski(depth - 1, v4, v2, v5, v0)) return true;
	if (in_sierpinski(depth - 1, v6, v5, v3, v0)) return true;
	return false;
}

const double triradius = 25, sqrt3 = sqrt(3);

bool func(double x, double y) {
	return in_sierpinski(5, point2D(0, triradius), point2D(-triradius * sqrt3 / 2, -triradius / 2), point2D(triradius * sqrt3 / 2, -triradius / 2), point2D(x, y));
}
*/

void test1(SDL_Surface *screen) {
	world world;
	camera *cam;
	surface *s1, *s2, *s3, *s5;
	surface_quadratic *s4;
	surface_compound *sc;
	// material_matte *m1;
	material_mirror *m1;
	material_mirror *m2;
	material_matte *m3;
	texture *t1, *t2, *t3, *t4;
	light *l, *l2;

	// cam = new camera_fisheye(point3D(0, 0, 0), point3D(1, 0, 0), vector3D(0, 0, 1), PI / 2);
	// cam = new camera_thinlens(point3D(-10, 0, 0), point3D(1, 0, 0), vector3D(0, 0, 1), atan(2.0), atan(2.0), 35, 3.5, true);
	// cam = new camera_orthographic(point3D(0, 0, 0), point3D(1, 0, 0), vector3D(0, 0, 1), 40, 40);
	cam = new camera_pinhole(point3D(-10, 0, 0), point3D(1, 0, 0), vector3D(0, 0, 1), atan(2.0), atan(2.0), true);
	// cam->rotate(PI / 4);

	s1 = new surface_sphere(point3D(15, -7, 0), 9);
	// m1 = new material_matte;
	m1 = new material_mirror(colorRGB(0.2, 0.6, 0.8));
	t1 = new texture_solid(colorRGB(0.2, 0.6, 0.8));
	s1->set_material(m1);
	s1->set_texture(t1);
	s2 = new surface_sphere(point3D(30, 9, 0), 11);
	// m2 = new material_phong;
	// m2->set_specular_shininess(50);
	m2 = new material_mirror(colorRGB(0.8, 0.2, 0.8));
	t2 = new texture_solid(colorRGB(0.8, 0.2, 0.8));

	s2->set_material(m2);
	s2->set_texture(t2);

	s3 = new surface_plane(point3D(10, 0, -10), vector3D(0, 0, 1));
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

	std::vector<point3D> vertices;
	vertices.push_back(point3D(0, 5, -10));
	vertices.push_back(point3D(10, 5, -10));
	vertices.push_back(point3D(0, 15, -10));
	vertices.push_back(point3D(10, 15, -10));
	vertices.push_back(point3D(0, 5, 0));
	vertices.push_back(point3D(10, 5, 0));
	vertices.push_back(point3D(0, 15, 0));
	vertices.push_back(point3D(10, 15, 0));
	surface_convexhull *s6 = new surface_convexhull(vertices);
	s6->set_material(m1);
	s6->set_texture(t1);

	// surface_regpolyhedron *s7 = new surface_regpolyhedron(5, point3D(5, 5, -5), 4, 1);
	// surface_glteapot *s7 = new surface_glteapot();
	surface_plymesh *s7 = new surface_plymesh("D:\\bun_zipper.ply");
	s7->apply_transformation(transformation_scale(65, 65, 65));
	s7->apply_transformation(transformation_rotate('x', -PI / 2));
	s7->apply_transformation(transformation_rotate('z', PI / 2));
	s7->apply_transformation(transformation_reflect('y'));
	s7->apply_transformation(transformation_translate(0, 0, -8));
	

	s7->set_material(m3);
	s7->set_texture(t1);

	surface_regpolyhedron *s8 = new surface_regpolyhedron(5, point3D(5, -5, -5), 20);
	s8->set_material(m3);
	s8->set_texture(t2);

	// l = new light_point(point3D(0, 0, 0), color_white);
	l = new light_point(point3D(-20, 0, 10), color_white);
	// l->set_spot(true, vector3D(30, 9, -30), PI / 3, 5);
	l->set_attenuation(true, 1, 0.0001, 0.00005);
	l2 = new light_point(point3D(-10, 0, 30), color_white);
	l2->set_attenuation(true, 1, 0.0001, 0.00005);

	world.set_ambient(color_white / 5);
	world.set_sampler(new sampler_jittered(16));
	world.set_camera(cam);
	world.set_fog(new fog(0.01, 1, color_white));
	//world.add_surface(s1);
	//world.add_surface(s2);
	world.add_surface(s3);
	// world.add_surface(sc);
	world.add_surface(s7);
	// world.add_surface(s8);
	world.add_light(l);
	//	world.add_light(l2);

	render(world, screen);
}

void test2(SDL_Surface *screen) {
	world world;
	camera *cam;
	surface *s;
	material *m;
	texture *t;
	light *l;

	cam = new camera_pinhole(point3D(0, 0, 0), point3D(1, 0, 0), vector3D(0, 0, 1), atan(2), atan(2), true);
	// cam = new camera_orthographic(point3D(0, 0, 0), point3D(1, 0, 0), vector3D(0, 0, 1), 40, 40);

	s = new surface_sphere(point3D(25, 0, 0), 10);
	m = new material_matte(color_white);
	t = new texture_image(image_file_create("C:\\Users\\ForeverBell\\Desktop\\earth.bmp", image_type_bmp), new texture_mapping_sphere());
	s->set_material(m);
	s->set_texture(t);

	l = new light_point(point3D(0, 0, 0), color_white);
	l->set_shadow(false);

	world.set_ambient(color_black);
	world.set_sampler(new sampler_jittered(25));
	world.set_camera(cam);
	world.add_surface(s);
	world.add_light(l);

	render(world, screen);
}

void test3(SDL_Surface *screen) {
	world world;
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

	world.set_ambient(color_white / 5);
	// world.set_sampler(new sampler_jittered(25));
	world.set_camera(cam);
	world.add_surface(s);
	world.add_light(l);

	render(world, screen);
}

int main() {
	if (SDL_Init(SDL_INIT_VIDEO) == -1) { 
		printf("Could not initialize SDL: %s.\n", SDL_GetError());
		return 0;
	}

	SDL_Surface *screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
	if (screen == NULL) {
		printf("Couldn't set destination video mode: %s.\n", SDL_GetError());
		return 0;
	}

	DWORD old_time = GetTickCount();
	test1(screen);
	printf("Total time used: %dms.\n", GetTickCount() - old_time);

	SDL_Event event;
	while (SDL_WaitEvent(&event));
	SDL_Quit();
	return 0;
}
