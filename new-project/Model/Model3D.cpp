#include "Model3D.h"
using namespace model;

Model3D::Model3D() {
	this->position = P6::MyVector(0.0f, 0.0f, 0.0f);
	this->scale = P6::MyVector(1.0f, 1.0f, 1.0f);
	this->axis = glm::vec3(0.0f, 1.0f, 0.0f);
	this->theta = glm::vec3(0.0f, 0.0f, 0.0f);
	//this->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    this->color = glm::vec4(254 / 254.0f, 0 / 254.0f, 0 / 254.0f, 1.0f);
	this->mesh_indices = {};
	this->VAO = 0;
    this->shaderProg = NULL;
}

Model3D::Model3D(MyVector scale, glm::vec4 color, GLuint shaderProg) {
    this->position = P6::MyVector(0.0f, 0.0f, 0.0f);
    this->scale = scale;
    this->axis = glm::vec3(0.0f, 1.0f, 0.0f);
    this->theta = glm::vec3(0.0f, 0.0f, 0.0f);
    //this->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    this->color = color;
    this->mesh_indices = {};
    this->VAO = 0;
    this->shaderProg = shaderProg;
}

void Model3D::loadModel(std::string objSrc, GLuint* VBO) {
    std::string path1 = objSrc;
    std::vector <tinyobj::shape_t> shapes1;
    std::vector<tinyobj::material_t> material1;
    std::string warning1, error1;

    tinyobj::attrib_t attributes;

    bool success1 = tinyobj::LoadObj(&attributes, &shapes1, &material1, &warning1, &error1, path1.c_str());

    std::vector<GLuint> mesh_indices1;
    for (int i = 0; i < shapes1[0].mesh.indices.size(); i++)
    {
        mesh_indices1.push_back(shapes1[0].mesh.indices[i].vertex_index);
    }
    this->mesh_indices = mesh_indices1;

    this->bindBuffers(attributes, VBO);   
}

void Model3D::drawModel() {
    glm::mat4 transformation_matrix;
    transformation_matrix = glm::translate(
        glm::mat4(1),
        glm::vec3(this->position.x, this->position.y, this->position.z)
    );

    transformation_matrix = glm::scale(
        transformation_matrix,
        glm::vec3(this->scale.x * 0.03, this->scale.y * 0.03, this->scale.z * 0.03)
    );


    glUseProgram(shaderProg);

    unsigned int transformloc = glGetUniformLocation(shaderProg, "transform");
    glUniformMatrix4fv(transformloc, 1, GL_FALSE, glm::value_ptr(transformation_matrix));

    GLuint colorLoc = glGetUniformLocation(this->shaderProg, "modelColor");
    glUniform4fv(colorLoc, 1, glm::value_ptr(this->color));


    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, this->mesh_indices.size(), GL_UNSIGNED_INT, 0);

}

void Model3D::bindBuffers(tinyobj::attrib_t attributes, GLuint* VBO) {
    GLuint EBO1;
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, VBO);
    glGenBuffers(1, &EBO1);

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * attributes.vertices.size(), &attributes.vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * this->mesh_indices.size(), &this->mesh_indices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Model3D::bindCamera(glm::mat4 projection, glm::mat4 viewMatrix) {
    unsigned int projLoc = glGetUniformLocation(this->shaderProg, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    unsigned int viewLoc = glGetUniformLocation(this->shaderProg, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
}

void Model3D::setScale(MyVector scale) {
    int multiplier = 40.f;
    scale.scalarMultiplication(multiplier);
    this->scale = scale;
}