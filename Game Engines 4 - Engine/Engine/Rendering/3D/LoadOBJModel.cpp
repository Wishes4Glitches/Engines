#include "LoadOBJModel.h"

LoadOBJModel::LoadOBJModel() : currentMaterial(Material())
{
	vertices.reserve(200);
	normals.reserve(200);
	textureCoords.reserve(200);
	indices.reserve(200);
	normalIndices.reserve(200);
	textureIndices.reserve(200);
	meshVertices.reserve(200);
	subMeshes.reserve(10);
}

LoadOBJModel::~LoadOBJModel()
{
	OnDestroy();
}

void LoadOBJModel::LoadModel(const std::string& objFilePath_)
{
	std::ifstream in(objFilePath_.c_str(), std::ios::in);
	if (!in)
	{
		Debug::Error("Cannot open OBJ file: " + objFilePath_, "LoadOBJModel.cpp", __LINE__);
		return;
	}
	std::string line;
	while (std::getline(in, line))
	{
		if (line.substr(0, 2) == "v ")
		{
			std::istringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			vertices.push_back(glm::vec3(x, y, z));

			glm::vec3 vertex = glm::vec3(x, y, z);

			//Minimum Values
			if (vertex.x < box.minVert.x) {
				box.minVert.x = vertex.x;
			}
			if (vertex.y < box.minVert.y) {
				box.minVert.y = vertex.y;
			}
			if (vertex.z < box.minVert.z) {
				box.minVert.z = vertex.z;
			}

			//max values
			if (vertex.x > box.maxVert.x) {
				box.maxVert.x = vertex.x;
			}
			if (vertex.y > box.maxVert.y) {
				box.maxVert.y = vertex.y;
			}
			if (vertex.z > box.maxVert.z) {
				box.maxVert.z = vertex.z;
			}
		}

		//Normal Data
		if (line.substr(0, 3) == "vn ") {
			std::istringstream v(line.substr(3));
			GLfloat n1, n2, n3;
			v >> n1 >> n2 >> n3;
			normals.push_back(glm::vec3(n1, n2, n3));
		}

		//Texture Coordinate Data
		if (line.substr(0, 3) == "vt ") {
			std::istringstream v(line.substr(3));
			float x, y;
			v >> x >> y;
			textureCoords.push_back(glm::vec2(x, y));
		}

		//Face Data
		if (line.substr(0, 2) == "f ") {
			int vert, text, norm;

			std::string data = line.substr(2);
			int space = data.find(" ");
			std::string d1 = data.substr(0, space);
			std::stringstream vertText(d1.substr(0, d1.find("/")));
			vertText >> vert;
			indices.push_back(vert - 1);
			d1 = d1.substr(d1.find("/") + 1);
			std::stringstream texText(d1.substr(0, d1.find("/")));
			texText >> text;
			textureIndices.push_back(text - 1);
			d1 = d1.substr(d1.find("/") + 1);
			std::stringstream normText(d1.substr(0, d1.find("/")));
			normText >> norm;
			normalIndices.push_back(norm - 1);

			space = data.find(" ");

			data = data.substr(data.find(" ") + 1);
			std::string d2 = data.substr(0, data.find(" "));
			std::stringstream vertText2(d2.substr(0, d2.find("/")));
			vertText2 >> vert;
			indices.push_back(vert - 1);
			d2 = d2.substr(d2.find("/") + 1);
			std::stringstream texText2(d2.substr(0, d2.find("/")));
			texText2 >> text;
			textureIndices.push_back(text - 1);
			d2 = d2.substr(d2.find("/") + 1);
			std::stringstream normText2(d2.substr(0, d2.find("/")));
			normText2 >> norm;
			normalIndices.push_back(norm - 1);

			space = data.find(" ");

			data = data.substr(data.find(" ") + 1);
			std::string d3 = data.substr(0, data.find(" "));
			std::stringstream vertText3(d3.substr(0, d3.find("/")));
			vertText3 >> vert;
			indices.push_back(vert - 1);
			d3 = d3.substr(d3.find("/") + 1);
			std::stringstream texText3(d3.substr(0, d3.find("/")));
			texText3 >> text;
			textureIndices.push_back(text - 1);
			d3 = d3.substr(d3.find("/") + 1);
			std::stringstream normText3(d3.substr(0, d3.find("/")));
			normText3 >> norm;
			normalIndices.push_back(norm - 1);
		}

		else if (line.substr(0, 7) == "usemtl ")
		{
			if (indices.size() > 0)
			{
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}
	}
	PostProcessing();
}

void LoadOBJModel::LoadModel(const std::string& objFilePath_, const std::string& matFilePath_)
{
	LoadMaterialLibrary(matFilePath_);
	LoadModel(objFilePath_);
}

std::vector<Vertex> LoadOBJModel::GetVerts()
{
	return meshVertices;
}

std::vector<int> LoadOBJModel::GetIndices()
{
	return indices;
}

std::vector<SubMesh> LoadOBJModel::GetSubMeshes()
{
	return subMeshes;
}

BoundingBox LoadOBJModel::GetBoundingBox()
{
	return box;
}

void LoadOBJModel::OnDestroy()
{
	vertices.clear();
	normals.clear();
	textureCoords.clear();
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	subMeshes.clear();
}

void LoadOBJModel::PostProcessing()
{
	for (int i = 0; i < indices.size(); i++)
	{
		Vertex vert;
		vert.position = vertices[indices[i]];
		vert.normal = normals[normalIndices[i]];
		vert.texCoords = textureCoords[textureIndices[i]];
		meshVertices.push_back(vert);
	}

	SubMesh subMesh;
	subMesh.vertexList = meshVertices;
	subMesh.meshIndices = indices;
	subMesh.material = currentMaterial;
	subMeshes.push_back(subMesh);

	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	currentMaterial = Material();
}

void LoadOBJModel::LoadMaterial(const std::string& fileName_)
{
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(fileName_);
}

void LoadOBJModel::LoadMaterialLibrary(const std::string& matFilePath_)
{
	MaterialLoader::LoadMaterial(matFilePath_);
}