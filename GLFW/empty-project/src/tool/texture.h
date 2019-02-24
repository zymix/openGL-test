#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include <vector>
class Texture
{
public:
	Texture() : _textureID(-1) {}
	unsigned int loadTexture(char const * path);
	unsigned int loadCubeMap(std::vector<std::string>& face);
	unsigned int _textureID;
};
#endif // _TEXTURE_H_
