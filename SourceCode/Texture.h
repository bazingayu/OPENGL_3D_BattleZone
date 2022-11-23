#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <stdio.h>
#include <string>
#include "IncludeS.h"
#include "GL/freeglut.h"
#include "Tvector.h"

class Texture
{
public:
	GLubyte	*imageData;		// Image Data (Up To 32 Bits)
	GLuint	bpp;			// Image Color Depth In Bits Per Pixel.
	GLuint	width;			// Image Width
	GLuint	height;			// Image Height
	GLuint	texID;			// Texture ID Used To Select A Texture
	GLuint  type;           // Type of image
	
	Texture();
	bool LoadTGA(char *filename);
};

#endif
