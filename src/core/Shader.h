#pragma once

#include <string>
#include <glad/gl.h>

class Shader {
public:
    unsigned int ID;

    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    void use() const;

    // Utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;

private:
    std::string readFile(const std::string& path);
    void checkCompileErrors(unsigned int shader, std::string type);
};
