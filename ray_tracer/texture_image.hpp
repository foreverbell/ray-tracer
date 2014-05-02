#ifndef __TEXTURE_IMAGE_HPP__
#define __TEXTURE_IMAGE_HPP__

#include "texture.hpp"
#include "image.hpp"
#include "texture_mapping.hpp"

namespace ray_tracer {
	class texture_image : public texture {
	public:
		texture_image(const image *, const texture_mapping *);
		colorRGB texture_shade(hit_info *) const;
	private:
		const image *image_ptr;
		const texture_mapping *mapping_ptr;
	};
}

#endif