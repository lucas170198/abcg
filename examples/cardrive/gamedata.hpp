#ifndef GAMEDATA_HPP_
#define GAMEDATA_HPP_

enum class Input {Rigth, Left};

enum class State {Playing, GameOver};

enum class Position{Left, Midle, Rigth};

struct GameData {
    State m_state{State::Playing};
    Position m_mainCarPos{Position::Midle};
    int level{0}; //should control the number of cars in the road and the speed for this cars
};

#endif
