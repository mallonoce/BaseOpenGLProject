#include "glitter.hpp"

enum class LightTypes {BASE = 0, POINT = 1, DIRECTIONAL = 2, SPOTLIGHT = 3};

/* Table of attenuation levels
* 
Distance	Constant	Linear	    Quadratic
7	        1.0	        0.7	        1.8
13	        1.0	        0.35	    0.44
20	        1.0	        0.22	    0.20
32	        1.0	        0.14	    0.07
50	        1.0	        0.09	    0.032
65	        1.0	        0.07	    0.017
100	        1.0	        0.045	    0.0075
160	        1.0	        0.027	    0.0028
200	        1.0	        0.022	    0.0019
325	        1.0	        0.014	    0.0007
600	        1.0	        0.007	    0.0002
3250	    1.0	        0.0014	    0.000007
*/

class Light
{
public:
    LightTypes GetType (){return LightTypes::BASE;};

    glm::vec3 ambient = glm::vec3(0.2f); // usually set to a low intensity because we don't want the ambient color to be too dominant
    glm::vec3 diffuse = glm::vec3(0.5f); // usually set to the exact color we'd like a light to have; often a bright white color
    glm::vec3 specular = glm::vec3(1.0f); //kept at vec3(1.0) shining at full intensity.

    // attenuation
    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.32f;
};

class PointLight : public Light
{
    public: 

    LightTypes GetType (){return LightTypes::POINT;};
    glm::vec4 position = glm::vec4(glm::vec3(0.0f), 1.0f);
};

class DirectionalLight : public Light
{
public:
    glm::vec3 direction = glm::vec3(1.0f, 0.0f, 0.0f);
    LightTypes GetType (){return LightTypes::DIRECTIONAL;};
};

class SpotLight : public Light
{
public:
    glm::vec4 position = glm::vec4(glm::vec3(0.0f), 1.0f);
    glm::vec3 direction = glm::vec3(1.0f, 0.0f, 0.0f);

    LightTypes GetType (){return LightTypes::SPOTLIGHT;};

    // spotlight 
    float cutOff = 12.5f; // degrees
    float outerCutOff = 17.5f; // degrees
};
