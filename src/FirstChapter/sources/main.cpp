#include "../headers/main.hpp"

#define TUPLE std::make_tuple
typedef std::chrono::duration<int, std::ratio<1, 30>> frame_duration;

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

//float vertices[] = {
//    // positions          // colors           // texture coords
//    0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
//    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
//    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
//    -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
//};

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
    0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
    0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
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
        system("pause");
    }
};

ManagedWindow init() {
    auto res = glfwInit();
    glfwSetErrorCallback([](int a, const char* msg) {std::cerr << "GLFW error occured, code " << a << ", message: " << msg << std::endl; });
    std::cout << "GLFW init result is " << res << std::endl;
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    auto managedWindow = createManagedWindow(glfwCreateWindow(mode->width, mode->height, "Test", nullptr, nullptr));
    auto window = managedWindow.get();
    glfwMakeContextCurrent(window);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    auto ret = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (!ret) throw new std::runtime_error("Error initializing OpenGL functions");
    glViewport(0, 0, mode->width, mode->height);

    // Global important callbacks
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* windo, int w, int h) { 
        glViewport(0, 0, w, h); 
    });
    glfwSetKeyCallback(window, [](GLFWwindow* w, int a, int b, int c, int d) {
        if (glfwGetKey(w, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetInputMode(w, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    });
    glfwSetCursorEnterCallback(window, [](GLFWwindow* w, int entered){
        if(entered == GLFW_TRUE)
            glfwSetInputMode(w, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    });
    return managedWindow;
}

auto setupOpenGL(ManagedWindow managedWindow) {
    using namespace std;
    auto window = managedWindow.get();

    auto setupBuffers = []() {

        unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        /*glGenBuffers(1, &EBO);*/
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        /*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Unbind the buffers for safety reasons
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        checkGLError();
        return VertexBufferPart{ VAO, VBO };
    };

    auto setupTextures = []() {
        Texture wallTexture("../../../../resources/wall.jpg");
        Texture containerTexture("../../../../resources/container.jpg");
        return std::vector<Texture>({wallTexture, containerTexture});
    };

    // Begin OpenGL stuff
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
    glEnable(GL_DEPTH_TEST);
    std::experimental::filesystem::path vertexPath("../../../shaders/FirstChapter/SimpleLight.vert");
    std::experimental::filesystem::path fragmentPath("../../../shaders/FirstChapter/SimpleLight.frag");
    std::experimental::filesystem::path vertexPath2("../../../shaders/FirstChapter/SimpleLamp.vert");
    std::experimental::filesystem::path fragmentPath2("../../../shaders/FirstChapter/SimpleLamp.frag");

    auto bufferPart = setupBuffers();
    auto textures = setupTextures();
    Shader lightShader(vertexPath, fragmentPath);
    Shader lampShader(vertexPath2, fragmentPath2);
    lightShader.use();
    return make_tuple(lightShader, lampShader, bufferPart, textures);
}

void loop(ManagedWindow& managedWindow, Shader& lightShader, Shader& lampShader, VertexBufferPart& data, std::vector<Texture> textures) {
    auto window = managedWindow.get();

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBindVertexArray(data.vao);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data.ebo);

    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    Camera camera;

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), (float)100. / (float)100., 0.1f, 100.0f);

    lightShader.setMat4("projection", projection);
    lightShader.setVec3("lightPos", lightPos);
    lightShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    lightShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);


    auto getMousePos = [&]{
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        return std::make_tuple(xpos, ypos);
    };

    auto processInput = [&](float dt, double xbefore, double ybefore) {
        float cameraSpeed = 2.5f * dt;
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            auto[x, y] = getMousePos();
            auto[dx, dy] = std::make_tuple(x - xbefore, ybefore - y);
            camera.ProcessMouseMovement(dx, dy);
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            dt *= 3;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(Camera_Movement::FORWARD, dt);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(Camera_Movement::BACKWARD, dt);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(Camera_Movement::LEFT, dt);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(Camera_Movement::RIGHT, dt);
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            camera.ProcessKeyboard(Camera_Movement::UP, dt);
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            camera.ProcessKeyboard(Camera_Movement::DOWN, dt);
    }; 
    auto drawGL =  [&]() {
        // Clear
        glClearColor(0.1f, 0.3f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 model, normalModel;
        lightShader.use();
        //model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.f), glm::vec3(0.5f, 1.0f, 0.0f));
        normalModel = glm::transpose(glm::inverse(model));
        lightShader.setMat4("model", model);
        lightShader.setMat4("normalModel", normalModel);
        lightShader.setMat4("view", camera.GetViewMatrix());
        lightShader.setFloat("time", (float)glfwGetTime());
        lightShader.setVec3("viewPos", camera.Position);
        Material::use(GOLD, lightShader);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        model = glm::translate(model, glm::vec3(5., 0., 0.));
        lightShader.setMat4("model", model);
        Material::use(COPPER, lightShader);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        lampShader.use();
        model = glm::translate(glm::mat4(), lightPos);
        lampShader.setMat4("model", model);
        lampShader.setMat4("view", camera.GetViewMatrix());
        lampShader.setMat4("projection", projection);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    };

    auto start_time = std::chrono::steady_clock::now();
    auto end_time = start_time + frame_duration(1);
    auto processing_time = start_time - std::chrono::steady_clock::now();
    auto[xBefore, yBefore] = std::make_tuple( 400., 300. );
    while (!glfwWindowShouldClose(window)) {
        start_time = std::chrono::steady_clock::now();
        end_time = start_time + frame_duration(1);
        drawGL();

        //GLint colorLocation = glGetUniformLocation(shader.program, "globalTime");
        //glUniform1f(colorLocation, (float)glfwGetTime());
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        checkGLError();
        glfwSwapBuffers(window);
        glfwPollEvents();
        processInput(0.01f, xBefore, yBefore);
        processing_time = std::chrono::steady_clock::now() - start_time;
        // std::cout << processing_time.count() << std::endl;
        std::tie(xBefore, yBefore) = getMousePos();
        std::this_thread::sleep_until(end_time);
    }
    glfwHideWindow(window);
}

void wrappingFunction() {
    try { 
        auto managedWindow = init();
        auto [lightShader, lampShader, bufferPart, textures] = setupOpenGL(managedWindow);
        loop(managedWindow, lightShader, lampShader, bufferPart, textures);
    }
    catch (std::exception& e) {
        std::cerr << "Application was stopped due to an error" << std::endl;
        std::cerr << e.what() << std::endl;
    }
}

int main() {
    std::cout << "Hello world!" << std::endl;
    wrappingFunction();
    system("pause");
    return 0;
}