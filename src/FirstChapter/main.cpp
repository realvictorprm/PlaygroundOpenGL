#include "main.hpp"

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

template<typename T>
auto unwrapOptional(std::optional<T>& opt, const char* failMsg) {
    if (opt.has_value()) return opt.value();
    throw new std::runtime_error(failMsg);
}

auto readCompleteFile (std::string filename) {
    auto file = std::ifstream(filename);
    if (file.is_open()) {
        auto res = std::string();
        file.seekg(0, std::ios::end);
        res.reserve(file.tellg());
        file.seekg(0, std::ios::beg);
        res.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
        return std::make_optional(res);
    }
    else
        return std::optional<std::string>{};
};

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f
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

    auto setupShaders = []() {
        auto createShader = [](std::string& shaderSource, int type) {
            auto shader = glCreateShader(type);
            auto shaderString = shaderSource.c_str();
            glShaderSource(shader, 1, &shaderString, nullptr);
            glCompileShader(shader);
            int success;
            char infoLog[512];
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (success) return std::make_optional(shader);
            else {
                glGetShaderInfoLog(shader, 512, NULL, infoLog);
                std::cerr << "error: " <<
                    infoLog << std::endl;
                return std::optional<GLuint>{};
            }
        };

        auto createShaderProgramm = [](std::vector<unsigned int> shaders) {
            auto shaderProgram = glCreateProgram();
            for (auto shader : shaders) {
                glAttachShader(shaderProgram, shader);
            }
            glLinkProgram(shaderProgram);
            int success = false;
            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
            if (success) return std::make_optional(shaderProgram);
            else {
                char infoLog[512];
                glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
                std::cerr << "error: " << infoLog << std::endl;
                return std::optional<GLuint>{};
            }
        };

        std::string vertexShaderSource =
            unwrapOptional(
                readCompleteFile("../../../shaders/FirstChapter/shader.vert"), 
                "Couldn't find vertex shader"
            );

        std::string fragmentShaderSource =
            unwrapOptional(
                readCompleteFile("../../../shaders/FirstChapter/shader.frag"), 
                "Couldn't find fragment shader"
            );

        GLuint vertexShader =
            unwrapOptional(
                createShader(vertexShaderSource, GL_VERTEX_SHADER), 
                "Couldn't create vertex shader"
            );
        
        GLuint fragmentShader =
            unwrapOptional(
                createShader(fragmentShaderSource, GL_FRAGMENT_SHADER), 
                "Couldn't create fragment shader"
            );

        GLuint shaderProgram = 
            unwrapOptional(
                createShaderProgramm(std::vector<unsigned int>{vertexShader, fragmentShader }), 
                "Couldn't create shader program"
            );
        
        glUseProgram(shaderProgram);

        return ShaderPart{ vertexShader, fragmentShader, shaderProgram };
    };

    auto setupBuffers = []() {
        GLuint VAO, VBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        //// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        //glBindBuffer(GL_ARRAY_BUFFER, 0);

        //// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        //// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        //glBindVertexArray(0);
        return VertexBufferPart{ VAO, VBO };
    };

    // Begin OpenGL stuff

    glViewport(0, 0, HEIGHT, WIDTH);
    auto shaderPart = setupShaders();
    auto bufferPart = setupBuffers();
    return make_tuple(shaderPart, bufferPart);
}

void loop(ManagedWindow& managedWindow, ShaderPart& shader, VertexBufferPart& data) {
    auto window = managedWindow.get();
    while (!glfwWindowShouldClose(window)) {
        // Clear
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwHideWindow(window);
}

void wrappingFunction() {
    try {
        auto test = TUPLE(10, 10);
        auto managedWindow = init();
        auto data = setupOpenGL(managedWindow);
        auto shaderPart = std::get<ShaderPart>(data);
        auto bufferPart = std::get<VertexBufferPart>(data);
        loop(managedWindow, shaderPart, bufferPart);
    }
    catch (std::exception& e) {
        std::cerr << "Application was stopped due to an error" << std::endl;
        std::cerr << e.what() << std::endl;
    }
}

int main() {
    wrappingFunction();
    system("pause");
    return 0;
}