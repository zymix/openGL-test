#include "Texture.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <iostream>
unsigned int Texture::loadTexture(char const * path)
{
	unsigned int tid;
	glGenTextures(1, &tid);
	
	int width, height, nrComponent;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponent, 0);
	if (data)
	{
		GLenum format;
		if (nrComponent == 1)
			format = GL_RED;
		else if (nrComponent == 3)
			format = GL_RGB;
		else if (nrComponent == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, tid);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	_textureID = tid;
	return tid;
}

unsigned int Texture::loadCubeMap(std::vector<std::string>& face)
{
	unsigned int tid;
	glGenTextures(1, &tid);
	glBindTexture(GL_TEXTURE_CUBE_MAP, tid);
	int width, height, nrChannels;
	for (unsigned int i = 0; i< face.size();++i)
	{
		unsigned char * data = stbi_load(face[i].c_str(), &width, &height, &nrChannels, 0);
		if (data) 
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Texture failed to load at path: " << face[i].c_str() << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	
	_textureID = tid;
	return tid;
}
