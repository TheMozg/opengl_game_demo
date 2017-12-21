#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "quad.hpp"
#include "map.hpp"

#include <iostream>
#include <list>
#include <memory>

Camera camera(glm::vec3(20.0f, 1.0f, 10.0f), 180.0f, 0.0f);

std::list<std::unique_ptr<OpenGLModel>> objects;

double last_xpos;
double last_ypos;

double deltaTime = 0.0f;
double lastFrame = 0.0f;

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    auto cameraPosOld = camera.getPosition();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyboard(CameraMovement::FORWARD, (float)deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyboard(CameraMovement::BACKWARD, (float)deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyboard(CameraMovement::LEFT, (float)deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyboard(CameraMovement::RIGHT, (float)deltaTime);

    auto cameraPosNew = camera.getPosition();

    auto cameraPos = cameraPosOld;
    for (size_t i = 0; i < 3; i++ ) {
        cameraPos[i] = cameraPosNew[i];
        for (auto &obj : objects) {
            if (obj->collidesWith(cameraPos, 0.3)) {
                cameraPos[i] = cameraPosOld[i];
                break;
            }
        }
    }

    camera.setPosition(cameraPos);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
    double xoffset = xpos - last_xpos;
    double yoffset = last_ypos - ypos;

    last_xpos = xpos;
    last_ypos = ypos;

    camera.processMouse((float)xoffset, (float)yoffset);
}

void error_callback(int error, const char* description) {
    std::cerr << "ERROR: " << description << std::endl;
}

int main() {
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL game demo", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwGetCursorPos(window, &last_xpos, &last_ypos);
    glfwSetCursorPosCallback(window, cursor_pos_callback);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        error_callback(42, "Failed to initialize GLAD");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glEnable(GL_DEPTH_TEST);

    Shader ourShader;
    ourShader.attach("shaders/camera.frag");
    ourShader.attach("shaders/camera.vert");
    ourShader.link();

    std::vector<std::shared_ptr<Texture>> textures;
    textures.push_back(std::make_shared<Texture>("textures/portal_black.png"));
    textures.push_back(std::make_shared<Texture>("textures/portal_white.jpg"));
    textures.push_back(std::make_shared<Texture>("textures/portal_white_2.jpg"));

    objects = Map::load("maps/map01.bmp", textures);

    ourShader.activate();

    while (!glfwWindowShouldClose(window)) {
        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        int width, height;
        glfwGetFramebufferSize(window, &width,&height);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
        glUniformMatrix4fv(ourShader.getUniformLocation("projection"), 1, GL_FALSE, &projection[0][0]);

        glm::mat4 view = camera.getViewMatrix();
        glUniformMatrix4fv(ourShader.getUniformLocation("view"), 1, GL_FALSE, &view[0][0]);

        for (auto &obj : objects) {
            obj->draw(ourShader.getUniformLocation("model"));
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}
