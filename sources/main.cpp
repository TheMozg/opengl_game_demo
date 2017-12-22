#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "quad.hpp"
#include "octahedron.hpp"
#include "map.hpp"
#include "shadow.hpp"

#include <iostream>
#include <list>
#include <memory>

Camera camera(glm::vec3(20.0f, 2.0f, 10.0f), 180.0f, 0.0f);

std::list<std::unique_ptr<OpenGLModel>> objects;
std::vector<std::shared_ptr<Texture>> textures;

std::unique_ptr<Octahedron> portal1;
std::unique_ptr<Octahedron> portal2;

bool upJetpackMode = false;
const float upJumpVelocity = 5.0f;
const float upAcceleration = -9.8;
float upVelocity = 0.0f;
bool upCollision = true;

double last_xpos;
double last_ypos;

double deltaTime = 0.0f;
double lastFrame = 0.0f;

void processInput(GLFWwindow *window) {
    upVelocity += upAcceleration * deltaTime;

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
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        if (upJetpackMode || upCollision){
            upVelocity = upJumpVelocity;
        }
    }

    auto cameraPosNew = camera.getPosition();
    cameraPosNew.y += upVelocity * deltaTime;

    auto cameraPos = cameraPosOld;
    for (size_t i = 0; i < 3; i++ ) {
        if (i == 1) {
            upCollision = false;
        }
        cameraPos[i] = cameraPosNew[i];
        for (auto &obj : objects) {
            if (obj->collidesWith(cameraPos, {0.15f, 0.15f}, {0.05f, 0.75f}, {0.15f, 0.15f})) {
                if (i == 1) {
                    upCollision = true;
                    upVelocity = 0.0f;
                }
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


std::unique_ptr<Octahedron> spawn_portal( ) {
    auto portal = std::make_unique<Octahedron>(textures[3]);
    portal->move(camera.getPosition() + camera.getDirection());
    portal->velocity = camera.getDirection();
    return portal;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_J && action == GLFW_PRESS)
        upJetpackMode = !upJetpackMode;

    if (key == GLFW_KEY_E && action == GLFW_PRESS) {
        portal1 = spawn_portal();
    }
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
    glfwWindowHint(GLFW_SAMPLES, 4);
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

    glfwSetKeyCallback(window, key_callback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        error_callback(42, "Failed to initialize GLAD");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glEnable(GL_DEPTH_TEST);

    textures.push_back(std::make_shared<Texture>("textures/portal_black.png"));
    textures.push_back(std::make_shared<Texture>("textures/portal_white.jpg"));
    textures.push_back(std::make_shared<Texture>("textures/portal_white_2.jpg"));
    textures.push_back(std::make_shared<Texture>("textures/orange_noise.png"));

    objects = Map::load("maps/map01.bmp", textures);
    Shader screenShader;
    screenShader.attach("shaders/shadows.frag");
    screenShader.attach("shaders/shadows.vert");
    screenShader.link();

    Shader shadowShader;
    shadowShader.attach("shaders/shadows_depth.frag");
    shadowShader.attach("shaders/shadows_depth.geom");
    shadowShader.attach("shaders/shadows_depth.vert");
    shadowShader.link();

    screenShader.activate();
    screenShader.setInt("diffuseTexture", 0);
    screenShader.setInt("depthMap", 1);

    ShadowCubeMap depthCubemap;
    depthCubemap.setPosition(camera.getPosition());

    unsigned int depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap.getID(), 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    while (!glfwWindowShouldClose(window)) {
        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        if (deltaTime > 0.2) {
            deltaTime = 0.2;
        }
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (portal1) {
            portal1->move(portal1->getPosition() + portal1->velocity*(float)deltaTime*3.0f);
            for (auto &obj : objects) {
                if (obj->collidesWith(portal1->getPosition(), 0.1f)) {
                    portal1.reset();
                    break;
                }
            }
        }
        if (portal1) depthCubemap.setPosition(portal1->getPosition());
        depthCubemap.activate();

        glViewport(0, 0, 1024, 1024);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);
        shadowShader.activate();
        for (unsigned int i = 0; i < 6; ++i)
            shadowShader.setMat4("shadowMatrices[" + std::to_string(i) + "]", depthCubemap.getTransforms()[i]);
        shadowShader.setFloat("far_plane", 25.0f);
        shadowShader.setVec3("lightPos", depthCubemap.getPosition());

        for (auto &obj : objects) {
            obj->draw(shadowShader.getUniformLocation("model"));
        }
        if (portal1) portal1->draw(shadowShader.getUniformLocation("model"));

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        int width, height;
        glfwGetFramebufferSize(window, &width,&height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        screenShader.activate();
        glm::mat4 projection = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
        glm::mat4 view = camera.getViewMatrix();
        screenShader.setMat4("projection", projection);
        screenShader.setMat4("view", view);
        screenShader.setVec3("lightPos", depthCubemap.getPosition());
        screenShader.setVec3("viewPos", camera.getPosition());
        screenShader.setFloat("far_plane", 25.0f);

        for (auto &obj : objects) {
            obj->draw(screenShader.getUniformLocation("model"));
        }
        if (portal1) portal1->draw(screenShader.getUniformLocation("model"));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}
