#ifndef EXECUTIONER_H
#define EXECUTIONER_H

// Local Headers
#include "glitter.hpp"
#include "camera.h"

    class Executioner
    {
    public:
        int run(const int& code);
    private:
        int _run1();
        int _run2();
        int _run3();
        int _run4();
        int _run5();
    
    public: // camera stuff... should be global?
        Camera camera;
        float lastX;
        float lastY; 
        bool firstMouse;
        float deltaTime;
        float lastFrame;


    };


#endif //EXECUTIONER_H