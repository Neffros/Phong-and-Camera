#include "myMesh.h"

Mesh::Mesh(const vector<Vertex> _vertices, const vector<unsigned int> _indices) :
	vertices{ _vertices }, indices{ _indices }
{
	initRenderingData();
}

Mesh::Mesh()
{
	this->vertices = vector<Vertex>();
	this->indices = vector<unsigned int>();
}

void Mesh::draw(myShader& shader)
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::addLastVertexAtPosition(double x, double y, double z)
{
	this->indices.push_back(this->indices.size());
	this->vertices.push_back(Vertex{ glm::vec3(x, y, z) });
	initRenderingData();
}

void Mesh::removeLastVertex()
{
	this->vertices.pop_back();
	this->indices.pop_back();
	initRenderingData();
}



void Mesh::initRenderingData()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
}