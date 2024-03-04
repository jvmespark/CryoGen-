//#define GLEW_STATIC
//#include <gl/glew.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <iostream>

#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
using namespace std;

#include "graphics/shader.h"
#include "objects/camera.h"
#include "graphics/textureManager.h"
#include "graphics/renderer.h"
#include "objects/enemy.h"

const GLuint WIDTH = 1280, HEIGHT = 720;

void keysProcess();
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// opengl
GLuint VAO, VBO;
Shader modelShader;
GLFWwindow* window;
int screenWidth, screenHeight;

void glInit ()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Cryogen", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	//glewExperimental = GL_TRUE;
	//glewInit();
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	glViewport(0, 0, screenWidth, screenHeight);
	glEnable(GL_DEPTH_TEST);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void vaoInit()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}

void vboInit()
{
	// create 1 single vbo to store multiple objects
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

// transform
glm::mat4 model, view, proj;
GLuint modelLoc, viewLoc, projLoc;
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

void initTransform()
{
	modelLoc = glGetUniformLocation(modelShader.Program, "model");
	viewLoc = glGetUniformLocation(modelShader.Program, "view");
	projLoc = glGetUniformLocation(modelShader.Program, "proj");
}


GLfloat currentTime = 0.0f, deltaTime = 0.0f, lastFrame = 0.0f;
int main(int argc, char* argv[])
{	
	glInit();
	vaoInit();
	vboInit();

	modelShader = Shader("src/graphics/shaders/default.vs", "src/graphics/shaders/default.frag");
	renderer* enemy1_renderer = new renderer(modelShader, "src/assets/images/ascii.png");
	renderer* enemy2_renderer = new renderer(modelShader, "src/assets/images/ascii.png");
	renderer* enemy3_renderer = new renderer(modelShader, "src/assets/images/ascii.png");
	initTransform();

	while (!glfwWindowShouldClose(window))
	{
		// calculate deltaTime
		currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		// Start Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		keysProcess();
		modelShader.Use();

		glBindVertexArray(VAO);

		// camera
		view = glm::mat4(1.0f);
		view = camera.GetViewMatrix();
		proj = glm::mat4(1.0f);
		proj = glm::perspective(camera.Zoom, float(screenWidth) / float(screenHeight), 0.1f, 100.0f);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
		
		// render objects
		enemy1_renderer->drawModel(glm::vec3( 0.0f,  0.0f,  0.0f), glm::vec3( 0.2f,  0.2f,  0.2f), 0, glm::vec3( 1.0f,  1.0f,  1.0f), 0, 2);
		enemy2_renderer->drawModel(glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3( 0.5f,  0.5f,  0.5f), 0, glm::vec3( 1.0f,  1.0f,  1.0f), 3, 5);
		enemy3_renderer->drawModel(glm::vec3( -1.0f,  -1.0f,  -1.0f), glm::vec3( 0.1f,  0.1f,  0.1f), 0, glm::vec3( 1.0f,  1.0f,  1.0f), 3, 5);

		// bind to viewport
		glBindVertexArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	TextureManager::Inst()->UnloadAllTextures();
	glfwTerminate();

	return 0;
}

// input handle
bool keys[1024];

void keysProcess()
{
	// get positon data as a msg
	/*
	string x = to_string(camera.Position.x);
	string y = to_string(camera.Position.y);
	string z = to_string(camera.Position.z);
	string msgStr = x + ',' + y + ',' + z;
	char* msg = new char[msgStr.length() + 1]; 
	strcpy(msg, msgStr.c_str());
	send(clientSd, (char*)&msg, strlen(msg), 0);
	*/

	float cameraSpeed = 5.0f * deltaTime;

	if (keys[GLFW_KEY_ESCAPE])
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);

	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (keys[GLFW_KEY_E])
		camera.ProcessKeyboard(UP, deltaTime);
	if (keys[GLFW_KEY_Q])
		camera.ProcessKeyboard(DOWN, deltaTime);
	
	if (keys[GLFW_KEY_L])
		camera.FPS_Camera = !camera.FPS_Camera;
}

bool firstMouse = true;
GLfloat lastX = WIDTH / 2;
GLfloat	lastY = HEIGHT / 2;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;
}