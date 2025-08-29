#include "engine.h"

#include "glfw/glfw3.h"
#include "glm/vec3.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

Engine::Engine(const int width, const int height, const char* title)
    : window_(width, height, "Voxel Engine"),
      shader_(ASSETS_PATH "shaders/base_vertex.glsl", ASSETS_PATH "shaders/base_fragment.glsl"),
      camera_(glm::vec3(0.0f, 0.0f, 0.0f), width, height)
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

    renderer_.SetPolygonMode();

    while (!glfwWindowShouldClose(window_.GetHandle()))
    {
        const double delta_time = CalculateDeltaTime();
        camera_.HandleInput(window_.GetHandle(), delta_time);

        renderer_.Clear(0.0f, 0.0f, 0.0f, 1.0f);
        renderer_.Draw(world_, shader_, camera_);

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
