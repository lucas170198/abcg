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
  // Parent class will show fullscreen button and FPS meter
  // abcg::OpenGLWindow::paintUI();
  static bool enabled{true};
  ImGui::Checkbox("Some option", &enabled);
  fmt::print("The checkbox is {}\n", enabled ? "enabled" : "disabled");
  ImGui::Text("Application is running");


}