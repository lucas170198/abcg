#ifndef GAMEDATA_HPP_
#define GAMEDATA_HPP_

enum class Input {Rigth, Left};

enum class State {Playing, GameOver};

enum class Position{Left, Midle, Rigth};

enum class Level {Easy, Medium, Hard};

struct GameData {
    State m_state{State::Playing};
    Position m_mainCarPos{Position::Midle};
    Level level{Level::Easy};
    int points{0};
};

#endif
