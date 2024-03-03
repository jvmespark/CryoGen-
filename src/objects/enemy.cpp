#include "enemy.h"

void drawEnemy(glm::mat4 model, GLuint modelLoc, glm::vec3 position)
{
	model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	//model = glm::rotate(model, glm::radians(GLfloat(glfwGetTime()) * 20.0f * (index + 1)), glm::vec3(1.0f, 0.3f, 0.5f));
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
}