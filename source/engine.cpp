#include "engine.h"

#include "spdlog/spdlog.h"
#include "glm/vec3.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "../modules/shader/shader.h"

Engine::Engine(const int width, const int height, const char* title)
    : window_(width, height, "Voxel Engine"), // initializes first
      shader_(ASSETS_PATH "shaders/base_vertex.glsl", ASSETS_PATH "shaders/base_fragment.glsl"),
      camera_(glm::vec3(0.0f, 0.0f, 0.0f), width, height)
      // world_()
{
}

void Engine::Run()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    const ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window_.GetHandle(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window_.GetHandle()))
    {
        const double delta_time = CalculateDeltaTime();
        camera_.HandleInput(window_.GetHandle(), delta_time);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader_.Use();
        camera_.Matrix(45.0f, 0.1f, 100.0f, shader_.GetProgramId(), "camera_matrix");
        world_.Draw(shader_);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(10, 10));
        ImGui::SetNextWindowBgAlpha(0.3f);

        ImGui::Begin("Stats");
        ImGui::Text("FPS: %.1f", 1.0 / delta_time);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window_.SwapBuffers();
        window_.PollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

double Engine::CalculateDeltaTime()
{
    static double last_time = glfwGetTime();

    const double current_time = glfwGetTime();
    const double delta_time = current_time - last_time;

    last_time = current_time;

    return delta_time;
}
