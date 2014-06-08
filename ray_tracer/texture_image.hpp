#ifndef __TEXTURE_IMAGE_HPP__
#define __TEXTURE_IMAGE_HPP__

#include "texture.hpp"
#include "image.hpp"
#include "shade_context.hpp"

namespace ray_tracer {
	class texture_image : public texture {
	public:
		texture_image(const image *);
		colorRGB texture_shade(shade_context *) const;
	private:
		const image *image_ptr;
	};
}

#endif