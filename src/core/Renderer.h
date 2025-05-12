#pragma once

#include "Shader.h"

class Renderer {
public:
    Renderer();
    ~Renderer();

    void init();
    void render();

private:
    unsigned int VAO, VBO;
    Shader* shader;
};
