#include "sticks.h"
#include <iostream>
using namespace std;

Game::Game(int newSize, bool crossFirst) {
    clear(newSize, crossFirst);
}

void Game::resizeVectors() {
    // горизонтальные линии: points строк × size столбцов
    h_lines.resize(points);
    for (int i = 0; i < points; ++i)
        h_lines[i].assign(size, false);

    // вертикальные линии: points столбцов × size строк (исправлено!)
    v_lines.resize(points);
    for (int i = 0; i < points; ++i)
        v_lines[i].assign(size, false);

    // клетки: size × size
    cells.assign(size, vector<Cell>(size, Cell::EMPTY));
}

void Game::clear(int newSize, bool crossFirst) {
    // устанавливаем новые размеры
    size = newSize;
    points = size + 1;
    maxMoves = 2 * size * (size + 1);

    // изменяем размеры всех векторов
    resizeVectors();

    // сбрасываем состояние игры
    crossTurn = crossFirst;
    status = GameStatus::IN_PROGRESS;
    movesCount = 0;

    // сбрасываем счёт (2 игрока: крестики и нолики)
    scores.resize(2);
    scores[0] = 0;
    scores[1] = 0;
}

bool Game::isValidHorizontalMove(int y, int x) const {
    if (y < 0 || y >= points) return false;
    if (x < 0 || x >= size) return false;
    return !h_lines[y][x];
}

bool Game::isValidVerticalMove(int x, int y) const {
    if (x < 0 || x >= points) return false;
    if (y < 0 || y >= size) return false;
    return !v_lines[x][y];
}

bool Game::isMoveValid(char type, int coord1, int coord2) const {
    // если ход горизонтальный
    if (type == 'h' || type == 'H') {
        return isValidHorizontalMove(coord1, coord2);
    }
    // если ход вертикальный
    if (type == 'v' || type == 'V') {
        return isValidVerticalMove(coord1, coord2);
    }

    return false;
}

bool Game::makeHorizontalMove(int y, int x) {
    if (!isValidHorizontalMove(y, x)) return false;
    h_lines[y][x] = true;
    return true;
}

bool Game::makeVerticalMove(int x, int y) {
    if (!isValidVerticalMove(x, y)) return false;
    v_lines[x][y] = true;
    return true;
}

bool Game::makeTurn(char type, int coord1, int coord2) {
    // проверяем, не закончена ли игра
    if (status != GameStatus::IN_PROGRESS) {
        cout << "Игра уже закончена!\n";
        return false;
    }

    bool success = false;

    // определяем тип хода
    if (type == 'h' || type == 'H') {
        // горизонтальный ход: h y x
        success = makeHorizontalMove(coord1, coord2);
        if (!success) {
            cout << "Неверный горизонтальный ход! Линия уже нарисована или вне диапазона.\n";
        }
    } else if (type == 'v' || type == 'V') {
        // вертикальный ход: v x y
        success = makeVerticalMove(coord1, coord2);
        if (!success) {
            cout << "Неверный вертикальный ход! Линия уже нарисована или вне диапазона.\n";
        }
    } else {
        cout << "Неизвестный тип хода! Используйте 'h' или 'v'.\n";
        return false;
    }

    if (!success) {
        return false;
    }

    // увеличиваем счётчик ходов
    movesCount++;

    // проверяем, образовались ли новые квадраты
    int taken = takeSquares();

    if (taken > 0) {
        cout << "Вы завершили " << taken << " квадрат(ов)! Получаете дополнительный ход.\n";
        // текущий игрок остаётся (не меняем crossTurn)
    } else {
        // нет квадратов — ход переходит к другому игроку
        switchTurn();
    }

    // проверяем, не закончилась ли игра
    checkGameOver();

    return true;
}

bool Game::Move2Square(char type, int coord1, int coord2) const {
    // если ход горизонтальный
    if (type == 'h' || type == 'H') {
        int y = coord1;
        int x = coord2;

        // проверяем клетку над линией (сверху)
        if (y < size) {
            int row = y;
            int col = x;

            if (cells[row][col] == Cell::EMPTY) {
                bool top = h_lines[row + 1][col];
                bool bottom = h_lines[row][col];
                bool left = v_lines[col][row];
                bool right = v_lines[col + 1][row];

                int sidesCount = (top ? 1 : 0) + (bottom ? 1 : 0) + (left ? 1 : 0) + (right ? 1 : 0);

                if (sidesCount == 3) {
                    return true;
                }
            }
        }

        // проверяем клетку под линией (снизу)
        if (y > 0) {
            int row = y - 1;
            int col = x;

            if (cells[row][col] == Cell::EMPTY) {
                bool top = h_lines[row + 1][col];
                bool bottom = h_lines[row][col];
                bool left = v_lines[col][row];
                bool right = v_lines[col + 1][row];

                int sidesCount = (top ? 1 : 0) + (bottom ? 1 : 0) + (left ? 1 : 0) + (right ? 1 : 0);

                if (sidesCount == 3) {
                    return true;
                }
            }
        }
    }

    // если ход вертикальный
    if (type == 'v' || type == 'V') {
        int x = coord1;
        int y = coord2;

        // проверяем клетку справа от линии
        if (x < size) {
            int row = y;
            int col = x;

            if (cells[row][col] == Cell::EMPTY) {
                bool top = h_lines[row + 1][col];
                bool bottom = h_lines[row][col];
                bool left = v_lines[col][row];
                bool right = v_lines[col + 1][row];

                int sidesCount = (top ? 1 : 0) + (bottom ? 1 : 0) + (left ? 1 : 0) + (right ? 1 : 0);

                if (sidesCount == 3) {
                    return true;
                }
            }
        }

        // проверяем клетку слева от линии
        if (x > 0) {
            int row = y;
            int col = x - 1;

            if (cells[row][col] == Cell::EMPTY) {
                bool top = h_lines[row + 1][col];
                bool bottom = h_lines[row][col];
                bool left = v_lines[col][row];
                bool right = v_lines[col + 1][row];

                int sidesCount = (top ? 1 : 0) + (bottom ? 1 : 0) + (left ? 1 : 0) + (right ? 1 : 0);

                if (sidesCount == 3) {
                    return true;
                }
            }
        }
    }

    return false;
}

// окончание игры
void Game::checkGameOver() {
    if (movesCount == maxMoves) {
        status = GameStatus::FINISHED;
    }
}

// проверяет, закончена ли игра
bool Game::isOver() const {
    return status == GameStatus::FINISHED;
}

// получение количества квадратиков, сделанных за ход
int Game::takeSquares() {
    int taken = 0;
    int playerIdx = crossTurn ? 0 : 1; // берём индекс того, кто ходит
    Cell playerCell = crossTurn ? Cell::CROSS : Cell::ZERO; // берём тип клетки, который нужно запомнить

    // проходимся по всему полю
    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            // если находим занятую клетку, то идём дальше по массиву
            if (cells[row][col] != Cell::EMPTY) continue;

            bool top = h_lines[row + 1][col];
            bool bottom = h_lines[row][col];
            bool left = v_lines[col][row];
            bool right = v_lines[col + 1][row];

            // если есть все линии, то увеличиваем значения
            if (top && bottom && left && right) {
                cells[row][col] = playerCell;
                scores[playerIdx]++;
                taken++;
            }
        }
    }

    return taken;
}

// проверка, выиграл ли игрок
bool Game::isWon(bool cross) const {
    if (status != GameStatus::FINISHED) return false;

    int playerIdx = cross ? 0 : 1;
    int opponentIdx = cross ? 1 : 0;

    return scores[playerIdx] > scores[opponentIdx];
}

bool Game::isCrossTurn() const {
    return crossTurn;
}

Cell Game::getCell(int row, int col) const {
    if (row < 0 || row >= size || col < 0 || col >= size) {
        return Cell::EMPTY;
    }
    return cells[row][col];
}

int Game::getScore(bool cross) const {
    return scores[cross ? 0 : 1];
}

int Game::getSize() const {
    return size;
}

void Game::switchTurn() {
    crossTurn = !crossTurn;
}

void Game::print() const {
    cout << "\n   ";
    for (int x = 0; x < points; ++x) cout << " " << x << "  ";
    cout << "\n";

    for (int y = points - 1; y >= 0; --y) {
        // номер строки
        cout << y << " ";
        // горизонтальные линии
        for (int x = 0; x < points; ++x) {
            cout << "+";
            if (x < size) {
                cout << (h_lines[y][x] ? "---" : "   ");
            }
        }
        cout << "\n";

        // вертикальные линии и клетки (кроме последней строки)
        if (y > 0) {
            cout << "  ";
            for (int x = 0; x < size; ++x) {
                // левая вертикальная линия
                cout << (v_lines[x][y-1] ? "|" : " ");
                // клетка
                char c = ' ';
                if (cells[y-1][x] == Cell::CROSS) c = 'X';
                else if (cells[y-1][x] == Cell::ZERO) c = 'O';
                cout << " " << c << " ";
            }
            // правая граница
            cout << (v_lines[size][y-1] ? "|" : " ") << "\n";
        }
    }
    cout << "-----------------------------\n";
    cout << "Ход: " << (crossTurn ? "X" : "O") << "\n";
    cout << "Счёт: X " << scores[0] << " : " << scores[1] << " O\n";
    cout << "Ходов: " << movesCount << "/" << maxMoves << "\n";
    cout << "-----------------------------\n";
}

void Game::printResult() const {
    cout << "\n========================================\n";
    cout << "            ИГРА ОКОНЧЕНА!\n";
    cout << "========================================\n";
    cout << "Финальный счёт:\n";
    cout << "   КРЕСТИКИ (X): " << scores[0] << "\n";
    cout << "   НОЛИКИ (O):   " << scores[1] << "\n";
    cout << "========================================\n";

    if (scores[0] > scores[1]) {
        cout << "  ПОБЕДИЛИ КРЕСТИКИ (X) !!!\n";
    } else if (scores[1] > scores[0]) {
        cout << "  ПОБЕДИЛИ НОЛИКИ (O) !!!\n";
    } else {
        cout << "  НИЧЬЯ!\n";
    }
    cout << "========================================\n";
}