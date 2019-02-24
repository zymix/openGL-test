#ifndef _SKYBOX_H_
#define _SKYBOX_H_
#include <vector>
#include <tool/Texture.h>
class Shader;
class Texture;

class Skybox
{
public:
	Skybox();
	~Skybox();
	void setTextureFaces(std::vector<std::string>& faces);
	void draw(Shader& shader);
private:
	unsigned int _skyboxVAO;
	unsigned int _skyboxVBO;
	::Texture _cubemapTexture;

private:
	static float _skyboxVertices[];
};
#endif // !_SKYBOX_H_

