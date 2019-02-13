#include "Model.h"

#define STB_IMAGE_IMPLEMENTATION
#include <tool/stb_image.h>
using namespace std;
void Model::loadMesh(string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (!scene || scene->mFlags&AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));
	processNode(scene->mRootNode, scene);
}
void Model::processNode(aiNode* node, const aiScene *scene) 
{
	for (unsigned int i = 0, size = node->mNumMeshes;i < size;++i) {
		int meshIdx = node->mMeshes[i];
		meshes.emplace_back(processMesh(scene->mMeshes[meshIdx], scene));
	}
	for (unsigned int i = 0, size = node->mNumChildren;i < size;++i) {
		aiNode* child = node->mChildren[i];
		processNode(child,  scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene *scene)
{
	vector<Vertex> vertices;
	vector<Texture> textures;
	vector<unsigned int> indices;
	//¶¥µã
	vertices.reserve(mesh->mNumVertices);
	for (unsigned int i =0;i<mesh->mNumVertices;++i)
	{
		Vertex vertex;
		vertex.position.x = mesh->mVertices[i].x;
		vertex.position.y = mesh->mVertices[i].y;
		vertex.position.z = mesh->mVertices[i].z;
			
		vertex.normal.x = mesh->mNormals[i].x;
		vertex.normal.y = mesh->mNormals[i].y;
		vertex.normal.z = mesh->mNormals[i].z;
		
		if (mesh->mTextureCoords[0])
		{
			vertex.texCoords.x = mesh->mTextureCoords[0][i].x;
			vertex.texCoords.y = mesh->mTextureCoords[0][i].y;
		} else {
			vertex.texCoords.x = vertex.texCoords.y = 0.0f;
		}

		vertex.tangent.x = mesh->mTangents[i].x;
		vertex.tangent.y = mesh->mTangents[i].y;
		vertex.tangent.z = mesh->mTangents[i].z;
		vertex.biTangent.x = mesh->mBitangents[i].x;
		vertex.biTangent.y = mesh->mBitangents[i].y;
		vertex.biTangent.z = mesh->mBitangents[i].z;

		vertices.emplace_back (vertex);
	}
	//Ë÷Òý
	int indicesSize = 0;
	for (unsigned int i = 0, size = mesh->mNumFaces; i < size;++i){
		aiFace &face = mesh->mFaces[i];
		indicesSize += face.mNumIndices;
	}
	indices.reserve(indicesSize);
	for (unsigned int i = 0, size = mesh->mNumFaces; i < size;++i)
	{
		aiFace &face = mesh->mFaces[i];
		for (unsigned int j=0, size = face.mNumIndices; j < size;++j)
		{
			indices.emplace_back(face.mIndices[j]);
		}
	}
	//ÎÆÀí
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	int textureSize = material->GetTextureCount(aiTextureType_DIFFUSE) *
		material->GetTextureCount(aiTextureType_SPECULAR) *
		material->GetTextureCount(aiTextureType_HEIGHT) *
		material->GetTextureCount(aiTextureType_AMBIENT);
	textures.reserve(textureSize);
	loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", textures);
	loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", textures);
	loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal", textures);
	loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height", textures);

	return Mesh(vertices, textures, indices);
}

void Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName, vector<Texture>& textures)
{
	for (unsigned int i = 0, size=mat->GetTextureCount(type);i<size;++i)
	{
		aiString  aistr;
		mat->GetTexture(type, i, &aistr);
		bool skip = false;
		for (unsigned int j = 0, jsize = textures_loaded.size();j<jsize;++j) {
			if (std::strcmp(typeName.c_str(), aistr.C_Str()) == 0) {
				textures.emplace_back(textures_loaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip) {
			int textureIdx = TextureFromFile(aistr.C_Str(), this->directory);
			Texture tex;
			tex.id = textureIdx;
			tex.type = typeName;
			tex.path =aistr.C_Str();
			textures.emplace_back(tex);
			textures_loaded.emplace_back(tex);
		}

	}
}

unsigned int Model::TextureFromFile(const char *path, const string &directory, bool gamma) {
	string filename = string(path);
	filename = directory + '/' + filename;
	
	unsigned int textureID;
	glGenTextures(1, &textureID);
	
	int width, height, nrComponents;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data) {
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	} else {
		std::cout<< "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}
	return textureID;
}

void Model::Draw(Shader& shader)
{
	for (unsigned int i = 0, size = meshes.size();i<size;++i)
	{
		meshes[i].Draw(shader);
	}
}