#ifndef __TEXTURE_IMAGE_HPP__
#define __TEXTURE_IMAGE_HPP__

#include "texture.hpp"
#include "image.hpp"
#include "shade_context.hpp"
#include "miscellaneous.hpp"
#include <memory>

namespace ray_tracer {

	class texture_image : public texture {
	public:
		texture_image(fname_ptr_t);
		colorRGB texture_shade(shade_context *) const;
	private:
		std::shared_ptr<image> image_ptr;
	};
}

#endif