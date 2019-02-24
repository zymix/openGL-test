#ifndef _MESH_H_
#define _MESH_H_
#include <vector>
#include <glm/glm.hpp>
#include <shader/Shader.h>
using namespace std;

namespace mesh
{
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoords;
		glm::vec3 tangent;
		glm::vec3 biTangent;
	};
	struct Texture
	{
		unsigned int id;
		string type;
		string path;
	};
}
using namespace mesh;

class Mesh
{
public:
	void Draw(Shader shader);
	Mesh(vector<Vertex>& vertices, vector<Texture>& textures, vector<unsigned int>& indices);
	~Mesh();
private:
	void setupMesh();

public:
	vector<Vertex> vertices;
	vector<Texture> textures;
	vector<unsigned int> indices;
private:
	unsigned int VAO, VBO, EBO;
};


#endif // !_MESH_H_

