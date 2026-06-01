#pragma once
#include <vector>
using namespace std;

enum class Cell {
    EMPTY, // клетка пуста
    CROSS, // крестик
    ZERO   // нолик
};

enum class GameStatus {
    IN_PROGRESS,
    FINISHED
};

class Game {
public:
    // конструктор
    Game(int size = 6, bool crossFirst = true);

    // очистка поля для новой игры
    void clear(int newSize, bool crossFirst = true);

    // сделать ход
    bool makeTurn(char type, int coord1, int coord2);

    // проверка состояния игры
    bool isOver() const;
    bool isWon(bool cross) const;
    bool isCrossTurn() const;

    // получение информации
    Cell getCell(int row, int col) const;
    int getScore(bool cross) const;
    int getSize() const;

    // проверка на ход для ИИ
    bool isMoveValid(char type, int coord1, int coord2) const;
    bool Move2Square(char type, int coord1, int coord2) const;

    // отрисовка
    void print() const;
    void printResult() const;

private:
    int size;     // размер поля (size x size клеток)
    int points;   // точек на сторону (size + 1)
    int maxMoves; // максимальное количество ходов

    vector<vector<bool>> h_lines; // горизонтальные линии [y][x]
    vector<vector<bool>> v_lines; // вертикальные линии [x][y]
    vector<vector<Cell>> cells;   // клетки [row][col]

    vector<int> scores; // очки [0] - крестики, [1] - нолики
    bool crossTurn; // чья очередь?
    int movesCount; // количество сделанных ходов
    GameStatus status; // статус игры

    void resizeVectors(); // изменение размера векторов

    bool isValidHorizontalMove(int y, int x) const;
    bool isValidVerticalMove(int x, int y) const;

    bool makeHorizontalMove(int y, int x);
    bool makeVerticalMove(int x, int y);

    int takeSquares();
    void checkGameOver();
    void switchTurn();
};