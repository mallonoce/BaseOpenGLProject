#ifndef EXECUTIONER_ADVANCED_GL_H
#define EXECUTIONER_ADVANCED_GL_H

// Local Headers
#include "glitter.hpp"
#include "camera.h"
#include "ExecutionerLight.h"
#include "GLFWManager.h"

    class ExecutionerAdvancedGL : public ExecutionerLight
    {
    public:
        int runDepthBuffer();
    protected:
        void processInputs(GLFWManager* glfwManager);
    };


#endif //EXECUTIONER_ADVANCED_GL_H