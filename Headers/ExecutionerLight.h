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
        SCENE scene =  SCENE::NORMAL;

    private:
        void processInputs(GLFWManager* glfwManager);
    };


#endif //EXECUTIONER_LIGHT_H