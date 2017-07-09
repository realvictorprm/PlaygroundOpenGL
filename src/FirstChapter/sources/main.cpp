#include "../headers/main.hpp"

#define HEIGHT 800
#define WIDTH 600

#define TUPLE std::make_tuple

auto TryOrFailwith(std::function<bool(void)> fun, const char* msg){
    auto success = false;
    try {
        success = fun();
    }
    catch (std::exception& e) {
        std::cerr << "exception occured: " << e.what() << std::endl;
    }
    if (!success) {
        std::cerr << msg << std::endl;
        system("pause");
        std::exit(-1);
    }
}



float vertices[] = {
    // positions          // colors           // texture coords
    0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};

float texCoords[] = {
    0.0f, 0.0f,  // lower-left corner  
    1.0f, 0.0f,  // lower-right corner
    0.5f, 1.0f   // top-center corner
};

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};

// logs every gl call to the console
void pre_gl_call(const char *name, void *funcptr, int len_args, ...) {
    printf("Calling: %s (%d arguments)\n", name, len_args);
}

typedef std::shared_ptr<GLFWwindow> ManagedWindow;

auto createManagedWindow(GLFWwindow* window) {
    return ManagedWindow(window, [](GLFWwindow*w) {
        glfwHideWindow(w);
        std::cout << "destroying glfw window" << std::endl;
        glfwDestroyWindow(w); 
    });
}

auto glErrorToString(GLuint& error) {
    switch (error) {
    case GL_INVALID_ENUM:
        return "GL_INVALID_ENUM";
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        return "GL_INVALID_FRAMEBUFFER_OPERATION";
    case GL_OUT_OF_MEMORY:
        return "GL_OUT_OF_MEMORY";
    case GL_INVALID_VALUE:
        return "GL_INVALID_VALUE";
    case GL_INVALID_OPERATION:
        return "GL_INVALID_OPERATION";
    default:
        return "unkown";
    }
}

auto checkGLError = []() {
    auto error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "error code "<< error << ", " << glErrorToString(error) << std::endl;
        
    }
};

ManagedWindow init() {
    auto res = glfwInit();
    glfwSetErrorCallback([](int a, const char* msg) {std::cerr << "GLFW error occured, code " << a << ", message: " << msg << std::endl; });
    std::cout << "GLFW init result is " << res << std::endl;
    auto managedWindow = createManagedWindow(glfwCreateWindow(HEIGHT, WIDTH, "Test", nullptr, nullptr));
    auto window = managedWindow.get();
    glfwMakeContextCurrent(window);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* windo, int w, int h) { glViewport(0, 0, w, h); });
    auto ret = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (!ret) throw new std::runtime_error("Error initializing OpenGL functions");
    return managedWindow;
}

auto setupOpenGL(ManagedWindow managedWindow) {
    using namespace std;
    auto window = managedWindow.get();

    auto setupBuffers = []() {

        unsigned int VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // Unbind the buffers for safety reasons
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

/*
        glBindBuffer(GL_ARRAY_BUFFER, 0);*/
        
        //glBindVertexArray(0);

        checkGLError();

        //// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        //glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        
        //// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        //// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        //glBindVertexArray(0);
        return VertexBufferPart{ VAO, VBO, EBO };
    };

    auto setupTextures = []() {
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load and generate the texture
        int width, height, nrChannels;
        unsigned char* data = stbi_load("../../../../resources/wall.jpg", &width, &height, &nrChannels, 0);
        if (data){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else
            std::cout << "Failed to load texture" << std::endl;
        stbi_image_free(data);
    };

    // Begin OpenGL stuff
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
    glViewport(0, 0, HEIGHT, WIDTH);
    std::experimental::filesystem::path vertexPath("../../../shaders/FirstChapter/shader.vert");
    std::experimental::filesystem::path fragmentPath("../../../shaders/FirstChapter/shader.frag");

    auto bufferPart = setupBuffers();
    setupTextures();
    Shader shader(vertexPath, fragmentPath);
    shader.use();
    return make_tuple(shader, bufferPart);
}

void loop(ManagedWindow& managedWindow, Shader& shader, VertexBufferPart& data) {
    auto window = managedWindow.get();
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBindVertexArray(data.vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data.ebo);
    while (!glfwWindowShouldClose(window)) {
        // Clear
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //GLint colorLocation = glGetUniformLocation(shader.program, "globalTime");
        //glUniform1f(colorLocation, (float)glfwGetTime());
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        checkGLError();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwHideWindow(window);
}

void wrappingFunction() {
    try { 
        auto managedWindow = init();
        auto [shader, bufferPart] = setupOpenGL(managedWindow);
        loop(managedWindow, shader, bufferPart);
    }
    catch (std::exception& e) {
        std::cerr << "Application was stopped due to an error" << std::endl;
        std::cerr << e.what() << std::endl;
    }
    catch (std::runtime_error& e) {
        std::cerr << "Application was stopped due to an error" << std::endl;
        std::cerr << e.what() << std::endl;
    }
    /*catch (...) {
        std::cerr << "Caught unkown runtime error!" << std::endl;
    }*/
}

int main() {
    std::cout << "Helo world!" << std::endl;
    wrappingFunction();
    system("pause");
    return 0;
}