#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <math.h>
#include "shader.h"
#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

constexpr unsigned int SCR_WIDTH{ 800 };
constexpr unsigned int SCR_HEIGHT{ 600 };

constexpr float vertices[] = {
    // positions          // colour          // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  0.0f, 1.0f    // top left 
};
constexpr unsigned int indices[]{  // note that we start from 0!
    0, 1, 3,
    1, 2, 3
};

void framebuffer_size_callback(GLFWwindow* window, const int width, const int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    // init/config glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window
    GLFWwindow* window{ glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr) };
    if (window == nullptr) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // init glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    Shader ourShader("assets/shaders/shader.vs", "assets/shaders/shader.fs");

    // register window resize callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // set background colour
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // generate VBO and store buffer id
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // copy vertices into VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // VBO VS VAO
    // VBO - move vertices to gpu once, reuse every frame
    // VAO - how to interpret the VBO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    // EBO - decides order to draw vertices in
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    Texture container("assets/textures/container.jpg", GL_TEXTURE0, GL_RGB);
    Texture awesomeface("assets/textures/awesomeface.png", GL_TEXTURE1, GL_RGBA);
    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);

    // Initialization code (done once, unless object frequently changes)
    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);
    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. then set our vertex attributes pointers
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // colour attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        // clear background to set colour
        glClear(GL_COLOR_BUFFER_BIT);

        // set texture/shader
        ourShader.use();
        container.bind();
        awesomeface.bind();

        // matrices
        glm::mat4 model{ glm::mat4(1.0f) };
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 view{ glm::mat4(1.0f) };
        // note that we're translating the scene in the reverse direction of where we want to move
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        glm::mat4 projection{ glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f) };

        // apply matrices
        int modelLoc = glGetUniformLocation(ourShader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        int viewLoc = glGetUniformLocation(ourShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        int projLoc = glGetUniformLocation(ourShader.ID, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // draw box
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();

    return 0;
}
