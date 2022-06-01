#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "trapezium.h"
#include "shader.h"
#include "texture.h"
#include "camera.h"
#include "light.h"
#include "window.h"
#include <iostream>
#include <../glm/glm.hpp>
#include <../glm/gtc/matrix_transform.hpp>
#include <../glm/gtc/type_ptr.hpp>

//trapezium - кол-во граней, высота, радиус
const int t_num = 5;
const float t_height = 3.0f, t_radius = 2.0f;

//позиции источников освещения
const std::vector<glm::vec3> lightPos =
{
	glm::vec3(1.0f, 2.0f, 1.0f),
	glm::vec3(-1.0f, 1.2f, 2.0f),
};

int main()
{
	GLFWwindow* window = init();
	if (window == nullptr)
	{
		return -1;
	}
	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);

	shader shader1("../shaders/vertex_shader.txt", "../shaders/fragment_shader1.txt");
	shader light_shader("../shaders/light_shader.txt", "../shaders/light_fr_shader.txt");

	texture texture1("../images/container.jpg");

	trapezium trap = trapezium(t_num); 

	glm::mat4 projection = glm::perspective(camera.Zoom, (float)width / (float)height, 0.1f, 1000.0f);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(t_radius, t_height, t_radius));

	shader1.use();
	shader1.setMat4("projection", projection);

	// material properties
	//shader1.setFloat("shininess", 32.0f);
	//shader1.setVec3("ambient", glm::vec3{ 0.1f });
	//shader1.setVec3("diffuse", glm::vec3{ 0.5f });
	//shader1.setVec3("specular", glm::vec3{ 1.f });

	glm::mat4 view = camera.GetViewMatrix();
	model = glm::rotate(model, -0.5f, { 1.f, 0.f, 0.f });

	// Light definition
	light light1(15.0f);

	light_shader.use();
	light_shader.setMat4("projection", projection);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		do_movement();

		texture1.use();

		//очистка окна и цветового буфера
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		view = camera.GetViewMatrix();

		shader1.use();
		shader1.setMat4("view", view);
		shader1.setMat4("model", model);
		shader1.setVec3("viewPos", camera.Position);

		trap.draw();

		for (int i = 0; i < lightPos.size(); i++)
		{
			/*// light properties
			shader1.setVec3("Lights[" + std::to_string(i) + "].ambient", 0.2f, 0.2f, 0.2f);
			shader1.setVec3("Lights[" + std::to_string(i) + "].diffuse", 0.5f, 0.5f, 0.5f);
			shader1.setVec3("Lights[" + std::to_string(i) + "].specular", 1.0f, 1.0f, 1.0f);
			shader1.setFloat("Lights[" + std::to_string(i) + "].constant", 1.0f);
			shader1.setFloat("Lights[" + std::to_string(i) + "].linear", 0.09f);
			shader1.setFloat("Lights[" + std::to_string(i) + "].quadratic", 0.032f);
			shader1.setVec3("Lights[" + std::to_string(i) + "].position", lightPos[i]);*/

			glm::mat4 light_model = glm::translate(glm::mat4(1.0f), lightPos[i]);
			light_shader.use();
			light_shader.setMat4("model", light_model);
			light_shader.setMat4("view", view);
			light1.draw();
		}
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

