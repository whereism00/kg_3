#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "camera.h"
#include <iostream>

//позиция камеры
Camera camera(glm::vec3(1.0f, 0.0f, 10.0f));

//window size
const GLuint width = 800, height = 600;

GLfloat lastX = width / 2, lastY = height / 2;
bool firstMouse = true;

//массив переменных логического типа, представляющий нажатые или отпущенные состояния клавиш
bool keys[1024];

//нажатие клавиш
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	//клавиша ESC
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

//движение камеры
void do_movement()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

//инициализация окна
GLFWwindow* init()
{
	glfwInit();

	//минимальная требуемая версия opengl - 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//установка профайла для которого создается контекст
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//выключение возможности изменения размера окна
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Window could not be opened." << std::endl;
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(window);

	glewInit();

	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);

	return window;
}
