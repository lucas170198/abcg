#ifndef CAR_HPP_
#define CAR_HPP_

#include "abcg.hpp"
#include "gamedata.hpp"


class OpenGLWindow;
class EnemyCar;
class Road;

class Car {
 public:
  void initializeGL(GLuint program);
  void paintGL(const GameData &gameData);
  void terminateGL();

  void update(const GameData &gameData);
  float mapPositionToXCord(Position pos);

 private:
  friend EnemyCar;
  friend Road;
  friend OpenGLWindow;

  GLuint m_program{};
  GLint m_translationLoc{};
  GLint m_colorLoc{};
  GLint m_scaleLoc{};

  GLuint m_vao{};
  GLuint m_vbo{};
  GLuint m_ebo{};

  glm::vec4 m_color{1};
  float m_scale{0.125f};
  const float initialyPos = -0.6f;
  glm::vec2 m_translation{glm::vec2{0, initialyPos}};
  glm::vec2 m_velocity{glm::vec2(0)};
};
#endif