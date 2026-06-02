#include "sticks.h"
#include "computer_player.h"
#include <iostream>
#include <string>
#include <sstream> // для парсинга
#include <unistd.h>

using namespace std;

int main() {
    cout << "ИГРА «ПАЛОЧКИ»\n";

    // выбираем размер поля
    int fieldSize;
    cout << "Размер поля (2-10): ";
    cin >> fieldSize;
    
    if (fieldSize < 2) fieldSize = 2;
    if (fieldSize > 10) fieldSize = 10;
    
    // выбираем режим игры
    int mode;
    cout << "\nРежим игры:\n";
    cout << "1 - Два игрока\n";
    cout << "2 - Против компьютера\n";
    cout << "3 - Демонстрационный режим\n";
    cout << "Выбор: ";
    cin >> mode;

    bool vsComputer = mode == 2;
    bool demoMode = mode == 3;

    bool crossFirst = true;
    if (!demoMode) {
        // выбираем кто первый ходит
        int first;
        cout << "\nКто первый?\n";
        cout << "1 - Крестики (X)\n";
        cout << "2 - Нолики (O)\n";
        cout << "Выбор: ";
        cin >> first;
        crossFirst = first == 1;
    } else {
        cout << "\nДемонстрационный режим: первыми ходят КРЕСТИКИ (X)\n";
    }

    bool playerIsCross = crossFirst;

    // создаём экземпляры
    Game game(fieldSize, crossFirst);
    ComputerPlayer computer;

    // главный игровой цикл
    while (!game.isOver()) {
        game.print();

        bool isPlayerTurn = game.isCrossTurn() == playerIsCross;

        // демонстрационный режим
        if (demoMode) {
            cout << "\nДемонстрационный режим. Ход: " << (game.isCrossTurn() ? "X" : "O") << endl;

            // задержка, чтобы пользователь успел увидеть поле
            sleep(3);

            Move move = computer.chooseMove(game);
            cout << "Компьютер (" << (game.isCrossTurn() ? "X" : "O") << ") ходит: ";
            move.print();
            cout << endl;

            game.makeTurn(move.type, move.coord1, move.coord2);
        }

        // режимы 1 и 2
        else {

            // ходит игрок
            if (isPlayerTurn || !vsComputer) {
                cout << "\nВаш ход (" << (game.isCrossTurn() ? "X" : "O") << ")\n";
                cout << "[формат: h y x  или  v y x]: ";

                string line;
                getline(cin, line);
                if (line.empty()) {
                    cout << "Введите ход!\n";
                    continue;
                }

                istringstream iss(line);
                char type;
                int y, x;

                if (!(iss >> type >> y >> x)) {
                    cout << "Неверный формат! Пример: h 3 2 или v 2 1\n";
                    continue;
                }

                bool success = false;
                if (type == 'h' || type == 'H') {
                    success = game.makeTurn('h', y, x);
                } else if (type == 'v' || type == 'V') {
                    // в makeTurn ожидается v x y, поэтому меняем аргументы местами
                    success = game.makeTurn('v', x, y);
                } else {
                    cout << "Неизвестный тип! Используйте h или v.\n";
                    continue;
                }

                if (!success) {
                    cout << "Ход невозможен (линия уже нарисована или вне диапазона).\n";
                }
            }

            // ходит комп
            else {
                cout << "\nХод компьютера (" << (game.isCrossTurn() ? "X" : "O") << ")\n";

                Move move = computer.chooseMove(game);

                cout << "Компьютер ходит: ";
                move.print();
                cout << endl;

                game.makeTurn(move.type, move.coord1, move.coord2);
            }
        }
    }
    
    // вывод результатов
    game.print();
    game.printResult();

    // вывод результатов игры с ИИ
    if (vsComputer) {
        // проверка победил ли человек: true - Крестик, false - Нолик
        bool playerWon = (playerIsCross && game.isWon(true)) || (!playerIsCross && game.isWon(false));
        
        if (playerWon) {
            cout << "\nВЫ ПОБЕДИЛИ КОМПЬЮТЕР!\n";
        } else if (game.isWon(!playerIsCross)) {
            cout << "\nКОМПЬЮТЕР ПОБЕДИЛ...\n";
        } else {
            cout << "\nНИЧЬЯ!\n";
        }
    }

}