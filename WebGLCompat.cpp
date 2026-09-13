//
//  WebGLCompat.cpp
//

#include "WebGLCompat.h"

#include <cmath>

#include "GetGlut.h"



//
//  drawWireSphere
//
//  A drop-in replacement for glutWireSphere/glutWireIcosahedron,
//    which Emscripten's legacy GL emulation does not implement.
//    Draws a latitude/longitude wireframe sphere.
//
void drawWireSphere (double radius, int slices, int stacks)
{
	static const double PI = 3.14159265358979323846;

	// latitude rings
	for(int stack = 1; stack < stacks; stack++)
	{
		double phi         = PI * stack / stacks;
		double ring_radius = radius * sin(phi);
		double y           = radius * cos(phi);

		glBegin(GL_LINE_LOOP);
			for(int slice = 0; slice <= slices; slice++)
			{
				double theta = 2.0 * PI * slice / slices;
				glVertex3f((float)(ring_radius * cos(theta)),
				           (float)(y),
				           (float)(ring_radius * sin(theta)));
			}
		glEnd();
	}

	// longitude meridians
	for(int slice = 0; slice < slices; slice++)
	{
		double theta = 2.0 * PI * slice / slices;

		glBegin(GL_LINE_STRIP);
			for(int stack = 0; stack <= stacks; stack++)
			{
				double phi         = PI * stack / stacks;
				double ring_radius = radius * sin(phi);
				double y           = radius * cos(phi);
				glVertex3f((float)(ring_radius * cos(theta)),
				           (float)(y),
				           (float)(ring_radius * sin(theta)));
			}
		glEnd();
	}
}



#ifdef __EMSCRIPTEN__

// Declared manually: it's implemented by Emscripten's GL emulation,
//   but not consistently declared by the legacy GL/gl.h header this
//   project includes for desktop compatibility.
extern "C" void glGenerateMipmap (GLenum target);

//
//  Emscripten's legacy GL emulation does not implement the
//    fixed-function attribute stack or the scalar glMaterialf
//    entry point.  This project never enables GL_LIGHTING
//    anywhere, so glMaterialf has no visible effect regardless of
//    its implementation.  The small, known set of state that this
//    project's two glPushAttrib/glPopAttrib call sites (in
//    Material.cpp and SpriteFont.cpp) actually change is restored
//    explicitly at each matching "pop" site instead of via a real
//    attribute stack - see the comments there.
//
void glPushAttrib (GLbitfield mask)
{
}

void glMaterialf (GLenum face, GLenum pname, GLfloat param)
{
}

//
//  Emscripten's legacy GL emulation does not implement the GLU
//    utility library.  glGenerateMipmap is the direct WebGL/GLES2
//    equivalent of what gluBuild2DMipmaps did on top of desktop
//    OpenGL, so this uploads level 0 and lets the driver generate
//    the rest of the mip chain.
//
GLint gluBuild2DMipmaps (GLenum target, GLint internalFormat,
                         GLsizei width, GLsizei height,
                         GLenum format, GLenum type, const void* data)
{
	glTexImage2D(target, 0, internalFormat, width, height, 0, format, type, data);
	glGenerateMipmap(target);
	return 0;
}

#endif  // __EMSCRIPTEN__
