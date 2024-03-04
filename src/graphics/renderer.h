#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "textureManager.h"
#include <iostream>

class renderer {
    public:
        renderer(Shader &shader, const char* texture);

        void drawModel(glm::vec3 position, 
            glm::vec3 size, float rotate, glm::vec3 color, int idx1, int idx2);
    private:
        Shader shader; 
        GLuint VAO;
        GLuint VBO;
        int texId;

        void initRenderData();
        void loadTexture(const char* texture);
        void bindTexture();
};