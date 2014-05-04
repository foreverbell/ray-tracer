TARGET = rt

FILES = BRDF.cpp BRDF_lambertian.cpp BRDF_phong.cpp BRDF_reflection.cpp \
	camera.cpp camera_fisheye.cpp camera_orthographic.cpp camera_pinhole.cpp camera_thinlens.cpp \
	colorRGB.cpp \
	convexhull.cpp \
	fog.cpp \
	hit_info.cpp \
	image.cpp image_bmp.cpp \
	light.cpp light_area.cpp light_point.cpp light_reflect.cpp \
	main.cpp demo/demo_1.cpp demo/demo_2.cpp demo/demo_3.cpp demo/demo_4.cpp \
	material.cpp material_matte.cpp material_mirror.cpp material_phong.cpp \
	matrix3D.cpp matrix4D.cpp \
	point2D.cpp point3D.cpp \
	polyvertex.cpp \
	quadratic.cpp \
	ray.cpp \
	sampler.cpp sampler_jittered.cpp sampler_random.cpp sampler_single.cpp \
	surface.cpp surface_compound.cpp surface_convexhull.cpp surface_disk.cpp surface_glteapot.cpp surface_plane.cpp surface_plymesh.cpp surface_quadratic.cpp surface_regpolyhedron.cpp surface_sphere.cpp surface_triangle.cpp surface_tricompound.cpp \
	texture.cpp texture_checker.cpp texture_image.cpp texture_mapping.cpp texture_mapping_sphere.cpp texture_solid.cpp \
	tracer.cpp \
	transformation.cpp transformation_reflect.cpp transformation_rotate.cpp transformation_scale.cpp transformation_translate.cpp \
	vector2D.cpp vector3D.cpp \
	world.cpp \
	../ply-1.1/plyfile.c

CFLAGS = `sdl-config --cflags` -g -O2 -Wall -std=c++0x
LDFLAGS = `sdl-config --libs` -lstdc++ -lm -ldl

$(TARGET):

	gcc $(CFLAGS) -o $(TARGET) $(FILES) $(LDFLAGS)

clean:
	rm -f $(TARGET)
