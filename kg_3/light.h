#pragma once
#include "gl/glew.h"

class light
{
    GLfloat coords[3] = {
            0.0f, 0.0f, 0.0f
    };
    GLuint vao, vbo;

public:
    float size;

    light(float size) : size(size)
    {
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    ~light()
    {
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }

    void draw() const
    {
        glBindVertexArray(vao);
        glPointSize(size);
        glDrawArrays(GL_POINTS, 0, 1);
        glBindVertexArray(0);
    }
};

