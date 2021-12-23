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
        case Scenes::Scene::EDITORSCENE:
            delete currentScene;
            currentScene = new Scenes::EditorScene();
            currentScene->sceneType = Scenes::Scene::EDITORSCENE;
            currentScene->Start();
            break;
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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Utils::UI::ImGuiLayer::init();

    changeScene(Scenes::Scene::RUNTIMESCENE);

    currentScene->onSceneStart();

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Seed rand
    srand(time(NULL));
}

void Mayhem::Window::update() {
    while(!glfwWindowShouldClose(Mayhem::Window::window)) { 
        glfwPollEvents();

        if (Mayhem::Input::KeyboardListener::GetKeyDown(GLFW_KEY_ESCAPE)) {
            std::cout << "Quitting..." << std::endl;
            exit(0);
        }



        glClear(GL_COLOR_BUFFER_BIT);
        Utils::UI::ImGuiLayer::update();
        currentScene->Update();


        if (currentScene->sceneType == Scenes::Scene::EDITORSCENE) {
            currentScene->onEditorUpdate();
        } else if (currentScene->sceneType == Scenes::Scene::RUNTIMESCENE) {
            currentScene->onRuntimeUpdate();
        }

        // ImGui rendering

        glfwSwapBuffers(Mayhem::Window::window);

        Mayhem::Input::KeyboardListener::endKeyFrame();
        Mayhem::Input::MouseListener::endMouseFrame();
        Utils::Time time;
    }
}

void Mayhem::Window::freeMemory() {
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
int Mayhem::Window::width;
int Mayhem::Window::height;
const char* Mayhem::Window::name;
