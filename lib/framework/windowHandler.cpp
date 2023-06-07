#include <iostream>

#include "framework/windowHandler.hpp"
#include "spdlog/spdlog.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

WindowHandler::WindowHandler()
{
    window = NULL;

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Opengl 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

int WindowHandler::activate()
{
    window = glfwCreateWindow(1024, 768, "Ferd.", NULL, NULL);
    if(window == NULL) {
        spdlog::critical("Failed to open GLFW window");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    const char* glsl_version = "#version 130";

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    return 0;
}

int WindowHandler::swapBuffers()
{
    if (window == NULL) {
        spdlog::critical("Window hasn't been activated");
        return -1;
    }

    glfwSwapBuffers(window);
    glfwPollEvents();

    return 0;
}

bool WindowHandler::isWindowRunning()
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        spdlog::debug("Escape was pressed");
        return false;
    }

    if(glfwWindowShouldClose(window) != 0) {
        spdlog::debug("User has closed window");
        return false;
    }

    return true;
}

void WindowHandler::updateCamera(Camera *gameCamera)
{
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        gameCamera->moveUp();
    }

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        gameCamera->moveDown();
    }

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        gameCamera->moveLeft();
    }

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        gameCamera->moveRight();
    }
}

void debugWindow()
{
    ImGui::Begin("Ferd Debug Window", (bool*)true, ImGuiWindowFlags_MenuBar);
    ImGui::Text("This will be used to display debug information");
    ImGui::End();
}

void WindowHandler::update()
{
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    debugWindow();
}

void WindowHandler::render()
{
    // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
