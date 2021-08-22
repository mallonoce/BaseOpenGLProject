#ifndef EXECUTIONER_LIGHT_H
#define EXECUTIONER_LIGHT_H

// Local Headers
#include "glitter.hpp"
#include "camera.h"
#include "Executioner.h"
#include "GLFWManager.h"

    class ExecutionerLight : public Executioner
    {
    public:
        enum class SCENE {NORMAL, DESERT, BIOCHEMICAL, FACTORY, HORROR};
        
        int run();
        int runModelLoading();
        SCENE scene =  SCENE::NORMAL;

    protected:
        void processInputs(GLFWManager* glfwManager);
        bool wireframe = false;
    };


#endif //EXECUTIONER_LIGHT_H