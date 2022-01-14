#include "Mesh.h"
#include <vector>


// Constructor 

Mesh::Mesh()
{
	drawCount = NULL;
}


/* Deconstructor which deletes the arrays */

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vertexArrayObject);
}


/* Function to initialisie a model */

void Mesh::InitialiseModel(const IndexedModel& model)
{

	drawCount = model.indices.size();

	/* Generate vertex array, store it in  Vertex Array Object, bind it */
	glGenVertexArrays(1, &vertexArrayObject); 
	glBindVertexArray(vertexArrayObject); 

	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers); 

	/* For each buffer binding new and passing it to GPU */
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VERTEXBUFFER]); 
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW); 
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]); 
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW); 
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]); 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW); 

	// Unbinding VertexArrayObject
	glBindVertexArray(0); 
}


/* Function to load model and initialise it based on the file */

void Mesh::LoadModelFromFile(const std::string& filename)
{
	IndexedModel model = OBJModel(filename).ToIndexedModel();
	InitialiseModel(model);
	Sphere meshCollisionSphere();
}


/* Function for rendering the mesh */

void Mesh::RenderMesh()
{
	glBindVertexArray(vertexArrayObject);
	glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


/* Function for Collision Data */

void Mesh::UpdateCollisionData(glm::vec3 pos, float radius)
{
	meshCollisionSphere.SetPos(pos);
	meshCollisionSphere.SetRadius(radius);
}

