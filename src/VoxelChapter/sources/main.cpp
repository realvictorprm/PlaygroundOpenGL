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

float skyboxVertices[] = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f,  1.0f
};


std::experimental::filesystem::path vertexPath("../shaders/FirstChapter/SimpleLight.vert");
std::experimental::filesystem::path fragmentPath("../shaders/FirstChapter/SimpleLight.frag");

std::experimental::filesystem::path lampVertexPath("../shaders/FirstChapter/SimpleLamp.vert");
std::experimental::filesystem::path lampFragmentPath("../shaders/FirstChapter/SimpleLamp.frag");

std::experimental::filesystem::path skyboxVertexPath("../shaders/FirstChapter/SimpleSkybox.vert");
std::experimental::filesystem::path skyboxFragmentPath("../shaders/FirstChapter/SimpleSkybox.frag");

struct DynamicEnvironmentMap {
    GLuint framebuffer;
    GLuint cubemap;
};

struct ApplicationData {
    Shader lightShader;
    Shader lampShader;
    Shader skyboxShader;
    std::vector<Model> models;
    std::vector<VertexBufferPart> buffers;
    std::vector<Texture> textures;
    Cubemap skybox;
    DynamicEnvironmentMap map;
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
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
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
        glBindVertexArray(0);

        checkGLError();
        std::cout << "created vao" << std::endl;
        return VertexBufferPart{ VAO, VBO };
    };

    auto setupSkybox = []() {
        unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindVertexArray(0);

        checkGLError();
        return VertexBufferPart{ VAO, VBO };
    };

    auto setupTextures = []() {
        Texture wallTexture("../../resources/wall.jpg");
        Texture containerTexture("../../resources/container.jpg");
        return std::vector<Texture>({wallTexture, containerTexture});
    };


    // Begin OpenGL stuff
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
    glEnable(GL_DEPTH_TEST);

    auto bufferPart = setupBuffers();
    auto textures = setupTextures();
    Shader lightShader(vertexPath, fragmentPath);
    Shader lampShader(lampVertexPath, lampFragmentPath);
    Shader skyboxShader(skyboxVertexPath, skyboxFragmentPath);
    lightShader.use();
    auto buffers = { bufferPart, setupSkybox() };
    auto relativeModelPath = std::experimental::filesystem::path("../../models/tasse/Tasse.obj");
    auto absModelPath = std::experimental::filesystem::canonical(relativeModelPath);
    auto model = Model::load(absModelPath.generic_string());
    auto skyboxPath = std::string("../../resources/skybox/");
    std::array<std::string, 6> skyboxTextures{ 
        skyboxPath + "right.jpg",
        skyboxPath + "left.jpg",
        skyboxPath + "top.jpg",
        skyboxPath + "bottom.jpg",
        skyboxPath + "back.jpg",
        skyboxPath + "front.jpg"
    };
    auto skybox = Cubemap::create(skyboxTextures);
    
    unsigned int fbo;
    glGenFramebuffers(1, &fbo);

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    GLuint cubemap;
    glGenTextures(1, &cubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    for (unsigned int i = 0; i < 6; i++) {
        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
            0, GL_RGBA, mode->width, mode->width, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    }
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    checkGLError();
    return ApplicationData{ 
        lightShader, lampShader, skyboxShader, 
        std::vector<Model>{ model }, buffers, textures, skybox,
        DynamicEnvironmentMap{fbo, cubemap}
    };
}

struct VertexAndNormal {
    glm::vec3 vertex;
    glm::vec3 normal;
};

void loop(ManagedWindow& managedWindow, ApplicationData& d) {
    auto window = managedWindow.get();
    auto lightShader = d.lightShader;
    auto lampShader = d.lampShader;
    auto textures = d.textures;

    auto model = d.models.front();
    auto data = d.buffers.front();

    auto skyboxData = d.buffers[1];
    auto skyboxShader = d.skyboxShader;
    checkGLError();
    std::printf("creating surface nets");

    auto res = SurfaceExtraction::Interpolate::createSurfaceNets(SurfaceExtraction::VoxelData<float, float>::createTorus(1., 1., 1.), 1, 0.);
    std::vector<float> vertices = std::get<0>(res);
    std::vector<size_t> faces = std::get<1>(res);
    std::vector<uint32_t> indicies;
    std::vector<VertexAndNormal> surfaceData(vertices.size() / 3);

    // Quads to triangles
    for (uint32_t i = 0; i < faces.size() / 4; i++) {
        auto f0 = faces[4 * i], f1 = faces[4 * i + 1],
            f2 = faces[4 * i + 2], f3 = faces[4 * i + 3];
        indicies.push_back(f0);
        indicies.push_back(f1);
        indicies.push_back(f2);
        indicies.push_back(f0);
        indicies.push_back(f2);
        indicies.push_back(f3);
        std::array<uint32_t, 4> f = {
            f0 * 3, f1 * 3, f2 * 3, f3 * 3
        };
        std::vector<glm::vec3> triple;
        for (auto& ff : f)
            triple.push_back(glm::vec3(vertices[ff], vertices[ff + 1], vertices[ff + 2]));
        
        auto n0 = -glm::cross(triple[1] - triple[0], triple[2] - triple[0]);

        surfaceData[f0] = (VertexAndNormal{ triple[0], n0 });
        surfaceData[f1] = (VertexAndNormal{ triple[1], n0 });
        surfaceData[f2] = (VertexAndNormal{ triple[2], n0 });
        surfaceData[f3] = (VertexAndNormal{ triple[3], n0 });
    }

    std::printf("size of vertices: %u, size of faces: %u, sizeof surfaceData: %u\n", vertices.size(), faces.size(), surfaceData.size());

    GLuint voxelVertexObject, surfaceNetsVertices, elementBuffer, normalsV;

    glGenVertexArrays(1, &voxelVertexObject);

    glGenBuffers(1, &surfaceNetsVertices);
    glGenBuffers(1, &elementBuffer);
    glBindVertexArray(voxelVertexObject);

    glBindBuffer(GL_ARRAY_BUFFER, surfaceNetsVertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexAndNormal) * surfaceData.size(), &surfaceData[0], GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAndNormal), (void*)(offsetof(VertexAndNormal, vertex)));
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAndNormal), (void*)(offsetof(VertexAndNormal, normal)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indicies.size(), &indicies[0], GL_STATIC_DRAW);

    glBindVertexArray(0);

    std::mutex glOperationRunning;
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    /*glBindVertexArray(data.vao);*/
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data.ebo);

    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    Camera camera;

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), (float)100. / (float)100., 0.01f, 100.0f);

    lightShader.use();
    lightShader.setMat4("projection", projection);
    lightShader.setVec3("lightPos", lightPos);
    lightShader.setVec3("objectColor", 1.f, 1.f, 1.f);
    lightShader.setVec3("lightColor", 1.f, 1.0f, 1.0f);
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    auto getMousePos = [&]{
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        return std::make_tuple(xpos, ypos);
    };

    auto processInput = [&](float dt, double xbefore, double ybefore) {
        float cameraSpeed = 1.f * dt;
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            auto[x, y] = getMousePos();
            auto[dx, dy] = std::make_tuple(x - xbefore, ybefore - y);
            camera.ProcessMouseMovement(dx, dy);
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            dt *= 3.;
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
        //auto radians = [] (float degree) {
        //    return (degree * AI_MATH_PI_F) / 180.f;
        //};
        //glDepthMask(GL_FALSE);
        //skyboxShader.use();
        //Cubemap::use(d.skybox);
        //skyboxShader.setMat4("projection", projection);
        //skyboxShader.setMat4("view", glm::mat4(glm::mat3(camera.GetViewMatrix())));
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        //glDepthMask(GL_TRUE);
        //glBindFramebuffer(GL_FRAMEBUFFER, d.map.framebuffer);
        ///*unsigned int rbo;
        //glGenRenderbuffers(1, &rbo);
        //glBindRenderbuffer(GL_RENDERBUFFER, rbo);
        //glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, mode->width, mode->height);
        //glBindRenderbuffer(GL_RENDERBUFFER, 0);
        //glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);*/
        //auto mappingProjection = glm::perspective(glm::radians(90.f), (float)100. / (float)100., 0.01f, 100.0f);
        //skyboxShader.setMat4("projection", mappingProjection);
        //float translationValues[]{
        //    // pitch, yaw
        //    0., 0., // right
        //    0., 90, // left
        //    90., 0., // top
        //    -90., 0., // bottom
        //    0., -90., // back
        //    0., 180. // front
        //};
        //



        //glViewport(0, 0, mode->width, mode->width);
        //for (unsigned int i = 0; i < 6; i++) {
        //    glFramebufferTexture2D(
        //        GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, d.map.cubemap, 0
        //    );
        //    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != (GLuint)oglplus::FramebufferStatus::Complete) {
        //        auto status = oglplus::Framebuffer::Status(oglplus::FramebufferTarget::Draw);
        //        std::cout << oglplus::EnumValueName(status) << std::endl;
        //        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
        //    }
        //    glClearColor(0.0f, 0.9f, 0.8f, 1.0f);
        //    if (i = 5) {
        //        glClearColor(1.0f, 0.f, 0.f, 1.0f);
        //    }
        //    glClear(GL_COLOR_BUFFER_BIT);
        //    skyboxShader.use();
        //    auto mappingCamera = Camera(camera);
        //    mappingCamera.Pitch = translationValues[2 * i];
        //    mappingCamera.Yaw = translationValues[2 * i + 1];
        //    auto untranslatedViewMat = glm::mat4(glm::mat3(mappingCamera.GetViewMatrix()));
        //    // glm::rotate(untranslatedViewMat, radians(90.), glm::vec3(1.0, 0., 0.))
        //    skyboxShader.setMat4("view", untranslatedViewMat);
        //    Cubemap::use(d.skybox);
        //    glDepthMask(GL_FALSE);
        //    glBindVertexArray(skyboxData.vao);
        //    glDrawArrays(GL_TRIANGLES, 0, 36);
        //    glDepthMask(GL_TRUE);

        //    lightShader.use();
        //    Cubemap::use(d.skybox);
        //    glm::mat4 m = glm::translate(glm::mat4(), glm::vec3(0.0f, -1.75f, -10.0f)); // translate it down so it's at the center of the scene
        //    m = glm::scale(m, glm::vec3(10., 10., 5.));
        //    glm::mat4 normalModel = glm::transpose(glm::inverse(m));
        //    Material::use(WHITE, lightShader);
        //    lightShader.setMat4("model", m);
        //    lightShader.setMat4("normalModel", normalModel);
        //    lightShader.setMat4("view", mappingCamera.GetViewMatrix());
        //    //model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.f), glm::vec3(0.5f, 1.0f, 0.0f));

        //    lightShader.setFloat("time", (float)glfwGetTime());
        //    lightShader.setVec3("viewPos", mappingCamera.Position);
        //    glDrawArrays(GL_TRIANGLES, 0, 36);

        //    lampShader.use();
        //    glBindVertexArray(data.vao);
        //    auto model = glm::translate(glm::translate(glm::mat4(), lightPos), glm::vec3(2. * sin(glfwGetTime()), 1. * cos(glfwGetTime()), 0.));
        //    lampShader.setMat4("model", model);
        //    lampShader.setMat4("view", mappingCamera.GetViewMatrix());
        //    lampShader.setMat4("projection", mappingProjection);
        //    lampShader.setFloat("time", (float)glfwGetTime());
        //    glDrawArrays(GL_TRIANGLES, 0, 36);
        //    checkGLError();
        //}
        //glBindFramebuffer(GL_FRAMEBUFFER, 0);
        //glViewport(0, 0, mode->width, mode->height);
        //
        //lightShader.use();
        //lightShader.setBool("useTexture", true);
        //lightShader.setInt("texture_specular1", 2);
        //glBindTexture(GL_TEXTURE_2D, d.textures[0].ID);
        //glm::mat4 m = glm::translate(glm::mat4(), glm::vec3(0.0f, -1.75f, -10.0f)); // translate it down so it's at the center of the scene
        //m = glm::scale(m, glm::vec3(10., 10., 5.));
        //glm::mat4 normalModel = glm::transpose(glm::inverse(m));
        //Material::use(WHITE, lightShader);
        //glBindTexture(GL_TEXTURE_CUBE_MAP, d.map.cubemap);
        //lightShader.setMat4("model", m);
        //lightShader.setMat4("normalModel", normalModel);
        //lightShader.setMat4("view", camera.GetViewMatrix());
        ////model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.f), glm::vec3(0.5f, 1.0f, 0.0f));
        //
        //lightShader.setFloat("time", (float)glfwGetTime());
        //lightShader.setVec3("viewPos", camera.Position);
        ////Material::use(GOLD, lightShader);
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        glDepthFunc(GL_LESS);
        lightShader.use();
        /*glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);*/
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glViewport(0, 0, mode->width, mode->height);
        Cubemap::use(d.skybox);
        glm::mat4 m = glm::scale(glm::mat4(), glm::vec3(0.1, 0.1, 0.1));
        glm::mat4 normalModel = glm::transpose(glm::inverse(m));
        Material::use(WHITE, lightShader);
        lightShader.setMat4("model", glm::translate(m, glm::vec3(0.0f, -10., -10.0f)));
        lightShader.setMat4("normalModel", normalModel);
        lightShader.setMat4("view", camera.GetViewMatrix());
        lightShader.setVec3("viewPos", camera.Position);
        lightShader.setVec3("lightPos", lightPos + glm::vec3(2. * sin(glfwGetTime()), 1. * cos(glfwGetTime()), 0.));

        glBindVertexArray(voxelVertexObject);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
        glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0);
        glDepthFunc(GL_LEQUAL);
        Material::use(COPPER, lightShader);
        m = glm::scale(glm::mat4(), glm::vec3(0.1, 0.1, 0.1));
        lightShader.setMat4("model", glm::translate(m, glm::vec3(0.0f, -10., -10.0f)));
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(3.0);
        glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


        glDepthFunc(GL_LESS);
        lampShader.use();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBindVertexArray(data.vao);
        auto model = glm::translate(glm::translate(glm::mat4(), lightPos), glm::vec3(2. * sin(glfwGetTime()), 1. * cos(glfwGetTime()), 0.));
        
        lampShader.setMat4("model", model);
        lampShader.setMat4("view", camera.GetViewMatrix());
        lampShader.setMat4("projection", projection);
        lampShader.setFloat("time", (float)glfwGetTime());
        glDrawArrays(GL_TRIANGLES, 0, 36);


        glDepthFunc(GL_LEQUAL);
        skyboxShader.use();
        Cubemap::use(d.skybox); 
        glBindVertexArray(skyboxData.vao);
        skyboxShader.setMat4("projection", projection);
        skyboxShader.setMat4("view", glm::mat4(glm::mat3(camera.GetViewMatrix())));
        glDrawArrays(GL_TRIANGLES, 0, 36);


    };

    auto start_time = std::chrono::steady_clock::now();
    auto end_time = start_time + frame_duration(1);
    auto processing_time = start_time - std::chrono::steady_clock::now();
    auto[xBefore, yBefore] = std::make_tuple( 400., 300. );

    auto lastWriteTime = [](std::experimental::filesystem::path& p) {return std::experimental::filesystem::last_write_time(p); };
    auto lastTimeModifiedV = lastWriteTime(vertexPath);
    auto lastTimeModifiedF = lastWriteTime(fragmentPath);

    while (!glfwWindowShouldClose(window)) {
        start_time = std::chrono::steady_clock::now();
        end_time = start_time + frame_duration(1);
        if (glOperationRunning.try_lock()) {
            drawGL();
            checkGLError();
            glfwSwapBuffers(window);
            glOperationRunning.unlock();
        }
        if (lastTimeModifiedV != lastWriteTime(vertexPath) || lastTimeModifiedF != lastWriteTime(fragmentPath)) {
            // reload shaders
            Shader s(vertexPath, fragmentPath);
            glOperationRunning.lock();
            lightShader = s;
            lightShader.use();
            lightShader.setMat4("projection", projection);
            lightShader.setVec3("lightPos", lightPos);
            lightShader.setVec3("objectColor", 1.f, 1.f, 1.f);
            lightShader.setVec3("lightColor", 1.f, 1.0f, 1.0f);
            glOperationRunning.unlock();
            lastTimeModifiedV = lastWriteTime(vertexPath);
            lastTimeModifiedF = lastWriteTime(fragmentPath);
        }
        glfwPollEvents();
        processInput(0.05f, xBefore, yBefore);
        processing_time = std::chrono::steady_clock::now() - start_time;
        // std::cout << processing_time.count() << std::endl;
        std::tie(xBefore, yBefore) = getMousePos();
        std::this_thread::sleep_until(end_time);
    }
    glfwHideWindow(window);
}

void wrappingFunction() {
    try { 
        std::cout << std::experimental::filesystem::current_path() << std::endl;
        auto managedWindow = init();
        auto applicationData = setupOpenGL(managedWindow);
        loop(managedWindow, applicationData);
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