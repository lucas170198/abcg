#ifndef ENEMYCAR_HPP_
#define ENEMYCAR_HPP_

#include "abcg.hpp"
#include "gamedata.hpp"

#include<random>

class OpenGLWindow;

class EnemyCar {
 public:
  void initializeGL(GLuint program);
  void paintGL(const GameData &gameData);
  void terminateGL();

  void update(GameData &gameData, float deltaTime);
  float mapPositionToXCord(Position pos);
  float enemyVelocity(GameData &gameData);


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
  float m_scale{0.125f};
  glm::vec2 m_translation{glm::vec2(0)};
  glm::vec2 m_velocity{glm::vec2(0)};

  std::default_random_engine m_randomEngine;
  std::uniform_int_distribution<int> m_trackDist{0, 2}; // random choose the track started by the enemy
  std::uniform_real_distribution<float> m_initialYPosDist{1.0f, 3.0f};

  Position m_carPorsition;
};
#endif