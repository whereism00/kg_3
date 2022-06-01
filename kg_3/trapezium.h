#pragma once
#include <gl/glew.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <../glm/glm.hpp>
#include <../glm/gtc/matrix_transform.hpp>
#include <../glm/gtc/type_ptr.hpp>

const float PI = 3.14159265358979323846f;

class trapezium
{
    int N;

    GLuint side_VBO, bottom_VBO, top_VBO,
		side_VAO, bottom_VAO, top_VAO;

	std::vector<GLfloat> side_vertices;
	std::vector<GLfloat> bottom_vertices;
	std::vector<GLfloat> top_vertices;

public:

    trapezium(int n)
    {
        N = n;
        make_vertices();

		glGenVertexArrays(1, &side_VAO);
		glGenBuffers(1, &side_VBO);

		// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
		glBindVertexArray(side_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, side_VBO);
		glBufferData(GL_ARRAY_BUFFER, side_vertices.size() * sizeof(float), side_vertices.data(), GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// normal attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0); // Unbind VAO

        glGenVertexArrays(1, &bottom_VAO);

        glBindVertexArray(bottom_VAO);
        glGenBuffers(1, &bottom_VBO);

        glBindBuffer(GL_ARRAY_BUFFER, bottom_VBO);
        glBufferData(GL_ARRAY_BUFFER, bottom_vertices.size() * sizeof(float), bottom_vertices.data(), GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0); // Unbind VAO

        glGenVertexArrays(1, &top_VAO);

        glBindVertexArray(top_VAO);
        glGenBuffers(1, &top_VBO);

        glBindBuffer(GL_ARRAY_BUFFER, top_VBO);
        glBufferData(GL_ARRAY_BUFFER, top_vertices.size() * sizeof(float), top_vertices.data(), GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0); // Unbind VAO
    }

    ~trapezium()
    {
        glDeleteVertexArrays(1, &side_VAO);
		glDeleteVertexArrays(1, &top_VAO);
		glDeleteVertexArrays(1, &bottom_VAO);
        glDeleteBuffers(1, &side_VBO);
		glDeleteBuffers(1, &top_VBO);
		glDeleteBuffers(1, &bottom_VBO);
    }

    void draw() const
    {
		glBindVertexArray(bottom_VAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, N);

		glBindVertexArray(top_VAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, N);

		glBindVertexArray(side_VAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4 * N);

		glBindVertexArray(0);
    }

    void make_vertices()
    {
        int i = 0;
        for (int j = 0; j < N; j++)
        {

            float angle = 2 * PI * j / N;
            float c = cosf(angle);
            float s = sinf(angle);

            float next_angle = 2 * PI * (j + 1) / N;
            float next_c = cosf(next_angle);
            float next_s = sinf(next_angle);

            glm::vec3 v1(c * 0.7f, 1.0f, s * 0.7f);
            glm::vec3 v2(c, 0.0f, s);
            glm::vec3 v3(next_c * 0.7f, 1.0f, next_s * 0.7f);
            glm::vec3 v4(next_c, 0.0f, next_s);
            glm::vec3 normal = glm::cross(v2 - v1, v3 - v2);

            side_vertices.push_back(v1.x);
            side_vertices.push_back(v1.y);
            side_vertices.push_back(v1.z);

            side_vertices.push_back(normal.x);
            side_vertices.push_back(normal.y);
            side_vertices.push_back(normal.z);

            side_vertices.push_back(v2.x);
            side_vertices.push_back(v2.y);
            side_vertices.push_back(v2.z);

            side_vertices.push_back(normal.x);
            side_vertices.push_back(normal.y);
            side_vertices.push_back(normal.z);

            side_vertices.push_back(v3.x);
            side_vertices.push_back(v3.y);
            side_vertices.push_back(v3.z);

            side_vertices.push_back(normal.x);
            side_vertices.push_back(normal.y);
            side_vertices.push_back(normal.z);

            side_vertices.push_back(v4.x);
            side_vertices.push_back(v4.y);
            side_vertices.push_back(v4.z);

            side_vertices.push_back(normal.x);
            side_vertices.push_back(normal.y);
            side_vertices.push_back(normal.z);
        }

        i = 0;
        int k = 0;
        float sign;
        for (int j = 0; j < N; j++)
        {
            if (j % 2) sign = -1.0f;
            else sign = 1.0f;

            float angle = sign * ((j + 1) / 2) * 2 * PI / N;
            float c = cosf(angle);
            float s = sinf(angle);
            bottom_vertices.push_back(c);
            bottom_vertices.push_back(0.0f);
            bottom_vertices.push_back(s);

            bottom_vertices.push_back(0.0f);
            bottom_vertices.push_back(-1.0f);
            bottom_vertices.push_back(0.0f);

            top_vertices.push_back(c * 0.7f);
            top_vertices.push_back(1.0f);
            top_vertices.push_back(s * 0.7f);

            top_vertices.push_back(0.0f);
            top_vertices.push_back(1.0f);
            top_vertices.push_back(0.0f);
        }
    }
};