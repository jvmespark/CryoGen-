#include "renderer.h"
#include "../graphics/objLoader.h"

/*
    render bugs:
        - index for attributes not correct
        - texture indexing problems, hard to get multiple objects with different textures
*/

renderer::renderer(Shader &shader, const char* texture) {
    this->shader = shader;
    this->loadTexture(texture);
    this->initRenderData();
}

void renderer::drawModel(glm::vec3 position, glm::vec3 size, float rotate, glm::vec3 color, int idx1, int idx2) {   
    glVertexAttribPointer(idx1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), static_cast<GLvoid *>(nullptr));
	glEnableVertexAttribArray(idx1); 

	glVertexAttribPointer(idx2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(idx2);

    GLuint modelLoc;
    glm::mat4 model;
    modelLoc = glGetUniformLocation(this->shader.Program, "model");

    // prepare transformations
    this->bindTexture();

	model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::scale(model, size);

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	
	glDrawArrays(GL_TRIANGLES, 0, 36);

}

void renderer::loadTexture(const char* texture) {
	TextureManager::Inst()->LoadTexture(texture, this->texId, GL_RGB, GL_RGB, 0, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void renderer::bindTexture()
{
	glActiveTexture(GL_TEXTURE0);
	TextureManager::Inst()->BindTexture(this->texId);
	glUniform1i(glGetUniformLocation(this->shader.Program, "ourTexture"), this->texId);
}

void renderer::initRenderData() {
    // configure VAO/VBO
    // one cube vertices
    GLfloat vertices[] = {
        -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
        1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
        1.0f,  1.0f,  1.0f,  1.0f, 1.0f,
        1.0f,  1.0f,  1.0f,  1.0f, 1.0f,
        -1.0f,  1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,

        -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
        1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
        1.0f,  1.0f,  1.0f,  1.0f, 1.0f,
        1.0f,  1.0f,  1.0f,  1.0f, 1.0f,
        -1.0f,  1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,

        -1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
        -1.0f,  1.0f,  1.0f,  1.0f, 0.0f,

        1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
        1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
        1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
        1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
        1.0f,  1.0f,  1.0f,  1.0f, 0.0f,

        -1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
        1.0f, -1.0f, -1.0f,  1.0f, 1.0f,
        1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
        1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
        -1.0f, -1.0f, -1.0f,  0.0f, 1.0f,

        -1.0f,  1.0f, -1.0f,  0.0f, 1.0f,
        1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
        1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
        1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f,  1.0f,  0.0f, 0.0f,
        -1.0f,  1.0f, -1.0f,  0.0f, 1.0f,
        1.0f,	 1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
        -1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
        1.0f, 	 1.0f,  1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f,  1.0f,  0.0f, 0.0f,
        1.0f,  -1.0f,  1.0f,  0.0f, 1.0f,
    };

	// put the cube data into the vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}