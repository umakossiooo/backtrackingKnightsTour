#include <iostream>
#include <fstream> // Para manejar archivos
#include <vector>
using namespace std;

// Movimiento posible del caballo
int dx[] = {2, 1, -1, -2, -2, -1, 1, 2};
int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};

// Función para verificar si el siguiente movimiento es válido
bool isValidMove(int x, int y, int N, vector<vector<int>> &board) {
    return (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1);
}

// Función recursiva de backtracking
bool solveKnightTour(int x, int y, int moveCount, int N, vector<vector<int>> &board) {
    if (moveCount == N * N) {
        return true; // El caballo ha recorrido todo el tablero
    }

    // Probar todos los movimientos posibles
    for (int i = 0; i < 8; i++) {
        int nextX = x + dx[i];
        int nextY = y + dy[i];

        if (isValidMove(nextX, nextY, N, board)) {
            board[nextX][nextY] = moveCount; // Hacer el movimiento
            if (solveKnightTour(nextX, nextY, moveCount + 1, N, board)) {
                return true;
            }
            board[nextX][nextY] = -1; // Retroceder (backtrack)
        }
    }

    return false;
}

int main() {
    int N;

    // Leer la entrada desde un archivo llamado "in.txt"
    ifstream inputFile("in.txt");
    if (!inputFile) {
        cerr << "Error: No se pudo abrir el archivo in.txt" << endl;
        return 1;
    }
    inputFile >> N; // Leer el tamaño del tablero
    inputFile.close();

    // Crear el tablero inicial
    vector<vector<int>> board(N, vector<int>(N, -1));

    // Posición inicial del caballo
    board[0][0] = 0;

    // Crear el archivo de salida
    ofstream outputFile("out.txt");
    if (!outputFile) {
        cerr << "Error: No se pudo crear el archivo output.txt" << endl;
        return 1;
    }

    // Resolver el problema
    if (solveKnightTour(0, 0, 1, N, board)) {
        // Imprimir la solución en la consola y en el archivo
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << board[i][j] << "\t";
                outputFile << board[i][j] << "\t";
            }
            cout << endl;
            outputFile << endl;
        }
    } else {
        // Mensaje de error si no hay solución
        string errorMsg = "No se encontro solucion para un tablero de tamano " + to_string(N) + ".";
        cout << errorMsg << endl;
        outputFile << errorMsg << endl;
    }

    outputFile.close(); // Cerrar el archivo de salida
    return 0;
}
