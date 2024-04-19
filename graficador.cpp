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
  CONSOLE_SCREEN_BUFFER_INFO info;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

  int anchoCMD = info.dwSize.X;
  int altoCMD = info.dwSize.Y;
    const int width = anchoCMD; // Ancho de la pantalla
    const int height = altoCMD; // Alto de la pantalla
    int x = width / 2; // Posici�n inicial X
    int y = height / 2; // Posici�n inicial Y
    char key;

    // Limpiar la pantalla
    system("cls");

    // Mostrar el mensaje inicial en la posici�n inicial
    gotoxy(x, y);
    std::cout << "<";

    // Bucle principal
    while (true) {
        // Verificar si se ha presionado alguna tecla
        if (_kbhit()) {
            // Obtener la tecla presionada
            key = _getch();

            // Mover el cursor seg�n la tecla presionada
            switch (key) {
                case 'w':
                    y = (y - 1 + height) % height; // Movimiento hacia arriba (con l�mite circular)
                    break;
                case 's':
                    y = (y + 1) % height; // Movimiento hacia abajo (con l�mite circular)
                    break;
                case 'a':
                    x = (x - 1 + width) % width; // Movimiento hacia la izquierda (con l�mite circular)
                    break;
                case 'd':
                    x = (x + 1) % width; // Movimiento hacia la derecha (con l�mite circular)
                    break;
            }

            // Limpiar la pantalla y mover el cursor a la nueva posici�n
            system("cls");
            gotoxy(x, y);
            std::cout << "<";
        }

        // Esperar un breve periodo de tiempo antes de la pr�xima iteraci�n
        Sleep(100);
    }

    return 0;
}
