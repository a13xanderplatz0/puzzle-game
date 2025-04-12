#include <iostream>    // Para std::cout, std::cin
#include <vector>      // Para std::vector
#include <cstdlib>     // Para rand(), srand()
#include <ctime>       // Para time()
#include <utility>     // Para std::pair, std::swap

// Función para imprimir el tablero
void imprimirTablero(int tablero[3][3]) {
    std::cout << "\nTablero:\n";
    std::cout << "+---+---+---+\n";
    for (int i = 0; i < 3; ++i) {
        std::cout << "|";
        for (int j = 0; j < 3; ++j) {
            if (tablero[i][j] == 0)
                std::cout << "   |";  // Casilla vacía
            else
                std::cout << " " << tablero[i][j] << " |";
        }
        std::cout << "\n+---+---+---+\n";
    }
}

// Función para llenar el tablero con números aleatorios
void llenarTablero(int tablero[3][3]) {
    std::vector<int> numeros = {1, 2, 3, 4, 5, 6, 7, 8};
    
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i == 2 && j == 2) {
                tablero[i][j] = 0;  // Casilla vacía en la esquina inferior derecha
            } else {
                int indice = rand() % numeros.size();
                tablero[i][j] = numeros[indice];
                numeros.erase(numeros.begin() + indice);
            }
        }
    }
}

// Función para encontrar la posición vacía (el 0)
std::pair<int, int> encontrarVacio(int tablero[3][3]) {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (tablero[i][j] == 0)
                return {i, j};
    return {-1, -1};  // No debería ocurrir si el tablero es válido
}

// Función para verificar si el jugador ha ganado
bool verificarVictoria(int tablero[3][3]) {
    int numeroEsperado = 1;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i == 2 && j == 2) {
                if (tablero[i][j] != 0) return false;
            } else {
                if (tablero[i][j] != numeroEsperado) return false;
                numeroEsperado++;
            }
        }
    }
    return true;
}

// Función principal del juego
void jugar(int tablero[3][3]) {
    bool victoria = false;
    
    while (!victoria) {
        imprimirTablero(tablero);
        std::cout << "\nPresiona W-A-S-D para mover (Arriba-Izquierda-Abajo-Derecha)\n> ";
        char movimiento;
        std::cin >> movimiento;

        auto [filaVacia, colVacia] = encontrarVacio(tablero);
        int nuevaFila = filaVacia;
        int nuevaCol = colVacia;

        // Determinar nueva posición según el movimiento
        switch (tolower(movimiento)) {
            case 'w': nuevaFila = filaVacia - 1; break;  // Arriba
            case 's': nuevaFila = filaVacia + 1; break;  // Abajo
            case 'a': nuevaCol = colVacia - 1; break;    // Izquierda
            case 'd': nuevaCol = colVacia + 1; break;    // Derecha
            default:
                std::cout << "Movimiento inválido. Usa solo W, A, S, D.\n";
                continue;
        }

        // Verificar si el movimiento es válido
        if (nuevaFila < 0 || nuevaFila > 2 || nuevaCol < 0 || nuevaCol > 2) {
            std::cout << "Movimiento fuera de los límites del tablero.\n";
            continue;
        }

        // Intercambiar la casilla vacía con la adyacente seleccionada
        std::swap(tablero[filaVacia][colVacia], tablero[nuevaFila][nuevaCol]);

        // Verificar si el jugador ha ganado
        if (verificarVictoria(tablero)) {
            imprimirTablero(tablero);
            std::cout << "\n¡Felicidades! ¡Has resuelto el puzzle!\n";
            victoria = true;
        }
    }
}

int main() {
    srand(time(nullptr));  // Inicializar semilla para números aleatorios
    
    int tablero[3][3];
    llenarTablero(tablero);
    jugar(tablero);
    
    return 0;
}
