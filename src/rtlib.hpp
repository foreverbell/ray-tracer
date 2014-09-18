#ifndef __RTLIB_HPP__
#define __RTLIB_HPP__

#include "world.hpp"
#include "colorRGB.hpp"
#include "vector3D.hpp"
#include "point3D.hpp"
#include "vector2D.hpp"
#include "point2D.hpp"
#include "image.hpp"
#include "transform.hpp"
#include "sampler.hpp"

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
#include "light_parallel.hpp"
/// }}}

/// {{{ headers for material
#include "material.hpp"
#include "material_phong.hpp"
#include "material_matte.hpp"
#include "material_mirror.hpp"
#include "material_transparent.hpp"
#include "material_artistic.hpp"
/// }}}

/// {{{ headers for surface
#include "surface.hpp"
#include "surface_convexhull.hpp"
#include "surface_flat.hpp"
#include "surface_glteapot.hpp"
#include "surface_quadratic.hpp"
#include "surface_regpolyhedron.hpp"
#include "surface_sphere.hpp"
#include "surface_mobius.hpp"
#include "surface_fractal_terrain.hpp"
#include "surface_csg.hpp"
/// }}}

/// {{{ headers for texture
#include "texture.hpp"
#include "texture_checker.hpp"
#include "texture_image.hpp"
#include "texture_solid.hpp"
/// }}}

#endif