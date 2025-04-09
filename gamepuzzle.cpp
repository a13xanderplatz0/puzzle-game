#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

void printTable(int table[3][3]) {
    cout << "\nTablero:\n";
    cout << "+---+---+---+\n";
    for (int i = 0; i < 3; ++i) {
        cout << "|";
        for (int j = 0; j < 3; ++j) {
            if (table[i][j] == 0)
                cout << "   |";
            else
                cout << " " << table[i][j] << " |";
        }
        cout << "\n+---+---+---+\n";
    }
}

void fillTable(int table[3][3]) {
    vector<int> numbers = { 1,2,3,4,5,6,7,8 };
    int index = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i == 2 && j == 2) {
                table[i][j] = 0; // espacio vacío
            } else {
                index = rand() % numbers.size();
                table[i][j] = numbers[index];
                numbers.erase(numbers.begin() + index);
            }
        }
    }
}

pair<int, int> findEmpty(int table[3][3]) {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (table[i][j] == 0)
                return { i, j };
    return { -1, -1 }; // No encontrado
}

bool verifyVictory(int table[3][3]) {
    int expected = 1;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i == 2 && j == 2 && table[i][j] == 0)
                return true;
            if (table[i][j] != expected)
                return false;
            expected++;
        }
    }
    return true;
}

void play(int table[3][3]) {
    bool win = false;
    while (!win) {
        printTable(table);
        cout << "\nUsa WASD para mover el bloque vacío (0). w=arriba, s=abajo, a=izquierda, d=derecha\n> ";
        char move;
        cin >> move;

        pair<int, int> empty = findEmpty(table);
        int ei = empty.first;
        int ej = empty.second;
        int ni = ei, nj = ej;

        switch (move) {
        case 'w': ni = ei - 1; break;
        case 's': ni = ei + 1; break;
        case 'a': nj = ej - 1; break;
        case 'd': nj = ej + 1; break;
        default:
            cout << "Movimiento inválido. Usa solo w, a, s, d.\n";
            continue;
        }

        if (ni < 0 || ni > 2 || nj < 0 || nj > 2) {
            cout << "Movimiento fuera de límites.\n";
            continue;
        }

        swap(table[ei][ej], table[ni][nj]);

        if (verifyVictory(table)) {
            printTable(table);
            cout << "\n¡Felicidades! Has ganado :)\n";
            win = true;
        }
    }
}

int main() {
    srand(time(NULL));
    int table[3][3];
    fillTable(table);
    play(table);
    return 0;
}
