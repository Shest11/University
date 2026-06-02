#include "computer_player.h"
#include <iostream>

using namespace std;

// инициализируем генератор случайных чисел
ComputerPlayer::ComputerPlayer() {
    // time(nullptr) возвращает текущее время в секундах
    // благодаря этому каждый запуск игры будет разным
    srand(time(nullptr));
}

// находим все ходы
vector<Move> ComputerPlayer::getAllMoves(const Game& game) const {
    vector<Move> moves;

    int size = game.getSize(); // размер поля
    int points = size + 1;     // количество точек

    // собираем все горизонтальные ходы
    for (int y = 0; y < points; ++y) {
        for (int x = 0; x < size; ++x) {
            // проверяем, можно ли сделать этот ход
            if (game.isMoveValid('h', y, x)) {
                moves.push_back({'h', y, x});
            }
        }
    }

    // собираем все вертикальные ходы
    for (int x = 0; x < points; ++x) {
        for (int y = 0; y < size; ++y) {
            if (game.isMoveValid('v', x, y)) {
                moves.push_back({'v', x, y});
            }
        }
    }

    return moves;
}

// находим выигрышные ходы
vector<Move> ComputerPlayer::getWinningMoves(const Game& game) const {
    vector<Move> winningMoves;

    // получаем все возможные ходы
    vector<Move> allMoves = getAllMoves(game);

    // проверяем каждый ход
    for (const Move& move : allMoves) {
        // если этот ход завершает квадрат - добавляем в список
        if (game.Move2Square(move.type, move.coord1, move.coord2)) {
            winningMoves.push_back(move);
        }
    }

    return winningMoves;
}

// выбор хода для ИИ
Move ComputerPlayer::chooseMove(const Game& game) {
    vector<Move> winningMoves = getWinningMoves(game);

    if (!winningMoves.empty()) {
        // если есть выигрышные ходы - выбираем случайный из них
        int index = rand() % winningMoves.size();
        cout << "Компьютер завершает квадрат!\n";
        return winningMoves[index];
    }

    // если нет выигрышных ходов, то выбираем случайный
    vector<Move> allMoves = getAllMoves(game);

    int index = rand() % allMoves.size();
    cout << "Компьютер выбрал случайный ход\n";
    return allMoves[index];
}