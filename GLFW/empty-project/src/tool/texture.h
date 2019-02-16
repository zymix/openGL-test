#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include <vector>
class Texture
{
public:
	unsigned int loadTexture(char const * path);
	unsigned int loadCubeMap(std::vector<std::string>& face);
private:
	unsigned int textureID;
};
#endif // _TEXTURE_H_
