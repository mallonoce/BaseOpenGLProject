#include "glitter.hpp"

struct Material
{
public:
    static Material GetMaterial(const std::string& materialName);
    void SetMaterial(const glm::vec3& newAmbient, const glm::vec3& newDiffuse, const glm::vec3& newSpecular, float newShininess);

public:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};
