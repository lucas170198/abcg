#include <fmt/core.h>

#include "abcg.hpp"
#include "board.hpp"

int main(int argc, char **argv) {
  try {
    // Create application instance
    abcg::Application app(argc, argv);
    
    // Create OpenGL window
    auto window{std::make_unique<Board>()};
    window->setWindowSettings({.title = "Tic Tac Toe"});
    
    // Run application
    app.run(std::move(window));
  } catch (const abcg::Exception &exception) {
    fmt::print(stderr, "{}\n", exception.what());
    return -1;
  }
  return 0;
}