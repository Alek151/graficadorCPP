#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cmath>
#include <vector>

// Librerias para el manejo de datos y arreglos, y verificación de pantalla.
using namespace std;


// inicializamos un objeto que contendra las posiciones
struct Cuadrado {
    int x;
    int y;
    int lado;
};


// nos ayudamos de vector para utilizar el objeto y almacenar cuadrados
vector<Cuadrado> cuadrados;

// configuramos coordenadas

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//funcion para dibujar los cuadrados

void dibujarCuadrado(int x, int y, int lado, int width, int height, char caracter) {
    for (int i = 0; i < lado; ++i) {
        for (int j = 0; j < lado; ++j) {
            if (i == 0 || i == lado - 1 || j == 0 || j == lado - 1) {
                int px = (x + j) % width;
                int py = (y + i) % height;

                gotoxy(px, py);
                cout << caracter;
            }
        }
    }
}

// funcion para insertar el cuadrado en el vector
void insertarCuadrado(int x, int y, int width, int height) {
    int lado;
    cout << "in Base:";
    cin >> lado;
    Cuadrado nuevo_cuadrado = {x, y, lado};
    cuadrados.push_back(nuevo_cuadrado);
    system("cls");
    char caracter = '*';

    if (x < 0) x = 0;
    if (y < 0) y = 0;


 // for que recorre la construcción del Vector
    for (const auto& cuadrado : cuadrados) {
        dibujarCuadrado(cuadrado.x, cuadrado.y, cuadrado.lado, width, height, caracter);
    }
}

int main() {

    //inicialización
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

    //obtengo tamaños de la cmd creada en cada maquina para determinar un tamaño en pantalla
    int anchoCMD = info.dwSize.X;
    int altoCMD = info.dwSize.Y;
    //obtengo los valores y los almaceno en ancho y alto global
    const int width = anchoCMD;
    const int height = altoCMD;

    //determino una posición X y Y inicial al centro diviendo el valor obtenido por dos.
    int x = width / 2;
    int y = height / 2;
    // llave para extraer las funciones
    char key;

    // limpio pantalla
    system("cls");
    //llevo el cursor a la posición establecida
    gotoxy(x, y);
    //pintar cursor
    cout << "";
     //incia el ciclo para leer los valores del usuario
    while (true) {
            // se establece el metodo kbhit para verificar si se presiona la tecla (este metodo no bloquea la ejecución del programa)
        if (_kbhit()) {
            // obtenemos el valor con _getch() y se almacena en Key
            key = _getch();
             //leemos el valor y entramos en el case correspondiente, ya sea para moverse o dibujar según los valores.
            switch (key) {
                case 'w':
                    y = (y - 1 + height) % height;
                    break;
                case 's':
                    y = (y + 1) % height;
                    break;
                case 'a':
                    x = (x - 1 + width) % width;
                    break;
                case 'd':
                    x = (x + 1) % width;
                    break;
                case '1':
                    // creación de cuadrado, nos vamos a la inserción y ejecución de bucle.
                    insertarCuadrado(x, y, width, height);
                    break;
            }
            //nos vamos al valor ejecutado con el cursor en su posición
            gotoxy(x, y);
            cout << "";
        }

        Sleep(100);
    }

    return 0;
}
