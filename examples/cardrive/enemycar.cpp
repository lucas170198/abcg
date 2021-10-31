#include "enemycar.hpp"

#include <glm/gtx/fast_trigonometry.hpp>
#include <glm/gtx/rotate_vector.hpp>

float EnemyCar::mapPositionToXCord(Position pos) {
    switch (pos) {
        case Position::Midle:
            return 0;
            break;
        case Position::Rigth:
            return 0.7f;
            break;
        case Position::Left:
            return -0.7f;
            break;
        default:
            throw abcg::Exception("Invalid position");
            break;
    }
}

void EnemyCar::initializeGL(GLuint program) {
    terminateGL();

    m_program = program;
    m_colorLoc = abcg::glGetUniformLocation(m_program, "color");
    m_scaleLoc = abcg::glGetUniformLocation(m_program, "scale");
    m_translationLoc = abcg::glGetUniformLocation(m_program, "translation");
    m_randomEngine.seed(
        std::chrono::steady_clock::now().time_since_epoch().count());

    auto &re{m_randomEngine};
    const int randomEnumIndex = m_randomDist(re);
    float xInitalCord = mapPositionToXCord(static_cast<Position>(randomEnumIndex));  // random choose the track
    m_translation = glm::vec2{xInitalCord, initialyPos};
    m_velocity = glm::vec2(0);

    std::array<glm::vec2, 24> positions{
        // Car body
        glm::vec2{-02.5f, +3.0f},
        glm::vec2{0, +4.0f},
        glm::vec2{02.5f, +3.0f},
        glm::vec2{-02.5f, -3.0f},
        glm::vec2{02.5f, -3.0f},

        // whell up left
        glm::vec2{-2.7f, +3.0f},
        glm::vec2{-3.7f, +3.0f},
        glm::vec2{-3.7f, +2.0f},
        glm::vec2{-2.7f, +2.0f},

        // whell up rigth
        glm::vec2{+2.7f, +3.0f},
        glm::vec2{+3.7f, +3.0f},
        glm::vec2{+3.7f, +2.0f},
        glm::vec2{+2.7f, +2.0f},

        // // whell down left
        glm::vec2{-2.7f, -3.0f},
        glm::vec2{-3.7f, -3.0f},
        glm::vec2{-3.7f, -2.0f},
        glm::vec2{-2.7f, -2.0f},

        // down rigth
        glm::vec2{+2.7f, -3.0f},
        glm::vec2{+3.7f, -3.0f},
        glm::vec2{+3.7f, -2.0f},
        glm::vec2{+2.7f, -2.0f},
    };

    // Normalize
    for (auto &position : positions) {
        position /= glm::vec2{3.7f, 3.7f};
    }

    const std::array indices{// car body
                        0, 1, 2,
                        0, 2, 3,
                        0, 2, 4,
                        0, 4, 3,
                        //whells
                        5, 6, 7,
                        5, 8, 7,
                        9, 10, 11,
                        9, 12, 11,
                        13, 14, 15,
                        13, 16, 15,
                        17, 18, 19,
                        17, 20, 19};

    // Generate VBO
    abcg::glGenBuffers(1, &m_vbo);
    abcg::glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions.data(), GL_STATIC_DRAW);
    abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Generate EBO
    abcg::glGenBuffers(1, &m_ebo);
    abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    abcg::glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(),
                    GL_STATIC_DRAW);
    abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Get location of attributes in the program
    GLint positionAttribute{abcg::glGetAttribLocation(m_program, "inPosition")};

    // Create VAO
    abcg::glGenVertexArrays(1, &m_vao);

    // Bind vertex attributes to current VAO
    abcg::glBindVertexArray(m_vao);

    abcg::glEnableVertexAttribArray(positionAttribute);
    abcg::glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    abcg::glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0,
                            nullptr);
    abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

    abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

    // End of binding to current VAO
    abcg::glBindVertexArray(0);
}

void EnemyCar::paintGL(const GameData &gameData) {
    if (gameData.m_state != State::Playing) return;

    abcg::glUseProgram(m_program);

    abcg::glBindVertexArray(m_vao);

    abcg::glUniform1f(m_scaleLoc, m_scale);
    abcg::glUniform2fv(m_translationLoc, 1, &m_translation.x);

    abcg::glUniform4fv(m_colorLoc, 1, &m_color.r);
    const int numberOfTriangulesToDrawObj = 13;
    abcg::glDrawElements(GL_TRIANGLES, numberOfTriangulesToDrawObj * 3,
        GL_UNSIGNED_INT, nullptr);

    abcg::glBindVertexArray(0);

    abcg::glUseProgram(0);
}

void EnemyCar::terminateGL(){
    abcg::glDeleteBuffers(1, &m_vbo);
    abcg::glDeleteBuffers(1, &m_ebo);
    abcg::glDeleteVertexArrays(1, &m_vao);
}

void EnemyCar::update(const GameData &gameData, float deltaTime) {
    //end of screen
    if(m_translation.y <= -1.5f){
        auto &re{m_randomEngine};
        const int randomEnumIndex = m_randomDist(re);
        m_translation.x =  mapPositionToXCord(static_cast<Position>(randomEnumIndex));
        m_translation.y = initialyPos;
    }
    else{
        m_translation.y -= 0.5f * deltaTime;  // TODO: add level here
    }
}
