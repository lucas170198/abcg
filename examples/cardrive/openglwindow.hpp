#ifndef OPENGLWINDOW_HPP_
#define OPENGLWINDOW_HPP_

#include <imgui.h>

#include <random>
#include <list>
#include "abcg.hpp"
#include "car.hpp"
#include "enemycar.hpp"
#include "gamedata.hpp"

class OpenGLWindow : public abcg::OpenGLWindow {
 protected:
  void handleEvent(SDL_Event& event) override;
  void initializeGL() override;
  void paintGL() override;
  void paintUI() override;
  void resizeGL(int width, int height) override;
  void terminateGL() override;

 private:
  GLuint m_objectsProgram{};

  int m_viewportWidth{};
  int m_viewportHeight{};

  GameData m_gameData;

  Car m_mainCar;
  std::list<EnemyCar> m_enemyCars;


  abcg::ElapsedTimer m_restartWaitTimer;

  ImFont* m_font{};

  std::default_random_engine m_randomEngine;

  void restart();
  void update();
  void positionStateMachine(Input in);
  void levelUp();
  void checkCollisions();
};

#endif