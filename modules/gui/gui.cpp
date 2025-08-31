#include "gui.h"

#include "glfw/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

GUI::GUI(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags &= ~ImGuiConfigFlags_NoMouseCursorChange;
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

GUI::~GUI()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void GUI::Draw(const float fps) const
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowPos(ImVec2(10, 10));
    ImGui::SetNextWindowBgAlpha(0.8f);

    ImGui::Begin("Stats");
    ImGui::SetWindowFontScale(2.0f);
    ImGui::Text("FPS: %.1f", fps);
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
