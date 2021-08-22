// Local Headers
#include "ExecutionerAdvancedGL.h"
#include "ShaderLoader.h"

#include "utils.h"
#include "camera.h"
#include "Material.h"
#include "Light.h"
#include "Model.h"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <iostream>

#ifdef WINBUILD
#include <windows.h>
#else
#include <unistd.h>
#endif


static ExecutionerAdvancedGL* execAdvanced;

void framebuffer_size_callback_advanced(GLFWwindow* window, int width, int height);
void mouse_callback_advanced(GLFWwindow* window, double xpos, double ypos);
void scroll_callback_advanced(GLFWwindow* window, double xoffset, double yoffset);

int ExecutionerAdvancedGL::runDepthBuffer()
{
    // set the global instance of ExecutionerLight
    execAdvanced = this;

    // camera
    camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    lastX = mWidth / 2.0f;
    lastY = mHeight / 2.0f;
    firstMouse = true;

    // timing
    deltaTime = 0.0f;	// time between current frame and last frame
    lastFrame = 0.0f;

    // lighting
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
    glm::vec3 lightDir(-0.2f, -1.0f, -0.3f);

    GLFWManager glfwManager(mWidth, mHeight, "OpenGL");

    glfwSetFramebufferSizeCallback(glfwManager.GetWindow(), framebuffer_size_callback_advanced);
    glfwSetCursorPosCallback(glfwManager.GetWindow(), mouse_callback_advanced);
    glfwSetScrollCallback(glfwManager.GetWindow(), scroll_callback_advanced);

    // tell GLFW to capture our mouse
    glfwSetInputMode(glfwManager.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    Shader ourShader(utils::getPath("model_loading.vs", utils::fileType::SHADER).c_str(),
        utils::getPath("model_loading.fs", utils::fileType::SHADER).c_str());

    // load models
    // -----------
    Model ourModel(utils::getPath("backpack/backpack.obj", utils::fileType::MESH).c_str());

    // render loop
    // -----------
    while (!glfwWindowShouldClose(glfwManager.GetWindow()))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInputs(&glfwManager);

        // render
        // ------
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // don't forget to enable shader before setting uniforms
        ourShader.use();

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)mWidth / (float)mHeight, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        ourShader.setMat4("model", model);
        ourModel.Draw(ourShader);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(glfwManager.GetWindow());
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback_advanced(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_callback_advanced(GLFWwindow* window, double xpos, double ypos)
{
    if (execAdvanced->firstMouse)
    {
        execAdvanced->lastX = xpos;
        execAdvanced->lastY = ypos;
        execAdvanced->firstMouse = false;
    }

    float xoffset = xpos - execAdvanced->lastX;
    float yoffset = execAdvanced->lastY - ypos; // reversed since y-coordinates go from bottom to top

    execAdvanced->lastX = xpos;
    execAdvanced->lastY = ypos;

    execAdvanced->camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback_advanced(GLFWwindow* window, double xoffset, double yoffset)
{
    execAdvanced->camera.ProcessMouseScroll(yoffset);
}

void ExecutionerAdvancedGL::processInputs(GLFWManager* glfwManager)
{
   // process input
        if (glfwManager->WasKeyPressed(GLFW_KEY_ESCAPE) )
            glfwManager->SetShouldClose(true);
        if (glfwManager->WasKeyPressed(GLFW_KEY_R))
        {
            camera.Position = glm::vec3(0.0f, 0.0f, 0.0f);
            scene = SCENE::NORMAL;
        }
        if (glfwManager->WasKeyPressed(GLFW_KEY_W))
            camera.ProcessKeyboard(FORWARD, deltaTime);
        if (glfwManager->WasKeyPressed(GLFW_KEY_S))
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwManager->WasKeyPressed(GLFW_KEY_A))
            camera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwManager->WasKeyPressed(GLFW_KEY_D))
            camera.ProcessKeyboard(RIGHT, deltaTime);
        if (glfwManager->WasKeyPressed(GLFW_KEY_SPACE))
            camera.ProcessKeyboard(UP, deltaTime);
        if (glfwManager->WasKeyPressed(GLFW_KEY_LEFT_SHIFT))
            camera.ProcessKeyboard(DOWN, deltaTime);
        if (glfwManager->WasKeyPressed(GLFW_KEY_B))
            scene = SCENE::BIOCHEMICAL;
        if (glfwManager->WasKeyPressed(GLFW_KEY_E))
            scene = SCENE::DESERT;
        if (glfwManager->WasKeyPressed(GLFW_KEY_F))
            scene = SCENE::FACTORY;
        if (glfwManager->WasKeyPressed(GLFW_KEY_H))
            scene = SCENE::HORROR;
        if (glfwManager->WasKeyPressed(GLFW_KEY_N))
            scene = SCENE::NORMAL;
        if (glfwManager->WasKeyPressed(GLFW_KEY_Q))
        {
            wireframe = !wireframe;
            if(wireframe)
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else 
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
}
