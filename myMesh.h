#pragma once

#include <string>
#include <vector>
#include "myShader.h"
#include "myVector3.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stddef.h>
#include <glm.hpp>
using namespace std;


struct Vertex {
	glm::vec3 Position{};
	glm::vec3 Normal{};
	glm::vec2 TexCoords{};
	//glm::vec3 Tangent{};
	//glm::vec3 Bitangent{};
};

class Mesh {

public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	unsigned int VAO;

	Mesh(const vector<Vertex> vertices, const vector<unsigned int> indices);
	Mesh();
	void draw(myShader& shader);
	void addLastVertexAtPosition(double x, double y, double z);
	void removeLastVertex();

private:
	unsigned int VBO, EBO;
	void initRenderingData();
};