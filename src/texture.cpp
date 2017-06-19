#include <GL\freeglut.h>
#include <iostream>
#include <string>
#include <soil.h>
#include "..\include\texture.h"
using namespace std;

GLuint wallTextureID, groundTexureID;
GLuint skyBoxTetureID[5];


void loadTexture(string filename, GLuint &textureID) {
	cout << "start loading texture of wall" << endl;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	int width, height;
	unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    //设置纹理参数
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	glBindTexture(GL_TEXTURE_2D, 0);

	cout << "Texture: " << filename << " loaded." << endl;
	cout << "loading texture of wall completes" << endl;
	cout << endl;
}

void loadSkyBoxTexture() {
	cout << "start loading textures of SkyBox" << endl;
	string filename[] = { "1_left.jpg", "2_front.jpg", "3_right.jpg", "4_back.jpg", "5_top.jpg" };
	glGenTextures(5, &skyBoxTetureID[0]);
	int width, height;
	unsigned char* image;
	for (int i = 0; i < 5; i++) {
		filename[i] = string("Texture/skybox/") + filename[i];

		glBindTexture(GL_TEXTURE_2D, skyBoxTetureID[i]);
		image = SOIL_load_image(filename[i].c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		cout << width << " " << height << endl;
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);    //设置纹理参数
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

		glBindTexture(GL_TEXTURE_2D, 0);
		cout << "Texture: " << filename[i] << " loaded." << endl;
	}
	cout << "loading textures of SkyBox completes" << endl;
	cout << endl;
}