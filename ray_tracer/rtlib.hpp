#ifndef __RTLIB_HPP__
#define __RTLIB_HPP__

#include "world.hpp"
#include "colorRGB.hpp"
#include "vector3D.hpp"
#include "point3D.hpp"
#include "vector2D.hpp"
#include "point2D.hpp"
#include "image.hpp"

/// {{{ headers for camera
#include "camera.hpp"
#include "camera_fisheye.hpp"
#include "camera_orthographic.hpp"
#include "camera_pinhole.hpp"
#include "camera_thinlens.hpp"
/// }}}

/// {{{ headers for light
#include "light.hpp"
#include "light_point.hpp"
#include "light_area.hpp"
/// }}}

/// {{{ headers for material
#include "material.hpp"
#include "material_phong.hpp"
#include "material_matte.hpp"
#include "material_mirror.hpp"
#include "material_transparent.hpp"
/// }}}

/// {{{ headers for sampler
#include "sampler.hpp"
#include "sampler_random.hpp"
#include "sampler_jittered.hpp"
#include "sampler_single.hpp"
/// }}}

/// {{{ headers for surface
#include "surface.hpp"
#include "surface_compound.hpp"
#include "surface_convexhull.hpp"
#include "surface_disk.hpp"
#include "surface_glteapot.hpp"
#include "surface_plane.hpp"
#include "surface_plymesh.hpp"
#include "surface_quadratic.hpp"
#include "surface_regpolyhedron.hpp"
#include "surface_sphere.hpp"
#include "surface_triangle.hpp"
#include "surface_tricompound.hpp"
/// }}}

/// {{{ headers for texture & mapping
#include "texture.hpp"
#include "texture_checker.hpp"
#include "texture_image.hpp"
#include "texture_solid.hpp"

#include "texture_mapping.hpp"
#include "texture_mapping_sphere.hpp"
/// }}}

/// {{{ headers for transform
#include "transform.hpp"
#include "transform_reflect.hpp"
#include "transform_rotate.hpp"
#include "transform_scale.hpp"
#include "transform_translate.hpp"
/// }}}

#endif