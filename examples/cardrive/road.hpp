#ifndef ROAD_HPP_
#define ROAD_HPP_

#include "abcg.hpp"
#include "gamedata.hpp"
#include <list>

class OpenGLWindow;

class Road {
 public:
  void initializeGL(GLuint program, glm::vec2 translation);
  void paintGL(const GameData &gameData);
  void terminateGL();

 private:
  friend OpenGLWindow;

  GLuint m_program{};
  GLint m_translationLoc{};
  GLint m_colorLoc{};
  GLint m_scaleLoc{};

  GLuint m_vao{};
  GLuint m_vbo{};
  GLuint m_ebo{};
  

  glm::vec4 m_color{1};
  float m_scale = 0.125f;
  glm::vec2 m_translation{glm::vec2(0)};
  glm::vec2 m_velocity{glm::vec2(0)};
};
#endif