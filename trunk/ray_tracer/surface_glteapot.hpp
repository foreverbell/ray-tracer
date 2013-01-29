/*
* (c) Copyright 1993, Silicon Graphics, Inc.
*
* ALL RIGHTS RESERVED
*
* Permission to use, copy, modify, and distribute this software
* for any purpose and without fee is hereby granted, provided
* that the above copyright notice appear in all copies and that
* both the copyright notice and this permission notice appear in
* supporting documentation, and that the name of Silicon
* Graphics, Inc. not be used in advertising or publicity
* pertaining to distribution of the software without specific,
* written prior permission.
*
* THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU
* "AS-IS" AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR
* OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
* MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  IN NO
* EVENT SHALL SILICON GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE
* ELSE FOR ANY DIRECT, SPECIAL, INCIDENTAL, INDIRECT OR
* CONSEQUENTIAL DAMAGES OF ANY KIND, OR ANY DAMAGES WHATSOEVER,
* INCLUDING WITHOUT LIMITATION, LOSS OF PROFIT, LOSS OF USE,
* SAVINGS OR REVENUE, OR THE CLAIMS OF THIRD PARTIES, WHETHER OR
* NOT SILICON GRAPHICS, INC.  HAS BEEN ADVISED OF THE POSSIBILITY
* OF SUCH LOSS, HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* ARISING OUT OF OR IN CONNECTION WITH THE POSSESSION, USE OR
* PERFORMANCE OF THIS SOFTWARE.
*
* US Government Users Restricted Rights
*
* Use, duplication, or disclosure by the Government is subject to
* restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
* (c)(1)(ii) of the Rights in Technical Data and Computer
* Software clause at DFARS 252.227-7013 and/or in similar or
* successor clauses in the FAR or the DOD or NASA FAR
* Supplement.  Unpublished-- rights reserved under the copyright
* laws of the United States.  Contractor/manufacturer is Silicon
* Graphics, Inc., 2011 N.  Shoreline Blvd., Mountain View, CA
* 94039-7311.
*
* OpenGL(TM) is a trademark of Silicon Graphics, Inc.
*/

#ifndef __SURFACE_GLTEAPOT_HPP__
#define __SURFACE_GLTEAPOT_HPP__

#include "surface.hpp"
#include "surface_tricompound.hpp"

namespace ray_tracer {

	/*
	* Submitted through the kind offices of Daniel Wagner (daniel@ims.tuwien.ac.at)
	*/

	/* 530 vertices */

	const int numVertices = 530;
	const float vertices[530][3] =  {
		2.1f, 3.6f, 0.0f, 
		2.071f, 3.711f, 0.0f, 
		2.105f, 3.748f, 0.0f, 
		2.174f, 3.711f, 0.0f, 
		2.25f, 3.6f, 0.0f, 
		1.937f, 3.6f, 0.8242f, 
		1.91f, 3.711f, 0.8128f, 
		1.942f, 3.748f, 0.8261f, 
		2.005f, 3.711f, 0.8532f, 
		2.076f, 3.6f, 0.8831f, 
		1.491f, 3.6f, 1.491f, 
		1.47f, 3.711f, 1.47f, 
		1.494f, 3.748f, 1.494f, 
		1.543f, 3.711f, 1.543f, 
		1.597f, 3.6f, 1.597f, 
		0.8242f, 3.6f, 1.937f, 
		0.8128f, 3.711f, 1.91f, 
		0.8261f, 3.748f, 1.942f, 
		0.8532f, 3.711f, 2.005f, 
		0.8831f, 3.6f, 2.076f, 
		0.0f, 3.6f, 2.1f, 
		0.0f, 3.711f, 2.071f, 
		0.0f, 3.748f, 2.105f, 
		0.0f, 3.711f, 2.174f, 
		0.0f, 3.6f, 2.25f, 
		-0.8812f, 3.6f, 1.937f, 
		-0.8368f, 3.711f, 1.91f, 
		-0.8332f, 3.748f, 1.942f, 
		-0.8541f, 3.711f, 2.005f, 
		-0.8831f, 3.6f, 2.076f, 
		-1.542f, 3.6f, 1.491f, 
		-1.492f, 3.711f, 1.47f, 
		-1.501f, 3.748f, 1.494f, 
		-1.544f, 3.711f, 1.543f, 
		-1.597f, 3.6f, 1.597f, 
		-1.956f, 3.6f, 0.8242f, 
		-1.918f, 3.711f, 0.8128f, 
		-1.944f, 3.748f, 0.8261f, 
		-2.006f, 3.711f, 0.8532f, 
		-2.076f, 3.6f, 0.8831f, 
		-2.1f, 3.6f, 0.0f, 
		-2.071f, 3.711f, 0.0f, 
		-2.105f, 3.748f, 0.0f, 
		-2.174f, 3.711f, 0.0f, 
		-2.25f, 3.6f, 0.0f, 
		-1.937f, 3.6f, -0.8242f, 
		-1.91f, 3.711f, -0.8128f, 
		-1.942f, 3.748f, -0.8261f, 
		-2.005f, 3.711f, -0.8532f, 
		-2.076f, 3.6f, -0.8831f, 
		-1.491f, 3.6f, -1.491f, 
		-1.47f, 3.711f, -1.47f, 
		-1.494f, 3.748f, -1.494f, 
		-1.543f, 3.711f, -1.543f, 
		-1.597f, 3.6f, -1.597f, 
		-0.8242f, 3.6f, -1.937f, 
		-0.8128f, 3.711f, -1.91f, 
		-0.8261f, 3.748f, -1.942f, 
		-0.8532f, 3.711f, -2.005f, 
		-0.8831f, 3.6f, -2.076f, 
		0.0f, 3.6f, -2.1f, 
		0.0f, 3.711f, -2.071f, 
		0.0f, 3.748f, -2.105f, 
		0.0f, 3.711f, -2.174f, 
		0.0f, 3.6f, -2.25f, 
		0.8242f, 3.6f, -1.937f, 
		0.8128f, 3.711f, -1.91f, 
		0.8261f, 3.748f, -1.942f, 
		0.8532f, 3.711f, -2.005f, 
		0.8831f, 3.6f, -2.076f, 
		1.491f, 3.6f, -1.491f, 
		1.47f, 3.711f, -1.47f, 
		1.494f, 3.748f, -1.494f, 
		1.543f, 3.711f, -1.543f, 
		1.597f, 3.6f, -1.597f, 
		1.937f, 3.6f, -0.8242f, 
		1.91f, 3.711f, -0.8128f, 
		1.942f, 3.748f, -0.8261f, 
		2.005f, 3.711f, -0.8532f, 
		2.076f, 3.6f, -0.8831f, 
		2.525f, 3.011f, 0.0f, 
		2.766f, 2.433f, 0.0f, 
		2.936f, 1.876f, 0.0f, 
		3.0f, 1.35f, 0.0f, 
		2.33f, 3.011f, 0.9912f, 
		2.551f, 2.433f, 1.086f, 
		2.708f, 1.876f, 1.152f, 
		2.767f, 1.35f, 1.178f, 
		1.793f, 3.011f, 1.793f, 
		1.964f, 2.433f, 1.964f, 
		2.084f, 1.876f, 2.084f, 
		2.13f, 1.35f, 2.13f, 
		0.9912f, 3.011f, 2.33f, 
		1.086f, 2.433f, 2.551f, 
		1.152f, 1.876f, 2.708f, 
		1.178f, 1.35f, 2.767f, 
		0.0f, 3.011f, 2.525f, 
		0.0f, 2.433f, 2.766f, 
		0.0f, 1.876f, 2.936f, 
		0.0f, 1.35f, 3.0f, 
		-0.9912f, 3.011f, 2.33f, 
		-1.086f, 2.433f, 2.551f, 
		-1.152f, 1.876f, 2.708f, 
		-1.178f, 1.35f, 2.767f, 
		-1.793f, 3.011f, 1.793f, 
		-1.964f, 2.433f, 1.964f, 
		-2.084f, 1.876f, 2.084f, 
		-2.13f, 1.35f, 2.13f, 
		-2.33f, 3.011f, 0.9912f, 
		-2.551f, 2.433f, 1.086f, 
		-2.708f, 1.876f, 1.152f, 
		-2.767f, 1.35f, 1.178f, 
		-2.525f, 3.011f, 0.0f, 
		-2.766f, 2.433f, 0.0f, 
		-2.936f, 1.876f, 0.0f, 
		-3.0f, 1.35f, 0.0f, 
		-2.33f, 3.011f, -0.9912f, 
		-2.551f, 2.433f, -1.086f, 
		-2.708f, 1.876f, -1.152f, 
		-2.767f, 1.35f, -1.178f, 
		-1.793f, 3.011f, -1.793f, 
		-1.964f, 2.433f, -1.964f, 
		-2.084f, 1.876f, -2.084f, 
		-2.13f, 1.35f, -2.13f, 
		-0.9912f, 3.011f, -2.33f, 
		-1.086f, 2.433f, -2.551f, 
		-1.152f, 1.876f, -2.708f, 
		-1.178f, 1.35f, -2.767f, 
		0.0f, 3.011f, -2.525f, 
		0.0f, 2.433f, -2.766f, 
		0.0f, 1.876f, -2.936f, 
		0.0f, 1.35f, -3.0f, 
		0.9912f, 3.011f, -2.33f, 
		1.086f, 2.433f, -2.551f, 
		1.152f, 1.876f, -2.708f, 
		1.178f, 1.35f, -2.767f, 
		1.793f, 3.011f, -1.793f, 
		1.964f, 2.433f, -1.964f, 
		2.084f, 1.876f, -2.084f, 
		2.13f, 1.35f, -2.13f, 
		2.33f, 3.011f, -0.9912f, 
		2.551f, 2.433f, -1.086f, 
		2.708f, 1.876f, -1.152f, 
		2.767f, 1.35f, -1.178f, 
		2.883f, 0.9053f, 0.0f, 
		2.625f, 0.5766f, 0.0f, 
		2.367f, 0.3533f, 0.0f, 
		2.25f, 0.225f, 0.0f, 
		2.659f, 0.9053f, 1.132f, 
		2.422f, 0.5766f, 1.03f, 
		2.184f, 0.3533f, 0.9291f, 
		2.076f, 0.225f, 0.8831f, 
		2.047f, 0.9053f, 2.047f, 
		1.864f, 0.5766f, 1.864f, 
		1.681f, 0.3533f, 1.681f, 
		1.597f, 0.225f, 1.597f, 
		1.132f, 0.9053f, 2.659f, 
		1.03f, 0.5766f, 2.422f, 
		0.9291f, 0.3533f, 2.184f, 
		0.8831f, 0.225f, 2.076f, 
		0.0f, 0.9053f, 2.883f, 
		0.0f, 0.5766f, 2.625f, 
		0.0f, 0.3533f, 2.367f, 
		0.0f, 0.225f, 2.25f, 
		-1.132f, 0.9053f, 2.659f, 
		-1.03f, 0.5766f, 2.422f, 
		-0.9291f, 0.3533f, 2.184f, 
		-0.8831f, 0.225f, 2.076f, 
		-2.047f, 0.9053f, 2.047f, 
		-1.864f, 0.5766f, 1.864f, 
		-1.681f, 0.3533f, 1.681f, 
		-1.597f, 0.225f, 1.597f, 
		-2.659f, 0.9053f, 1.132f, 
		-2.422f, 0.5766f, 1.03f, 
		-2.184f, 0.3533f, 0.9291f, 
		-2.076f, 0.225f, 0.8831f, 
		-2.883f, 0.9053f, 0.0f, 
		-2.625f, 0.5766f, 0.0f, 
		-2.367f, 0.3533f, 0.0f, 
		-2.25f, 0.225f, 0.0f, 
		-2.659f, 0.9053f, -1.132f, 
		-2.422f, 0.5766f, -1.03f, 
		-2.184f, 0.3533f, -0.9291f, 
		-2.076f, 0.225f, -0.8831f, 
		-2.047f, 0.9053f, -2.047f, 
		-1.864f, 0.5766f, -1.864f, 
		-1.681f, 0.3533f, -1.681f, 
		-1.597f, 0.225f, -1.597f, 
		-1.132f, 0.9053f, -2.659f, 
		-1.03f, 0.5766f, -2.422f, 
		-0.9291f, 0.3533f, -2.184f, 
		-0.8831f, 0.225f, -2.076f, 
		0.0f, 0.9053f, -2.883f, 
		0.0f, 0.5766f, -2.625f, 
		0.0f, 0.3533f, -2.367f, 
		0.0f, 0.225f, -2.25f, 
		1.132f, 0.9053f, -2.659f, 
		1.03f, 0.5766f, -2.422f, 
		0.9291f, 0.3533f, -2.184f, 
		0.8831f, 0.225f, -2.076f, 
		2.047f, 0.9053f, -2.047f, 
		1.864f, 0.5766f, -1.864f, 
		1.681f, 0.3533f, -1.681f, 
		1.597f, 0.225f, -1.597f, 
		2.659f, 0.9053f, -1.132f, 
		2.422f, 0.5766f, -1.03f, 
		2.184f, 0.3533f, -0.9291f, 
		2.076f, 0.225f, -0.8831f, 
		2.199f, 0.1424f, 0.0f, 
		1.927f, 0.07031f, 0.0f, 
		1.253f, 0.01934f, 0.0f, 
		0.0f, 0.0f, 0.0f, 
		2.029f, 0.1424f, 0.8631f, 
		1.777f, 0.07031f, 0.7562f, 
		1.156f, 0.01934f, 0.4919f, 
		1.561f, 0.1424f, 1.561f, 
		1.368f, 0.07031f, 1.368f, 
		0.8899f, 0.01934f, 0.8899f, 
		0.8631f, 0.1424f, 2.029f, 
		0.7562f, 0.07031f, 1.777f, 
		0.4919f, 0.01934f, 1.156f, 
		0.0f, 0.1424f, 2.199f, 
		0.0f, 0.07031f, 1.927f, 
		0.0f, 0.01934f, 1.253f, 
		-0.8631f, 0.1424f, 2.029f, 
		-0.7562f, 0.07031f, 1.777f, 
		-0.4919f, 0.01934f, 1.156f, 
		-1.561f, 0.1424f, 1.561f, 
		-1.368f, 0.07031f, 1.368f, 
		-0.8899f, 0.01934f, 0.8899f, 
		-2.029f, 0.1424f, 0.8631f, 
		-1.777f, 0.07031f, 0.7562f, 
		-1.156f, 0.01934f, 0.4919f, 
		-2.199f, 0.1424f, 0.0f, 
		-1.927f, 0.07031f, 0.0f, 
		-1.253f, 0.01934f, 0.0f, 
		-2.029f, 0.1424f, -0.8631f, 
		-1.777f, 0.07031f, -0.7562f, 
		-1.156f, 0.01934f, -0.4919f, 
		-1.561f, 0.1424f, -1.561f, 
		-1.368f, 0.07031f, -1.368f, 
		-0.8899f, 0.01934f, -0.8899f, 
		-0.8631f, 0.1424f, -2.029f, 
		-0.7562f, 0.07031f, -1.777f, 
		-0.4919f, 0.01934f, -1.156f, 
		0.0f, 0.1424f, -2.199f, 
		0.0f, 0.07031f, -1.927f, 
		0.0f, 0.01934f, -1.253f, 
		0.8631f, 0.1424f, -2.029f, 
		0.7562f, 0.07031f, -1.777f, 
		0.4919f, 0.01934f, -1.156f, 
		1.561f, 0.1424f, -1.561f, 
		1.368f, 0.07031f, -1.368f, 
		0.8899f, 0.01934f, -0.8899f, 
		2.029f, 0.1424f, -0.8631f, 
		1.777f, 0.07031f, -0.7562f, 
		1.156f, 0.01934f, -0.4919f, 
		-2.4f, 3.038f, 0.0f, 
		-3.101f, 3.032f, 0.0f, 
		-3.619f, 2.995f, 0.0f, 
		-3.94f, 2.895f, 0.0f, 
		-4.05f, 2.7f, 0.0f, 
		-2.377f, 3.09f, 0.2531f, 
		-3.122f, 3.084f, 0.2531f, 
		-3.669f, 3.041f, 0.2531f, 
		-4.005f, 2.926f, 0.2531f, 
		-4.12f, 2.7f, 0.2531f, 
		-2.325f, 3.206f, 0.3375f, 
		-3.168f, 3.198f, 0.3375f, 
		-3.778f, 3.143f, 0.3375f, 
		-4.15f, 2.993f, 0.3375f, 
		-4.275f, 2.7f, 0.3375f, 
		-2.273f, 3.322f, 0.2531f, 
		-3.214f, 3.313f, 0.2531f, 
		-3.888f, 3.244f, 0.2531f, 
		-4.294f, 3.06f, 0.2531f, 
		-4.43f, 2.7f, 0.2531f, 
		-2.25f, 3.375f, 0.0f, 
		-3.234f, 3.364f, 0.0f, 
		-3.938f, 3.291f, 0.0f, 
		-4.359f, 3.09f, 0.0f, 
		-4.5f, 2.7f, 0.0f, 
		-2.273f, 3.322f, -0.2531f, 
		-3.214f, 3.313f, -0.2531f, 
		-3.888f, 3.244f, -0.2531f, 
		-4.294f, 3.06f, -0.2531f, 
		-4.43f, 2.7f, -0.2531f, 
		-2.325f, 3.206f, -0.3375f, 
		-3.168f, 3.198f, -0.3375f, 
		-3.778f, 3.143f, -0.3375f, 
		-4.15f, 2.993f, -0.3375f, 
		-4.275f, 2.7f, -0.3375f, 
		-2.377f, 3.09f, -0.2531f, 
		-3.122f, 3.084f, -0.2531f, 
		-3.669f, 3.041f, -0.2531f, 
		-4.005f, 2.926f, -0.2531f, 
		-4.12f, 2.7f, -0.2531f, 
		-3.991f, 2.394f, 0.0f, 
		-3.806f, 2.025f, 0.0f, 
		-3.48f, 1.656f, 0.0f, 
		-3.0f, 1.35f, 0.0f, 
		-4.055f, 2.365f, 0.2531f, 
		-3.852f, 1.98f, 0.2531f, 
		-3.496f, 1.6f, 0.2531f, 
		-2.977f, 1.28f, 0.2531f, 
		-4.196f, 2.3f, 0.3375f, 
		-3.952f, 1.881f, 0.3375f, 
		-3.531f, 1.478f, 0.3375f, 
		-2.925f, 1.125f, 0.3375f, 
		-4.336f, 2.235f, 0.2531f, 
		-4.051f, 1.782f, 0.2531f, 
		-3.566f, 1.356f, 0.2531f, 
		-2.873f, 0.9703f, 0.2531f, 
		-4.4f, 2.205f, 0.0f, 
		-4.097f, 1.737f, 0.0f, 
		-3.582f, 1.3f, 0.0f, 
		-2.85f, 0.9f, 0.0f, 
		-4.336f, 2.235f, -0.2531f, 
		-4.051f, 1.782f, -0.2531f, 
		-3.566f, 1.356f, -0.2531f, 
		-2.873f, 0.9703f, -0.2531f, 
		-4.196f, 2.3f, -0.3375f, 
		-3.952f, 1.881f, -0.3375f, 
		-3.531f, 1.478f, -0.3375f, 
		-2.925f, 1.125f, -0.3375f, 
		-4.055f, 2.365f, -0.2531f, 
		-3.852f, 1.98f, -0.2531f, 
		-3.496f, 1.6f, -0.2531f, 
		-2.977f, 1.28f, -0.2531f, 
		2.55f, 2.137f, 0.0f, 
		3.27f, 2.303f, 0.0f, 
		3.581f, 2.7f, 0.0f, 
		3.752f, 3.182f, 0.0f, 
		4.05f, 3.6f, 0.0f, 
		2.55f, 1.944f, 0.5569f, 
		3.324f, 2.159f, 0.5028f, 
		3.652f, 2.617f, 0.3839f, 
		3.838f, 3.151f, 0.265f, 
		4.191f, 3.6f, 0.2109f, 
		2.55f, 1.519f, 0.7425f, 
		3.445f, 1.844f, 0.6704f, 
		3.806f, 2.433f, 0.5119f, 
		4.027f, 3.085f, 0.3533f, 
		4.5f, 3.6f, 0.2813f, 
		2.55f, 1.093f, 0.5569f, 
		3.566f, 1.529f, 0.5028f, 
		3.961f, 2.249f, 0.3839f, 
		4.215f, 3.018f, 0.265f, 
		4.809f, 3.6f, 0.2109f, 
		2.55f, 0.9f, 0.0f, 
		3.621f, 1.385f, 0.0f, 
		4.031f, 2.166f, 0.0f, 
		4.301f, 2.988f, 0.0f, 
		4.95f, 3.6f, 0.0f, 
		2.55f, 1.093f, -0.5569f, 
		3.566f, 1.529f, -0.5028f, 
		3.961f, 2.249f, -0.3839f, 
		4.215f, 3.018f, -0.265f, 
		4.809f, 3.6f, -0.2109f, 
		2.55f, 1.519f, -0.7425f, 
		3.445f, 1.844f, -0.6704f, 
		3.806f, 2.433f, -0.5119f, 
		4.027f, 3.085f, -0.3533f, 
		4.5f, 3.6f, -0.2813f, 
		2.55f, 1.944f, -0.5569f, 
		3.324f, 2.159f, -0.5028f, 
		3.652f, 2.617f, -0.3839f, 
		3.838f, 3.151f, -0.265f, 
		4.191f, 3.6f, -0.2109f, 
		4.158f, 3.663f, 0.0f, 
		4.238f, 3.684f, 0.0f, 
		4.261f, 3.663f, 0.0f, 
		4.2f, 3.6f, 0.0f, 
		4.308f, 3.666f, 0.1978f, 
		4.379f, 3.689f, 0.1687f, 
		4.381f, 3.668f, 0.1397f, 
		4.294f, 3.6f, 0.1266f, 
		4.64f, 3.673f, 0.2637f, 
		4.69f, 3.7f, 0.225f, 
		4.645f, 3.677f, 0.1863f, 
		4.5f, 3.6f, 0.1688f, 
		4.971f, 3.68f, 0.1978f, 
		5.001f, 3.711f, 0.1687f, 
		4.909f, 3.687f, 0.1397f, 
		4.706f, 3.6f, 0.1266f, 
		5.122f, 3.683f, 0.0f, 
		5.142f, 3.716f, 0.0f, 
		5.029f, 3.691f, 0.0f, 
		4.8f, 3.6f, 0.0f, 
		4.971f, 3.68f, -0.1978f, 
		5.001f, 3.711f, -0.1687f, 
		4.909f, 3.687f, -0.1397f, 
		4.706f, 3.6f, -0.1266f, 
		4.64f, 3.673f, -0.2637f, 
		4.69f, 3.7f, -0.225f, 
		4.645f, 3.677f, -0.1863f, 
		4.5f, 3.6f, -0.1688f, 
		4.308f, 3.666f, -0.1978f, 
		4.379f, 3.689f, -0.1687f, 
		4.381f, 3.668f, -0.1397f, 
		4.294f, 3.6f, -0.1266f, 
		0.0f, 4.725f, 0.0f, 
		0.5109f, 4.651f, 0.0f, 
		0.4875f, 4.472f, 0.0f, 
		0.2953f, 4.25f, 0.0f, 
		0.3f, 4.05f, 0.0f, 
		0.4715f, 4.651f, 0.2011f, 
		0.4499f, 4.472f, 0.1918f, 
		0.2725f, 4.25f, 0.1161f, 
		0.2768f, 4.05f, 0.1178f, 
		0.3632f, 4.651f, 0.3632f, 
		0.3465f, 4.472f, 0.3465f, 
		0.2098f, 4.25f, 0.2098f, 
		0.213f, 4.05f, 0.213f, 
		0.2011f, 4.651f, 0.4715f, 
		0.1918f, 4.472f, 0.4499f, 
		0.1161f, 4.25f, 0.2725f, 
		0.1178f, 4.05f, 0.2768f, 
		0.0f, 4.651f, 0.5109f, 
		0.0f, 4.472f, 0.4875f, 
		0.0f, 4.25f, 0.2953f, 
		0.0f, 4.05f, 0.3f, 
		-0.2011f, 4.651f, 0.4715f, 
		-0.1918f, 4.472f, 0.4499f, 
		-0.1161f, 4.25f, 0.2725f, 
		-0.1178f, 4.05f, 0.2768f, 
		-0.3632f, 4.651f, 0.3632f, 
		-0.3465f, 4.472f, 0.3465f, 
		-0.2098f, 4.25f, 0.2098f, 
		-0.213f, 4.05f, 0.213f, 
		-0.4715f, 4.651f, 0.2011f, 
		-0.4499f, 4.472f, 0.1918f, 
		-0.2725f, 4.25f, 0.1161f, 
		-0.2768f, 4.05f, 0.1178f, 
		-0.5109f, 4.651f, 0.0f, 
		-0.4875f, 4.472f, 0.0f, 
		-0.2953f, 4.25f, 0.0f, 
		-0.3f, 4.05f, 0.0f, 
		-0.4715f, 4.651f, -0.2011f, 
		-0.4499f, 4.472f, -0.1918f, 
		-0.2725f, 4.25f, -0.1161f, 
		-0.2768f, 4.05f, -0.1178f, 
		-0.3632f, 4.651f, -0.3632f, 
		-0.3465f, 4.472f, -0.3465f, 
		-0.2098f, 4.25f, -0.2098f, 
		-0.213f, 4.05f, -0.213f, 
		-0.2011f, 4.651f, -0.4715f, 
		-0.1918f, 4.472f, -0.4499f, 
		-0.1161f, 4.25f, -0.2725f, 
		-0.1178f, 4.05f, -0.2768f, 
		0.0f, 4.651f, -0.5109f, 
		0.0f, 4.472f, -0.4875f, 
		0.0f, 4.25f, -0.2953f, 
		0.0f, 4.05f, -0.3f, 
		0.2011f, 4.651f, -0.4715f, 
		0.1918f, 4.472f, -0.4499f, 
		0.1161f, 4.25f, -0.2725f, 
		0.1178f, 4.05f, -0.2768f, 
		0.3632f, 4.651f, -0.3632f, 
		0.3465f, 4.472f, -0.3465f, 
		0.2098f, 4.25f, -0.2098f, 
		0.213f, 4.05f, -0.213f, 
		0.4715f, 4.651f, -0.2011f, 
		0.4499f, 4.472f, -0.1918f, 
		0.2725f, 4.25f, -0.1161f, 
		0.2768f, 4.05f, -0.1178f, 
		0.6844f, 3.916f, 0.0f, 
		1.237f, 3.825f, 0.0f, 
		1.734f, 3.734f, 0.0f, 
		1.95f, 3.6f, 0.0f, 
		0.6313f, 3.916f, 0.2686f, 
		1.142f, 3.825f, 0.4857f, 
		1.6f, 3.734f, 0.6807f, 
		1.799f, 3.6f, 0.7654f, 
		0.4859f, 3.916f, 0.4859f, 
		0.8786f, 3.825f, 0.8786f, 
		1.231f, 3.734f, 1.231f, 
		1.385f, 3.6f, 1.385f, 
		0.2686f, 3.916f, 0.6313f, 
		0.4857f, 3.825f, 1.142f, 
		0.6807f, 3.734f, 1.6f, 
		0.7654f, 3.6f, 1.799f, 
		0.0f, 3.916f, 0.6844f, 
		0.0f, 3.825f, 1.237f, 
		0.0f, 3.734f, 1.734f, 
		0.0f, 3.6f, 1.95f, 
		-0.2686f, 3.916f, 0.6313f, 
		-0.4857f, 3.825f, 1.142f, 
		-0.6807f, 3.734f, 1.6f, 
		-0.7654f, 3.6f, 1.799f, 
		-0.4859f, 3.916f, 0.4859f, 
		-0.8786f, 3.825f, 0.8786f, 
		-1.231f, 3.734f, 1.231f, 
		-1.385f, 3.6f, 1.385f, 
		-0.6313f, 3.916f, 0.2686f, 
		-1.142f, 3.825f, 0.4857f, 
		-1.6f, 3.734f, 0.6807f, 
		-1.799f, 3.6f, 0.7654f, 
		-0.6844f, 3.916f, 0.0f, 
		-1.237f, 3.825f, 0.0f, 
		-1.734f, 3.734f, 0.0f, 
		-1.95f, 3.6f, 0.0f, 
		-0.6313f, 3.916f, -0.2686f, 
		-1.142f, 3.825f, -0.4857f, 
		-1.6f, 3.734f, -0.6807f, 
		-1.799f, 3.6f, -0.7654f, 
		-0.4859f, 3.916f, -0.4859f, 
		-0.8786f, 3.825f, -0.8786f, 
		-1.231f, 3.734f, -1.231f, 
		-1.385f, 3.6f, -1.385f, 
		-0.2686f, 3.916f, -0.6313f, 
		-0.4857f, 3.825f, -1.142f, 
		-0.6807f, 3.734f, -1.6f, 
		-0.7654f, 3.6f, -1.799f, 
		0.0f, 3.916f, -0.6844f, 
		0.0f, 3.825f, -1.237f, 
		0.0f, 3.734f, -1.734f, 
		0.0f, 3.6f, -1.95f, 
		0.2686f, 3.916f, -0.6313f, 
		0.4857f, 3.825f, -1.142f, 
		0.6807f, 3.734f, -1.6f, 
		0.7654f, 3.6f, -1.799f, 
		0.4859f, 3.916f, -0.4859f, 
		0.8786f, 3.825f, -0.8786f, 
		1.231f, 3.734f, -1.231f, 
		1.385f, 3.6f, -1.385f, 
		0.6313f, 3.916f, -0.2686f, 
		1.142f, 3.825f, -0.4857f, 
		1.6f, 3.734f, -0.6807f, 
		1.799f, 3.6f, -0.7654f
	};

	const int strip_vertices[] = {
		508, 508, 504, 509, 504, 505, 500, 501, 496, 497, 492, 493, 488, 489, 484, 485, 480, 481, 476, 477, 472, 473, -1,
		476, 475, 480, 479, 484, 483, 488, 487, 492, 491, 496, 495, 500, 499, 504, 499, 503, 498, 502, 437, 441, -1,
		527, 526, 467, 466, 471, 470, 475, 474, 479, 478, 483, 482, 487, 486, 491, 490, 495, 494, 499, 494, 498, -1,
		490, 490, 425, 486, 421, 482, 417, 478, 413, 474, 409, 470, 405, 466, 465, 526, 465, 461, 460, 456, 455, 451, -1,
		405, 465, 464, 460, 459, 455, 454, 450, -1,
		455, 451, 450, 446, 450, 401, 454, 458, 459, 463, 464, 404, 405, 404, 409, 408, 413, 412, 417, 416, 421, 420, -1,
		421, 420, 425, 420, 424, 419, 423, 418, 422, 418, 401, 414, 410, 415, 411, 416, 411, 412, 407, 408, 403, 404, 403, 463, -1,
		418, 418, 414, 419, 415, 420, 416, -1,
		407, 403, 402, 462, -1,
		403, 463, 462, 458, 462, 401, 402, 406, 407, 406, 411, 406, 410, 401, -1,
		494, 494, 498, 433, 437, 432, 436, 431, 435, 430, 434, 430, 401, 426, 422, 427, 423, 428, 424, 429, 425, 490, -1,
		430, 430, 426, 431, 427, 432, 428, 433, 429, 494, 490, -1,
		437, 437, 441, 436, 440, 435, 439, 434, 438, 401, 442, 446, 447, 451, 452, 456, 457, 461, 522, 526, 527, -1,
		452, 448, 447, -1,
		510, 445, 449, 444, 448, 443, 447, 443, 442, 443, 438, 443, 439, 444, 440, 445, 441, 506, 502, 507, 503, -1,
		510, 506, 445, -1,
		507, 506, 511, 510, 515, 510, 514, 449, 453, 448, 453, 452, 457, -1,
		527, 523, 522, 518, 457, 518, 453, 518, 514, 519, 515, -1,
		523, 519, 518, -1,
		504, 503, 508, 507, 512, 511, 516, 515, 520, 519, 524, 523, 528, 527, 468, 467, 472, 471, 476, 475, -1,
		472, 473, 468, 469, 528, 529, 524, 525, 520, 521, 516, 517, 512, 513, 508, 509, -1,
		211, 211, 214, 210, 209, -1,
		212, 215, 216, 219, 220, 223, 220, 211, 217, 214, 213, 209, 213, 208, 212, 147, -1,
		220, 217, 216, 213, 212, -1,
		251, 251, 248, 252, 249, 253, 250, 253, 211, 256, 210, 255, 209, 254, 208, 207, 147, 206, 147, 146, 147, 151, 212, 215, -1,
		206, 206, 202, 207, 203, 254, 251, 255, 252, 256, 253, -1,
		223, 223, 222, 219, 218, 215, 155, 151, 150, 146, 145, 146, 205, 206, 201, 202, 197, 202, 198, 203, 199, 251, 248, -1,
		145, 149, 150, 154, 155, 159, 218, 221, 222, 225, 226, 229, -1,
		204, 204, 145, 144, 149, 148, 149, 153, 154, 158, 159, 163, 221, 224, 225, 228, 229, 232, 229, 211, 226, 223, 222, -1,
		224, 224, 167, 163, 162, 158, 157, 153, 152, 148, 87, 148, 83, 144, 143, 204, 139, 200, 135, 196, 131, 192, -1,
		82, 83, 142, 143, 138, 139, 134, 135, 130, 131, 126, 127, 122, 123, 118, 123, 119, 184, 180, 185, 181, -1,
		81, 82, 141, 142, 137, 138, 133, 134, 129, 130, 125, 126, 121, 122, 117, 118, 113, 114, 109, 110, -1,
		80, 81, 140, 141, 136, 137, 132, 133, 128, 129, 124, 125, 120, 121, 116, 117, 112, 113, 108, 109, -1,
		4, 80, 79, 140, 74, 136, 69, 132, 64, 128, 59, 124, 54, 120, 49, 116, 44, 112, 39, 108, -1,
		79, 79, 73, 74, 68, 69, 63, 64, 58, 59, 53, 54, 48, 49, 48, 43, 42, 37, 36, 31, 30, 31, 25, -1,
		42, 42, 48, 47, 53, 52, 58, 57, 63, 62, 68, 67, 73, 72, 78, 77, 3, 2, 8, 7, 13, -1,
		36, 36, 42, 41, 47, 46, 52, 51, 57, 56, 62, 61, 67, 66, 72, 71, 77, 76, 2, 1, 7, -1,
		66, 66, 60, 61, 55, 56, 50, 51, 45, 46, 40, 41, 35, 36, 30, -1,
		31, 31, 25, 26, 20, 21, 15, 16, 10, 11, 5, 6, 0, 1, 75, 76, 70, 71, 65, 66, 60, -1,
		1, 1, 7, 6, 12, 11, 17, 16, 22, 21, 27, 26, 32, 31, 32, 37, 38, 43, 44, 49, -1,
		7, 7, 13, 12, 18, 17, 23, 22, 28, 27, 33, 32, 33, 38, -1,
		44, 44, 38, 39, 33, 34, 28, 29, 23, 24, 18, 19, 13, 14, 8, 9, 3, 4, 78, 79, 73, -1,
		39, 108, 34, 104, 29, 100, 24, 96, 19, 92, 14, 88, 9, 84, 4, 84, 80, 85, 81, 86, 81, 82, -1,
		108, 109, 104, 105, 100, 101, 96, 97, 92, 93, 88, 89, 84, 85, -1,
		109, 110, 105, 106, 101, 102, 97, 98, 93, 94, 89, 90, 85, 86, -1,
		118, 119, 114, 115, 110, 111, 106, 107, 102, 103, 98, 99, 94, 95, 90, 91, 86, 87, 82, 83, -1,
		111, 115, 176, -1,
		107, 111, 172, 176, 177, -1,
		103, 107, 168, 172, 173, 177, 178, -1,
		99, 103, 164, 168, 169, 173, 174, 178, 179, -1,
		95, 99, 160, 164, 165, 169, 170, 174, 175, 179, 233, -1,
		91, 95, 156, 160, 161, 165, 166, 170, 171, 175, 230, 233, 234, -1,
		87, 91, 152, 156, 157, 161, 162, 166, 167, 171, 227, 230, 231, 234, 235, 234, 238, 234, 237, 233, 236, 179, -1,
		185, 185, 181, 186, 182, 187, 183, 239, 236, 240, 237, 241, 238, 211, 235, 232, 231, 228, 227, 224, 167, -1,
		236, 179, 183, 178, 182, 177, 181, 176, 180, 115, 119, -1,
		131, 192, 127, 188, 123, 188, 184, 189, 185, 190, 186, 191, 187, 242, 239, 243, 240, 244, 241, 244, 211, 247, -1,
		192, 192, 188, 193, 189, 194, 190, 195, 191, 245, 242, 246, 243, 247, 244, -1,
		211, 247, 250, 246, 249, 245, 248, 195, 199, 194, 198, 193, 197, 192, 197, 196, 201, 200, 205, 204, 145, -1,
		393, 393, 394, 398, 399, 371, -1,
		399, 395, 394, -1,
		363, 363, 393, 397, 398, 370, 371, 375, -1,
		379, 375, 374, 370, 369, 397, 368, 363, 362, -1,
		396, 395, 400, 399, 372, 371, 376, 375, 380, 379, 384, 383, 388, 387, 392, 391, 396, 391, 395, 390, 394, -1,
		374, 378, 379, 378, 383, 382, 387, 386, 391, 386, 390, 385, 389, 353, 358, 352, 357, 351, 356, 350, 355, -1,
		341, 341, 347, 346, 352, 346, 351, 345, 350, -1,
		335, 334, 340, 339, 345, 344, 350, 349, 355, 354, -1,
		390, 390, 394, 389, 393, 358, 363, 357, 362, 356, 361, 355, 360, 354, 360, 359, 365, 364, 330, 329, 335, 334, -1,
		345, 346, 340, 341, 335, 336, 330, 331, 365, 366, 360, 366, 361, 367, 362, 367, 368, 333, 369, 373, 374, 378, -1,
		353, 353, 348, 385, 381, 386, 381, 382, 377, 378, 377, 373, 338, 333, 332, 367, 332, 366, 332, 331, 337, 336, 342, 341, 347, -1,
		332, 337, 338, 343, 377, 343, 381, 343, 348, 342, 348, 347, 353, 352, -1,
		337, 342, 343, -1,
		314, 314, 319, 318, 323, 322, 323, 327, -1,
		309, 309, 314, 313, 318, 317, 322, 321, 322, 326, 327, 299, -1,
		271, 271, 309, 276, 313, 281, 317, 286, 321, 291, 321, 325, 326, 298, 299, 303, -1,
		265, 265, 271, 270, 276, 275, 281, 280, 286, 285, 291, 290, 291, 296, 325, 297, 298, 302, 303, 307, -1,
		259, 259, 265, 264, 270, 269, 275, 274, 280, 279, 285, 284, 290, 289, 290, 295, 296, 261, 297, 301, 302, 306, 307, 311, -1,
		293, 293, 259, 258, 264, 263, 269, 268, 274, 273, 279, 278, 284, 283, 289, 288, 289, 294, 295, 260, 261, 266, -1,
		309, 305, 271, 266, 265, 260, 259, 294, 293, 288, 287, 288, 282, 283, 277, 278, 272, 273, 267, 268, 262, -1,
		268, 268, 262, 263, 257, 258, 292, 293, 287, -1,
		261, 266, 301, 305, 306, 310, 311, 315, 316, 320, -1,
		316, 316, 311, 312, 307, 308, 303, 304, 299, 300, 327, 328, 323, 324, 319, 320, 319, 315, 314, 310, 309, 305, -1
	};

	class surface_glteapot : public surface_tricompound {
	public:
		surface_glteapot();
	};
}

#endif