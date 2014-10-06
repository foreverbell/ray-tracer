
#include "demo.hpp"

using namespace ray_tracer;

void demo_7::set_world() {
	FILE *f = fopen("../resource/4LDB.spheres", "r");
	int n;
	
	fscanf(f, "%d", &n);
	for (int i = 0; i < n; ++i) {
		point3D center;
		double radius;

		fscanf(f, "%lf%lf%lf%lf", &center.x, &center.y, &center.z, &radius);
		surface_sphere *sphere = new surface_sphere(center, radius);
		sphere->set_material(new material_matte());
		sphere->set_texture(new texture_solid(color_red));
		wld.add_surface(sphere);
	}

	cam = new camera_pinhole(point3D(-10, -40, -70), point3D(-10, -40, 0), vector3D(0, 1, 0), atan(2.0), atan(2.0), true);

	light *l = new light_point(point3D(-10, -40, -70), color_white);
	wld.add_light(l);

	// wld.set_ambient(color_white / 5);
	wld.set_sampler(new sampler_jittered(16));
	wld.set_silhouette(1.5);
	wld.set_camera(cam);
}
