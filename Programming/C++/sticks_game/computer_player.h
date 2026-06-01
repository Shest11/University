#pragma once

#include <iostream>
#include "sticks.h"
#include <vector>
using namespace std;

struct Move {
    char type; // 'h' или 'v'
    int coord1;// для 'h': y (высота), для 'v': x (позиция)
    int coord2;// для 'h': x (позиция), для 'v': y (высота)

    // метод для вывода хода на экран (для отладки)
    void print() const {
        cout << type << " " << coord1 << " " << coord2;
    }
};

class ComputerPlayer {
public:
    // конструктор
    ComputerPlayer();

    // выбор как ходить
    Move chooseMove(const Game& game);

private:
    // получить все возможные ходы в данный момент
    vector<Move> getAllMoves(const Game& game) const;

    // найти ходы, которые завершают квадрат (выигрышные)
    vector<Move> getWinningMoves(const Game& game) const;
};