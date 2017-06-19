#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <GL/freeglut.h>
#include <string>

void loadTexture(std::string filename, GLuint &textureID);
void loadSkyBoxTexture();

#endif
