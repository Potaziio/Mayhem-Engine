#include "Window.hpp"

void Mayhem::Window::WindowFramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    Mayhem::Window::width = width;
    Mayhem::Window::height = height;

    if (currentScene->sceneCamera == Scenes::Scene::SCENECAMERA::ORTHOGRAPHIC) {
        currentScene->OrthoCamera->UpdateOrthoCameraBounds(-(float)width * 0.5f, (float)width * 0.5f, -(float)height * 0.5f, (float)height * 0.5f, 0.0f, 100.0f);
        currentScene->OrthoCamera->CameraBoundsX = width;
        currentScene->OrthoCamera->CameraBoundsY = height;
    } else {
        currentScene->PerspectiveCamera->aspectX = width;
        currentScene->PerspectiveCamera->aspectY = height;
    }
 }

void Mayhem::Window::changeScene(enum Scenes::Scene::SCENETYPE sceneType) {
    switch(sceneType) {
        case Scenes::Scene::RUNTIMESCENE:
            delete currentScene;
            currentScene = new Scenes::GameScene();
            currentScene->sceneType = Scenes::Scene::RUNTIMESCENE;
            currentScene->Start();
            break;
    }
}

Mayhem::Window::Window(const char* name, int width, int height) {
    Mayhem::Window::name = name;
    Mayhem::Window::width = width;
    Mayhem::Window::height = height; 

    if (!glfwInit()) {
        fprintf(stderr, "ERROR::GLFW::INIT::FAILED");
        exit(-1);
    }

    // WINDOW FLAGS
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);

    Mayhem::Window::window = glfwCreateWindow(width, height, name, NULL, NULL);

    if (!Mayhem::Window::window) {
        glfwTerminate();
        std::cout << "ERROR::WINDOW::CREATION::FAILED" << std::endl;
        exit(-1);
    }

    glfwMakeContextCurrent(Mayhem::Window::window);
    glfwSwapInterval(1);

    // GLEW INIT
    GLenum err;
    if ((err = glewInit()) != GLEW_OK) {
        std::cout << "ERROR::GLEW::INIT::FAILED" << std::endl;
    }

    // Callbacks setup

    glfwSetFramebufferSizeCallback(Mayhem::Window::window, WindowFramebufferSizeCallback);
    glfwSetKeyCallback(Mayhem::Window::window, Mayhem::Input::KeyboardListener::KeyCallback);
    glfwSetCursorPosCallback(window, Mayhem::Input::MouseListener::MouseCursorCallback);
    glfwSetScrollCallback(window, Mayhem::Input::MouseListener::MouseScrollCallback);
    glfwSetMouseButtonCallback(window, Mayhem::Input::MouseListener::MouseButtonCallback);

    Utils::UI::ImGuiLayer::init();

    changeScene(Scenes::Scene::RUNTIMESCENE);

    currentScene->onSceneStart();

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Seed rand
    srand(time(NULL));
}

bool wireOn = false;

void Mayhem::Window::update() {
    while(!glfwWindowShouldClose(Mayhem::Window::window)) { 
        glfwPollEvents();

        if (Mayhem::Input::KeyboardListener::GetKeyDown(GLFW_KEY_ESCAPE)) {
            std::cout << "Quitting..." << std::endl;
            exit(0);
        }


        if (Mayhem::Input::KeyboardListener::GetKeyDown(GLFW_KEY_P)) {
            if (wireOn) {
                wireOn = false;
                glPolygonMode(GL_FRONT, GL_FILL);
                glPolygonMode(GL_BACK, GL_FILL);
            } else {
                wireOn = true;
                glPolygonMode(GL_FRONT, GL_LINE);
                glPolygonMode(GL_BACK, GL_LINE);
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        currentScene->Update();

        if (currentScene->sceneType == Scenes::Scene::RUNTIMESCENE) {
            currentScene->onRuntimeUpdate();
        }

        Utils::UI::ImGuiLayer::update();
        // ImGui rendering

        glfwSwapBuffers(Mayhem::Window::window);

        Mayhem::Input::KeyboardListener::endKeyFrame();
        Mayhem::Input::MouseListener::endMouseFrame();
        Utils::Time time;
    }
}

void Mayhem::Window::freeMemory() {
    glDeleteFramebuffers(GL_FRAMEBUFFER, &windowFBO);
    glDeleteRenderbuffers(GL_RENDERBUFFER, &windowRBO);
    glDeleteTextures(GL_TEXTURE, &windowFBOTexture);

    currentScene->freeSceneMemory();
    delete currentScene;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    glfwDestroyWindow(Window::window);
}

// Initialize static vars

GLFWwindow* Mayhem::Window::window;
Mayhem::Scenes::Scene* Mayhem::Window::currentScene;

unsigned int Mayhem::Window::windowFBO;
unsigned int Mayhem::Window::windowFBOTexture;
unsigned int Mayhem::Window::windowRBO;

float Mayhem::Window::sceneWindowWidth;
float Mayhem::Window::sceneWindowHeight;

int Mayhem::Window::width;
int Mayhem::Window::height;
const char* Mayhem::Window::name;
