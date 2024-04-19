#include <iostream>
#include <conio.h> // Para utilizar kbhit() y getch()
#include <windows.h>

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main() {
   //Se lee la entrada
  CONSOLE_SCREEN_BUFFER_INFO info;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
  //Se obtiene el alto y ancho del Cmd que se anb
  int anchoCMD = info.dwSize.X;
  int altoCMD = info.dwSize.Y;
    const int width = anchoCMD; // Ancho de la pantalla
    const int height = altoCMD; // Alto de la pantalla
    int x = width / 2; // Posición inicial X
    int y = height / 2; // Posición inicial Y
    char key;

    // Limpiar la pantalla
    system("cls");

    // Mostrar el mensaje inicial en la posición inicial
    gotoxy(x, y);
    std::cout << "";

    // Bucle principal
    while (true) {
        // Verificar si se ha presionado alguna tecla
        if (_kbhit()) {
            // Obtener la tecla presionada
            key = _getch();

            // Mover el cursor según la tecla presionada
            switch (key) {
                case 'w':
                    y = (y - 1 + height) % height; // Movimiento hacia arriba (con límite circular)
                    break;
                case 's':
                    y = (y + 1) % height; // Movimiento hacia abajo (con límite circular)
                    break;
                case 'a':
                    x = (x - 1 + width) % width; // Movimiento hacia la izquierda (con límite circular)
                    break;
                case 'd':
                    x = (x + 1) % width; // Movimiento hacia la derecha (con límite circular)
                    break;
            }

            gotoxy(x, y);
            std::cout << "";
        }

        // Esperar un breve periodo de tiempo antes de la próxima iteración
        Sleep(100);
    }

    return 0;
}
