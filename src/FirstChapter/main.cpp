#include "main.hpp"

#define HEIGHT 800
#define WIDTH 600

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f
};

int init() {
    auto res = glfwInit();
    std::cout << "GLFW init result is " << res << std::endl;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    return 0;
}

typedef std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> ManagedWindow;

ManagedWindow createManagedWindow(GLFWwindow* window) { return ManagedWindow(window, &glfwDestroyWindow); }


void loop() {
    auto managedWindow = createManagedWindow(glfwCreateWindow(HEIGHT, WIDTH, "Test", nullptr, nullptr));
    auto window = managedWindow.get();
    glfwMakeContextCurrent(window);
    glViewport(0, 0, HEIGHT, WIDTH);
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* windo, int w, int h) { glViewport(0, 0, w, h); });
    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

int main() {
    if (init() != 0) return -1;
    
    loop();
    system("pause");

    return 0;
}