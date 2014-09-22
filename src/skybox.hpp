#ifndef __SKYBOX_HPP__
#define __SKYBOX_HPP__

#include "miscellaneous.hpp"
#include "image.hpp"
#include "shade_context.hpp"
#include "colorRGB.hpp"
#include <memory>

namespace ray_tracer {

	/* Skybox is centered at camera's position. */
	/* +x right, +y top, +z back */

	class skybox {
	public:
		// front, back, left, right, top, bottom
		//  5
		// 3142
		//  6
		skybox(fname_ptr_t, fname_ptr_t, fname_ptr_t, fname_ptr_t, fname_ptr_t, fname_ptr_t);
		skybox(fname_ptr_t);
		colorRGB skybox_shade(shade_context *) const;
	private:
		std::shared_ptr<image> texture_union_ptr;
		std::shared_ptr<image> texture_front_ptr, texture_back_ptr;
		std::shared_ptr<image> texture_left_ptr, texture_right_ptr;
		std::shared_ptr<image> texture_top_ptr, texture_bottom_ptr;
	};
}

#endif