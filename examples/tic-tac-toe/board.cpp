#include <fmt/core.h>

#include "board.hpp"

#include <imgui.h>

void Board::initializeGL() {
  auto windowSettings{getWindowSettings()};
  fmt::print("Initial window size: {}x{}\n", windowSettings.width,
             windowSettings.height);
}

void Board::paintGL() {
  // Set the clear color
  abcg::glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2],
                     m_clearColor[3]);
  // Clear the color buffer
  abcg::glClear(GL_COLOR_BUFFER_BIT);
}

void Board::paintUI() {
  // Parent class will show fullscreen button and FPS meter;
  // abcg::OpenGLWindow::paintUI();
  ImGui::ShowDemoWindow();

    // static bool use_work_area = true;
    // static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;

    // // full screen windown
    // const ImGuiViewport* viewport = ImGui::GetMainViewport();
    // ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
    // ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);

    // if (ImGui::Begin("Game", NULL, flags)){
    //   printf("flags: %d", flags);
    // }
    // ImGui::End();
}