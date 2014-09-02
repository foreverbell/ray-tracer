
#include <vector>
#include "ray.hpp"
#include "surface_plymesh.hpp"
#include "../lib/ply-1.1/ply.h"

namespace ray_tracer {
	typedef struct Vertex {
		float x,y,z;             /* the usual 3-space position of a vertex */
	} Vertex;

	typedef struct Face {
		unsigned char nverts;    /* number of vertex indices in list */
		int *verts;              /* vertex index list */
	} Face;

	PlyProperty vert_props[] = { /* list of property information for a vertex */
		{"x", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex, x), 0, 0, 0, 0},
		{"y", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex, y), 0, 0, 0, 0},
		{"z", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex, z), 0, 0, 0, 0},
	};

	PlyProperty face_props[] = { /* list of property information for a vertex */
		{"vertex_indices", PLY_INT, PLY_INT, offsetof(Face, verts),
		1, PLY_UCHAR, PLY_UCHAR, offsetof(Face, nverts)},
	};

	surface_plymesh::surface_plymesh(const char *filename) {
		PlyFile *ply_ptr;
		int nelems;
		char **elist_ptr;
		int file_type;
		float version;
		std::vector<point3D> vertices;
		std::vector<std::pair<int, int *> > faces;

		ply_ptr = ply_open_for_reading((char *)filename, &nelems, &elist_ptr, &file_type, &version);
		for (int i = 0; i < nelems; ++i) {
			char *elem_name = elist_ptr[i];
			int nprops, num_elems;
			PlyProperty **plist_ptr = ply_get_element_description(ply_ptr, elem_name, &num_elems, &nprops);

			if (equal_strings("vertex", elem_name)) {
				Vertex vert;
				vertices.reserve(num_elems);
				ply_get_property(ply_ptr, elem_name, &vert_props[0]);
				ply_get_property(ply_ptr, elem_name, &vert_props[1]);
				ply_get_property(ply_ptr, elem_name, &vert_props[2]);
				for (int j = 0; j < num_elems; ++j) {
					ply_get_element(ply_ptr, &vert);
					vertices.push_back(point3D(vert.x, vert.y, vert.z));
				}
			} else if (equal_strings("face", elem_name)) {
				Face face;
				faces.reserve(num_elems);
				ply_get_property(ply_ptr, elem_name, &face_props[0]);
				for (int j = 0; j < num_elems; ++j) {
					ply_get_element(ply_ptr, &face);
					faces.push_back(std::make_pair(face.nverts, face.verts));
				}
			}
		}
		ply_close(ply_ptr);
		for (std::vector<std::pair<int, int *> >::iterator it = faces.begin(); it != faces.end(); ++it) {
			int nverts = it->first;
			int *vert_ptr = it->second;
			for (int i = 1; i < nverts - 1; ++i) {
				add_surface(surface_triangle(vertices[vert_ptr[0]], vertices[vert_ptr[i]], vertices[vert_ptr[i + 1]]));
			}
		}
		setup();
	}
}
