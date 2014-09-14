#ifndef __SKYBOX_HPP__
#define __SKYBOX_HPP__

#include "miscellaneous.hpp"
#include "image.hpp"
#include "shade_context.hpp"
#include "colorRGB.hpp"

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
		colorRGB skybox_shade(shade_context *) const;
	private:
		const image *texture_front_ptr, *texture_back_ptr;
		const image *texture_left_ptr, *texture_right_ptr;
		const image *texture_top_ptr, *texture_bottom_ptr;
	};
}

#endif