#include "openglwindow.hpp"

#include <imgui.h>

#include "abcg.hpp"

void OpenGLWindow::checkCollisions(){
    for(const auto enemyCar : m_enemyCars){
        const auto enemyCarTranslation{enemyCar.m_translation};
        const auto distance{glm::distance(m_mainCar.m_translation, enemyCarTranslation)};

        if(distance < m_mainCar.m_scale * 0.9f + enemyCar.m_scale * 0.85f){
            m_gameData.m_state = State::GameOver;
            m_restartWaitTimer.restart();
        }
    }
}

void OpenGLWindow::positionStateMachine(Input in){
    if(in == Input::Rigth){
        if(m_gameData.m_mainCarPos == Position::Left)
            m_gameData.m_mainCarPos = Position::Midle;
        else if(m_gameData.m_mainCarPos == Position::Midle)
            m_gameData.m_mainCarPos = Position::Rigth;
    }
    else if(in == Input::Left){
        if(m_gameData.m_mainCarPos == Position::Rigth)
            m_gameData.m_mainCarPos = Position::Midle;
        else if(m_gameData.m_mainCarPos == Position::Midle)
            m_gameData.m_mainCarPos = Position::Left;
        
    }
}

void OpenGLWindow::levelUp(){
    if(m_gameData.points >= 50 && m_gameData.level == Level::Easy)
        m_gameData.level = Level::Medium;
    else if(m_gameData.points >= 100 &&  m_gameData.level == Level::Medium)
        m_gameData.level = Level::Hard;
}

void OpenGLWindow::handleEvent(SDL_Event &event){
    if (event.type == SDL_KEYUP){
        if(event.key.keysym.sym == SDLK_LEFT){
            positionStateMachine(Input::Left);
        }
        else if(event.key.keysym.sym == SDLK_RIGHT){
            positionStateMachine(Input::Rigth);
        }
    }
    
}

void OpenGLWindow::initializeGL(){
    //load font
    ImGuiIO &io{ImGui::GetIO()};
    const std::string fontFileName{"Inconsolata-Medium.ttf"};
    auto fileName{getAssetsPath() + fontFileName};
    m_font = io.Fonts->AddFontFromFileTTF(fileName.c_str(), 20.0f);

    if (m_font == nullptr) {
        throw abcg::Exception{abcg::Exception::Runtime("Cannot load font file")};
    }

    // load GPU programing for Vertex and frag
    const std::string vertexShadderFile{"objects.vert"};
    const std::string fragShadderFile{"objects.frag"};
    m_objectsProgram = createProgramFromFile(getAssetsPath() + vertexShadderFile, getAssetsPath() + fragShadderFile);


    abcg::glClearColor(0, 0, 0, 1); // color to clean the screen beteween frames

    #if !defined(__EMSCRIPTEN__)
        abcg::glEnable(GL_PROGRAM_POINT_SIZE);
    #endif

    m_randomEngine.seed(
        std::chrono::steady_clock::now().time_since_epoch().count()
    );

    restart();
}

void OpenGLWindow::restart(){
    m_gameData.m_state = State::Playing;
    m_gameData.points = 0;
    m_gameData.level = Level::Easy;
    m_mainCar.initializeGL(m_objectsProgram);
    m_enemyCars.clear();
    m_enemyCars.resize(3);
    for(EnemyCar &enemyCar : m_enemyCars){
        enemyCar.initializeGL(m_objectsProgram);
    }

}

void OpenGLWindow::update(){
    const int secondsUntilRestart = 5;
    float deltaTime{static_cast<float>(getDeltaTime())};

    if(m_gameData.m_state != State::Playing && m_restartWaitTimer.elapsed() > secondsUntilRestart){
        restart();
        return;
    }

    m_mainCar.update(m_gameData);
    for(EnemyCar &enemyCar : m_enemyCars){
        enemyCar.update(m_gameData, deltaTime);
    }

    if(m_gameData.m_state == State::Playing)
        checkCollisions();
    
    levelUp();
}

void OpenGLWindow::paintGL() {
  update();

  abcg::glClear(GL_COLOR_BUFFER_BIT);
  abcg::glViewport(0, 0, m_viewportWidth, m_viewportHeight);

  m_mainCar.paintGL(m_gameData);

  for(EnemyCar &enemyCar : m_enemyCars){
      enemyCar.paintGL(m_gameData);
  }
}

void OpenGLWindow::paintUI() {
  abcg::OpenGLWindow::paintUI();

  {
    const auto size{ImVec2(300, 85)};
    const auto position{ImVec2((m_viewportWidth - size.x) / 2.0f,
                               (m_viewportHeight - size.y) / 2.0f)};
    ImGui::SetNextWindowPos(position);
    ImGui::SetNextWindowSize(size);
    ImGuiWindowFlags flags{ImGuiWindowFlags_NoBackground |
                           ImGuiWindowFlags_NoTitleBar |
                           ImGuiWindowFlags_NoInputs};
    ImGui::Begin(" ", nullptr, flags);
    ImGui::PushFont(m_font);

    if (m_gameData.m_state == State::GameOver){
      ImGui::Text("Game Over!");
      ImGui::Text("Total points: %d", m_gameData.points);

    }

    ImGui::PopFont();
    ImGui::End();
  }
}

void OpenGLWindow::resizeGL(int width, int height) {
  m_viewportWidth = width;
  m_viewportHeight = height;

  abcg::glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLWindow::terminateGL() {
  abcg::glDeleteProgram(m_objectsProgram);

  m_mainCar.terminateGL();
  for(EnemyCar &enemyCar : m_enemyCars){
      enemyCar.terminateGL();
  }
}


