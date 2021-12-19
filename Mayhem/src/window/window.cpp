#include "Window.hpp"

void Mayhem::Window::WindowFramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    Mayhem::Window::width = width;
    Mayhem::Window::height = height;
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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    changeScene(Scenes::Scene::EDITORSCENE);

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
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (Mayhem::Input::KeyboardListener::GetKeyDown(GLFW_KEY_ESCAPE)) {
            std::cout << "Quitting..." << std::endl;
            exit(0);
        }

        // Scene Updating

        currentScene->Update();
        currentScene->GuiUpdate();

        Utils::GUI::EditorGUI::onEditorGuiUpdate();

        if (currentScene->sceneType == Scenes::Scene::EDITORSCENE) {
            currentScene->onEditorUpdate();
        } else if (currentScene->sceneType == Scenes::Scene::RUNTIMESCENE) {
            currentScene->onRuntimeUpdate();
        }

        // ImGui rendering

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(Mayhem::Window::window);

        Mayhem::Input::KeyboardListener::endKeyFrame();
        Mayhem::Input::MouseListener::endMouseFrame();
        Utils::Time time;
    }
}

void Mayhem::Window::freeMemory() {
    currentScene->freeSceneMemory();
    delete currentScene;

    glfwTerminate();
    glfwDestroyWindow(Window::window);
}

// Initialize static vars

GLFWwindow* Mayhem::Window::window;
Mayhem::Scenes::Scene* Mayhem::Window::currentScene;
int Mayhem::Window::width;
int Mayhem::Window::height;
const char* Mayhem::Window::name;
