#ifndef _MODEL_
#define _MODEL_
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <mesh/Mesh.h>

class Model
{
public:
	Model(const char *path, bool gamma = false)
		: gammaCorrection(gamma) 
	{
		loadMesh(path);
	}
	void Draw(Shader& shader);
private:
	//加载文件，执行aiScene-->aiNode-->mesh的转换
	void loadMesh(string path);
	void processNode(aiNode* node, const aiScene *scene);
	Mesh processMesh(aiMesh* mesh, const aiScene *scene);
	void loadMaterialTextures(aiMaterial * mat, aiTextureType type, string typeName, vector<mesh::Texture>& textures);
	unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);
private:
	vector<Mesh> meshes;
	vector<mesh::Texture> textures_loaded;
	string directory;
	bool gammaCorrection;
};
#endif // _MODEL_


